#include "DXUT.h"
#include "Home.h"

extern CCamera* g_pCamera;
extern CMouse* g_pMouse;
extern CGameTileMgr* g_pGameTileMgr;
extern CGameObjMgr* g_pGameObjMgr;

CPlayer::CPlayer(void) :
	m_fTime(0)//�÷��̾� ����
{
	g_pCamera->SetCameraObj(this);//ī�޶� ������Ʈ �÷��̾�� ����
}


CPlayer::~CPlayer(void)
{
}

void CPlayer::Load(wstring wFile)
{
	__super::Load(wFile);//����� Ŭ���� �ε�

	m_pController = new CEricController(this);//�÷��̾� ��Ʈ�ѷ� ����

	SetPos(g_pGameTileMgr->FindCenterPos(m_vPos));//Ÿ�ϸŴ����κ��� ��ġ �޾ƿ� ��ġ ����
	g_pCamera->SetCameraPos(*this->GetPos());//ī�޶� ��ġ ����

	OnChangeAni(AT_NORMAL);//�ִ� ���� ����

	//�ｺ ������Ʈ ����
	CGameObj* pHealth = g_pGameObjMgr->Load(EGAMEOBJ_HEALTH, ETEAM_NENUTAL, L"Creature_Health", L"Health", D3DXVECTOR2(0, 0), 0, ERENDER_NORMAL, true);
	((CHealth*)pHealth)->SetPlayer(this);

	CUI* pMiniDot = NULL;//�÷��̾ �̴ϸʿ� ���̰� Dot ����

	if (m_iTeam == ETEAM_FRIEND)//�Ʊ� ���̸� �ʷϻ����� ����
		pMiniDot = g_pGameObjMgr->UILoad(UI_MINIDOT, L"GreenDot", L"GreenDot", D3DXVECTOR2(0, 0), false, true);

	if (pMiniDot != NULL)//Dot�� ������Ʈ�� ������ ��������
	{
		pMiniDot->SetObj(this);
		pMiniDot->SetScl(D3DXVECTOR2(-2, -2));
	}
}

void CPlayer::OnFrameMove(float fElapsedTime)//�ǽð� ������ ����
{
	__super::OnFrameMove(fElapsedTime);

	D3DXVECTOR2 vRMousePos = g_pMouse->GetOneRMousePos();//������ ���콺�� ��ġ�� �޾ƿ���

	if (vRMousePos != NULLVECTOR2)//Ŭ������ ��� Ŭ���� ���콺�� ��ġ�� ��ǥ �缳��
	{
		m_vGoalPos = g_pGameTileMgr->FindCenterPos(g_pGameTileMgr->FindTileIndex(vRMousePos));
	}
}

void CPlayer::OnDamage(int iDamage, CGameObj* pGameObj)//�÷��̾ �������� �Ծ��� ���
{
	m_iHealth -= iDamage;//ü�¿��� ��������ŭ ���ҽ�Ŵ

	if (m_iHealth <= 0)//ü���� 0�ΰ�� ���º�ȯ
	{
		if (m_iAniCategory != AT_DIE)
			OnChangeAni(AT_DIE);
	}
}