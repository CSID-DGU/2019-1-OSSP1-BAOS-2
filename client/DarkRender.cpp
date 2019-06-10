#include "DXUT.h"
#include "../Home.h"

extern CTexture * g_pTexture;
extern CSprite * g_pSprite;
extern CCamera* g_pCamera;

CDarkRender::CDarkRender(CGameObj* pGameObj) ://생성 및 초기화
	CImgRender(pGameObj),//Dark img 생성
	m_pDarkInfo(nullptr),//Dark의 정보와 color 초기화
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
	if (m_iTexture == -1)//가리키는 텍스쳐가 없을경우
		return;

	g_pTexture->RestoreTexture(m_iTexture);
}

void CDarkRender::SetDarkMode(D3DXVECTOR2 vPos, int iTexture)//DarkMode 설정
{
	const STextureInfo * SViewInfo = g_pTexture->GetTextureInfo(iTexture);
	DWORD* pViewColor = g_pTexture->GetImgColorBits(iTexture);

	m_pDarkInfo = g_pTexture->GetTextureInfo(m_iTexture);//Dark의 텍스쳐 정보와 color 정보 설정
	m_pDarkColor = g_pTexture->GetImgColorBits(m_iTexture);

	MakeAlpha(m_pDarkColor, pViewColor, vPos, m_pDarkInfo, SViewInfo);
}

void CDarkRender::MakeAlpha(DWORD* pDark, DWORD* pView, D3DXVECTOR2 vPos, const STextureInfo* DarkInfo, const STextureInfo* ViewInfo)
{
	D3DXVECTOR2 vCenter(vPos.x - (int)ViewInfo->m_TextureInfo.Width * 0.5f, vPos.y - (int)ViewInfo->m_TextureInfo.Height * 0.5f);

	for (int y = 0; y < (int)ViewInfo->m_TextureInfo.Height; ++y)
		for (int x = 0; x < (int)ViewInfo->m_TextureInfo.Width; ++x)
		{
			int iDarkX = ((int)vCenter.x + x);  // 검은색이미지에 지워질부분의 위치값
			int iDarkY = ((int)vCenter.y + y);

			int iDarkIndex = (iDarkY * (int)DarkInfo->m_ImgDesc.Width) + iDarkX; // 검은색 이미지 색상값은 일열로 저장되어있다 이를 찾기위해선 세로 크기 * 열 + X값이다. 
			int iViewIndex = (y * (int)ViewInfo->m_TextureInfo.Width) + x; // 일렬로된 배열에서 위치값을 계산 // 예시 1 * 1024 + 1, 3* 1024 + 5  

			if (iDarkX < 0 || iDarkX >= (int)DarkInfo->m_ImgDesc.Width || iDarkY < 0 || iDarkY >= (int)DarkInfo->m_ImgDesc.Height)
				continue;

			D3DXCOLOR DarkColor = pDark[iDarkIndex]; // 배열에서 위치값 ( 인덱스 ) 를 이용하여 색상값을 가져온다
			D3DXCOLOR ViewColor = pView[iViewIndex];

			if (DarkColor.a > ViewColor.a) // 1.0f 는 검은색 0.0f 는 비어있는색
				DarkColor.a = ViewColor.a; // 알파값을 비교하여 작은것을 넣는다

			pDark[iDarkIndex] = DarkColor;
		}
}