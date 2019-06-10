#include "DXUT.h"
#include "../Home.h"

extern CTexture * g_pTexture;
extern CSprite * g_pSprite;
extern CCamera* g_pCamera;

CDarkRender::CDarkRender(CGameObj* pGameObj) ://���� �� �ʱ�ȭ
	CImgRender(pGameObj),//Dark img ����
	m_pDarkInfo(nullptr),//Dark�� ������ color �ʱ�ȭ
	m_pDarkColor(nullptr)
{
}


CDarkRender::~CDarkRender()
{
}


void CDarkRender::Load(wstring wFile)
{
	__super::Load(wFile);
}

void CDarkRender::ClearDark()//Dark clear
{
	if (m_iTexture == -1)//����Ű�� �ؽ��İ� �������
		return;

	g_pTexture->RestoreTexture(m_iTexture);
}

void CDarkRender::SetDarkMode(D3DXVECTOR2 vPos, int iTexture)//DarkMode ����
{
	const STextureInfo * SViewInfo = g_pTexture->GetTextureInfo(iTexture);
	DWORD* pViewColor = g_pTexture->GetImgColorBits(iTexture);

	m_pDarkInfo = g_pTexture->GetTextureInfo(m_iTexture);//Dark�� �ؽ��� ������ color ���� ����
	m_pDarkColor = g_pTexture->GetImgColorBits(m_iTexture);

	MakeAlpha(m_pDarkColor, pViewColor, vPos, m_pDarkInfo, SViewInfo);
}

void CDarkRender::MakeAlpha(DWORD* pDark, DWORD* pView, D3DXVECTOR2 vPos, const STextureInfo* DarkInfo, const STextureInfo* ViewInfo)
{
	D3DXVECTOR2 vCenter(vPos.x - (int)ViewInfo->m_TextureInfo.Width * 0.5f, vPos.y - (int)ViewInfo->m_TextureInfo.Height * 0.5f);

	for (int y = 0; y < (int)ViewInfo->m_TextureInfo.Height; ++y)
		for (int x = 0; x < (int)ViewInfo->m_TextureInfo.Width; ++x)
		{
			int iDarkX = ((int)vCenter.x + x);  // �������̹����� �������κ��� ��ġ��
			int iDarkY = ((int)vCenter.y + y);

			int iDarkIndex = (iDarkY * (int)DarkInfo->m_ImgDesc.Width) + iDarkX; // ������ �̹��� ������ �Ͽ��� ����Ǿ��ִ� �̸� ã�����ؼ� ���� ũ�� * �� + X���̴�. 
			int iViewIndex = (y * (int)ViewInfo->m_TextureInfo.Width) + x; // �Ϸķε� �迭���� ��ġ���� ��� // ���� 1 * 1024 + 1, 3* 1024 + 5  

			if (iDarkX < 0 || iDarkX >= (int)DarkInfo->m_ImgDesc.Width || iDarkY < 0 || iDarkY >= (int)DarkInfo->m_ImgDesc.Height)
				continue;

			D3DXCOLOR DarkColor = pDark[iDarkIndex]; // �迭���� ��ġ�� ( �ε��� ) �� �̿��Ͽ� ������ �����´�
			D3DXCOLOR ViewColor = pView[iViewIndex];

			if (DarkColor.a > ViewColor.a) // 1.0f �� ������ 0.0f �� ����ִ»�
				DarkColor.a = ViewColor.a; // ���İ��� ���Ͽ� �������� �ִ´�

			pDark[iDarkIndex] = DarkColor;
		}
}