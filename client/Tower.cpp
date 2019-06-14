#include "DXUT.h"
#include "Home.h"

extern GameDataMgr * g_pGameDataMgr;
extern CGameObjMgr* g_pGameObjMgr;
extern CGameTileMgr* g_pGameTileMgr;

CTower::CTower(void)//���๰ Ŭ����
{
}


CTower::~CTower(void)
{
}

void CTower::Load(wstring wFile)//wFile load
{
	__super::Load(wFile);

	m_pController = new CTowerAI(this);//���๰ �����ϴ� ��Ʈ�ѷ� ����

	//���๰ ü�� ����
	CGameObj* pHealth = g_pGameObjMgr->Load(EGAMEOBJ_HEALTH, ETEAM_NENUTAL, L"Creature_Health", L"Health", D3DXVECTOR2(0, 0), 0, ERENDER_NORMAL, true);
	((CHealth*)pHealth)->SetPlayer(this);

	CUI* pMiniDot = NULL;//�̴ϸʿ� ������ �̴�Dot ����

	if (m_iTeam == ETEAM_FRIEND)//���� �Ʊ��� ���
		pMiniDot = g_pGameObjMgr->UILoad(UI_MINIDOT, L"GreenDot", L"GreenDot", D3DXVECTOR2(0, 0), false, true);//Dot�� �ʷϻ����� ����

	if (m_iTeam == ETEAM_ENEMY)//���� ������ ���
		pMiniDot = g_pGameObjMgr->UILoad(UI_MINIDOT, L"RedDot", L"RedDot", D3DXVECTOR2(0, 0), false, true);//Dot�� ���������� ����


	if (pMiniDot != NULL)//�̴�Dot�� ���� ���
	{
		pMiniDot->SetObj(this);//������Ʈ ����
		pMiniDot->SetScl(D3DXVECTOR2(-2, -2));//������Ʈ ������ ����
	}

	OnChangeAni(AT_NORMAL);

	for (int Row = (int)m_vPos.x - 1; Row <= m_vPos.x + 1; Row++)//���๰ ���� ĭ��ŭ �ݺ�
		for (int Col = (int)m_vPos.y - 1; Col <= m_vPos.y; Col++)//
		{
			D3DXVECTOR2 vNeighborNode = D3DXVECTOR2((float)Row, (float)Col);
			STileData* pData = g_pGameTileMgr->GetTileData(vNeighborNode);//������ Ÿ�� Data ����
			if (pData == nullptr)
				continue;

			pData->m_iTileType = 0;//TileType ����
		}

	SetPos(g_pGameTileMgr->FindCenterPos(m_vPos));
}

void CTower::OnDamage(int iDamage, CGameObj* pGameObj)//�������� �Ծ��� ��
{
	m_iHealth -= iDamage;//ü�¿��� ������ ����

	if (m_iHealth <= 0)//ü���� 0�� ���
	{
		if (m_iAniCategory != AT_DIE)//���� Die�� ����
			OnChangeAni(AT_DIE);
	}
}

void CTower::OnFrameMove(float fElapsedTime)//Frame ����
{
	__super::OnFrameMove(fElapsedTime);
}