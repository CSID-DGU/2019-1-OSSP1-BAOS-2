#include "DXUT.h"
#include "../Home.h"

extern CTexture * g_pTexture;
extern CSprite * g_pSprite;
extern CCamera* g_pCamera;

CImgRender::CImgRender(CGameObj * pGameObj) ://렌더링 오브젝트 생성 및 초기화
	CRender(pGameObj),
	m_iTexture(-1)
{
}


CImgRender::~CImgRender(void)//소멸
{
	g_pTexture->ReserveRelease(m_iTexture);//텍스쳐 release
}

void CImgRender::Load(wstring wFile)
{
	m_iTexture = g_pTexture->Load(wFile);//wFile의 텍스쳐 index 
}

bool CImgRender::OnFrameMove(float fElapsedTime)
{
	UpdateWorld();//업데이트

	return false;
}

void CImgRender::UpdateWorld()//업데이트
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
	D3DXMatrixIdentity(&matView);//행렬

	if (m_pGameObj->IsCmeara() == true)//오브젝트가 카메라인경우
		g_pCamera->GetTransform(&matView);//카메라 변환

	D3DXMATRIX matWorld = m_matWorld * matView;
	matWorld._43 = 0.0f;

	g_pSprite->SetTransform(&matWorld);
	g_pSprite->OnDraw(g_pTexture->GetTexture(m_iTexture), NULL, 0.0f, 0.0f);
}