#include "DXUT.h"
#include "../Home.h"

extern CTexture * g_pTexture;
extern CSprite * g_pSprite;
extern CCamera* g_pCamera;

CImgRender::CImgRender(CGameObj * pGameObj) :
	CRender(pGameObj),//���ӿ�����Ʈ ����
	m_iTexture(-1)
{
}


CImgRender::~CImgRender(void)
{
	g_pTexture->ReserveRelease(m_iTexture);
}

void CImgRender::Load(wstring wFile)
{
	//�̹��� �ε�
	m_iTexture = g_pTexture->Load(wFile);
}

bool CImgRender::OnFrameMove(float fElapsedTime)//������ ����
{
	UpdateWorld();

	return false;
}

void CImgRender::UpdateWorld()//���� ���� ������Ʈ
{
	D3DXMATRIX matRot;//matrix ����
	MakeRot(matRot);

	D3DXMATRIX matTrans;
	MakeTrans(matTrans);

	D3DXMATRIX matScale;
	MakeScale(matScale);

	m_matWorld = matRot * matScale * matTrans;
	m_matWorld._43 = 0.0f;
}

void CImgRender::OnFrameRender()//������ ������
{
	if (m_pGameObj == NULL)
		return;

	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);

	if (m_pGameObj->IsCmeara() == true)
		g_pCamera->GetTransform(&matView);

	D3DXMATRIX matWorld = m_matWorld * matView;
	matWorld._43 = 0.0f;

	g_pSprite->SetTransform(&matWorld);
	g_pSprite->OnDraw(g_pTexture->GetTexture(m_iTexture), NULL, 0.0f, 0.0f);
}