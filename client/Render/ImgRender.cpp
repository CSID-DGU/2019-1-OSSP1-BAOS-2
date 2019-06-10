#include "DXUT.h"
#include "../Home.h"

extern CTexture * g_pTexture;
extern CSprite * g_pSprite;
extern CCamera* g_pCamera;

CImgRender::CImgRender(CGameObj * pGameObj) ://������ ������Ʈ ���� �� �ʱ�ȭ
	CRender(pGameObj),
	m_iTexture(-1)
{
}


CImgRender::~CImgRender(void)//�Ҹ�
{
	g_pTexture->ReserveRelease(m_iTexture);//�ؽ��� release
}

void CImgRender::Load(wstring wFile)
{
	m_iTexture = g_pTexture->Load(wFile);//wFile�� �ؽ��� index 
}

bool CImgRender::OnFrameMove(float fElapsedTime)
{
	UpdateWorld();//������Ʈ

	return false;
}

void CImgRender::UpdateWorld()//������Ʈ
{
	D3DXMATRIX matRot;
	MakeRot(matRot);

	D3DXMATRIX matTrans;
	MakeTrans(matTrans);

	D3DXMATRIX matScale;
	MakeScale(matScale);

	m_matWorld = matRot * matScale * matTrans;
	m_matWorld._43 = 0.0f;
}

void CImgRender::OnFrameRender()//Frame Render
{
	if (m_pGameObj == NULL)
		return;

	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);//���

	if (m_pGameObj->IsCmeara() == true)//������Ʈ�� ī�޶��ΰ��
		g_pCamera->GetTransform(&matView);//ī�޶� ��ȯ

	D3DXMATRIX matWorld = m_matWorld * matView;
	matWorld._43 = 0.0f;

	g_pSprite->SetTransform(&matWorld);
	g_pSprite->OnDraw(g_pTexture->GetTexture(m_iTexture), NULL, 0.0f, 0.0f);
}