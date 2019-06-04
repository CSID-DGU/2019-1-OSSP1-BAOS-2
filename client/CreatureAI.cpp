#include "DXUT.h"
#include "Home.h"

extern CMouse* g_pMouse;
extern CGameTileMgr* g_pGameTileMgr;
extern CGameObjMgr* g_pGameObjMgr;


CCreatureAI::CCreatureAI(CAniObj* pGameObj) ://ũ���� ������ ���� �� �ʱ�ȭ
	CGameObjController(pGameObj)
{
	AddState(AT_NORMAL, SFSMState((DWORD)this, NULL, OnUpdateNormal, NULL));
	AddState(AT_MOVE, SFSMState((DWORD)this, NULL, OnUpdateMove, NULL));
	AddState(AT_ATTACK, SFSMState((DWORD)this, NULL, OnUpdateAttack, NULL));
	AddState(AT_DIE, SFSMState((DWORD)this, OnBeginDie, NULL, NULL));
}

CCreatureAI::~CCreatureAI(void)
{
}

void CCreatureAI::OnFrameMove(float fElapsedTime)//������ ����
{
	OnPriorityEnemy();					//�켱���� �� ����
	OnUpdateState(fElapsedTime);		//���� ������Ʈ
	OnChangeReserveState();				//����� ���·� ��ȯ
}

void CCreatureAI::OnEndAni(int iAniCategory)//�ִ� ����
{
	if (iAniCategory == AT_DIE)//���� ������ ���
	{
		m_pGameObj->Destroy();//������Ʈ ����
		return;
	}

	pGameObj()->OnChangeAni(AT_NORMAL);//���� ������Ʈ���� NORMAL���� �ִ� ��ȯ
}

void CCreatureAI::OnChangeAni(int iAniCategory)//�ִ� ��ȯ
{
	OnChangeState(iAniCategory);
}

void CCreatureAI::OnPriorityEnemy()//�켱���� �� ����
{
	//���� ���� �ִ������� Ÿ���� ��� ���� �����Ѵ�.
	SetEnemy(g_pGameObjMgr->OnFindTarget(pGameObj(), g_pGameObjMgr->m_setPlayObj, AI_SCOPE));
	if (m_pEnemy == NULL)
	{
		//pEnemy = m_pGameObj->GetDamager();
	}
}

void CCreatureAI::OnUpdateNormal(DWORD dwObj, float fElapsedTime)
{
	CCreatureAI* pController = (CCreatureAI*)dwObj;//��Ʈ�ѷ� AI
	CAniObj* pObj = pController->pGameObj();

	D3DXVECTOR2 vTargetPos = g_pGameTileMgr->FindIndexCenter(*pObj->GetGoalPos());//��ǥ ��ġ�� �޾ƿͼ� Ÿ�� ��ġ �޾ƿ�
	D3DXVECTOR2 vPlayerPos = *pObj->GetPos();//�÷��̾� ��ġ �޾ƿ�

	//�÷��̾� ��ġ�� Ÿ�� index�� �����͸� �����´�.
	STileData* pData = g_pGameTileMgr->GetTileData(g_pGameTileMgr->FindTileIndex(vPlayerPos));
	if (pData != NULL)//�����Ͱ� �������
		pData->m_iTileType = 0;//Ÿ�� Ÿ�� 0����

	if (pObj->GetTeam() == ETEAM_FRIEND)//�Ʊ� ���� ���
		pObj->SetGoalPos(*g_pGameObjMgr->pEnemyTower->GetPos());//��Ÿ�� ��ġ�� ��ǥ ��ġ ����
	else                                //���� ���� ���
		pObj->SetGoalPos(*g_pGameObjMgr->pFriendTower->GetPos());//�Ʊ� Ÿ�� ��ġ�� ��ǥ ����

	pController->m_vPath = NULLVECTOR2;

	//Ÿ�� ��ġ�� �÷��̾� ��ġ ���, ���� �Ÿ�(5)�̻��� ���
	if (CUtil::CalcDist(&vPlayerPos, &vTargetPos) > 5 && *pObj->GetGoalPos() != NULLVECTOR2)
	{
		pObj->OnChangeAni(AT_MOVE);//Ani ���¸� MOVE�� ����
		pData->m_iTileType = 1;//Ÿ��Ÿ�� 1�� ����
	}
}

void CCreatureAI::OnUpdateMove(DWORD dwObj, float fElapsedTime)//�ǽð����� �̵� ������Ʈ
{
	CCreatureAI* pController = (CCreatureAI*)dwObj;
	CAniObj* pObj = pController->pGameObj();

	D3DXVECTOR2 vTargetPos = g_pGameTileMgr->FindIndexCenter(*pObj->GetGoalPos());//Ÿ�� ��ġ 
	D3DXVECTOR2 vPlayerPos = *pObj->GetPos();//�÷��̾� ��ġ

	D3DXVECTOR2 vPathPos = g_pGameTileMgr->FindCenterPos(pController->m_vPath);//��� ����

	if (pController->GetEnemy() != NULL)//���� �ִ� ���
	{
		if (CUtil::CalcDist(pObj, pController->GetEnemy()) < pObj->GetScope())//������Ʈ�� ���� ��ġ�� ���� ���� �ִ°��
			pObj->OnChangeAni(AT_ATTACK);//���� ���·� ��ȯ
		else
			pObj->SetGoalPos(*pController->GetEnemy()->GetPos());//��ǥ ��ġ �缳��
	}

	//��Ʈ�ѷ��� ��κ��Ͱ� ���� �÷��̾� ��ġ�� ��� ��ġ�� ���� ������ ���, 
	if (pController->m_vPath == NULLVECTOR2 || CUtil::CalcDist(&vPlayerPos, &vPathPos) < 5)
		pController->FindNode();//��Ʈ�ѷ� 
	else
	{
		pObj->SetDirectionVector(pController->FollowPath());//���⺤�� ����
		D3DXVECTOR2 vPos = *pObj->GetPos();//��ġ �޾ƿ���

		D3DXVECTOR2 vMoveVel = *pObj->GetDirectionVector() * (pObj->GetSpeed() * fElapsedTime);//�̵��ӵ�

		vPos += vMoveVel;//��ġ���� �̵��ӵ� �����ְ�
		pObj->SetPos(vPos);//��ġ �缳��
	}


	if (CUtil::CalcDist(&vPlayerPos, &vTargetPos) < 5 || *pObj->GetGoalPos() == NULLVECTOR2)
	{
		pObj->OnChangeAni(AT_NORMAL);
	}
}

void CCreatureAI::OnUpdateAttack(DWORD dwObj, float fElapsedTime)//���ݻ��� ������Ʈ
{
	CCreatureAI* pController = (CCreatureAI*)dwObj;
	CAniObj* pObj = pController->pGameObj();

	if (pController->GetEnemy() == NULL)//�ҷ��� ���� ���� ���
	{
		pController->OnChangeAni(AT_NORMAL);//NORMAL ���·� ��ȯ
		return;
	}

	D3DXVECTOR2 vPlayerIndex = g_pGameTileMgr->FindTileIndex(*pObj->GetPos());//Ÿ�ϸŴ������� Ÿ�� ��ġ ������ player index ����
	D3DXVECTOR2 vTargetIndex = g_pGameTileMgr->FindTileIndex(*pController->GetEnemy()->GetPos());//Ÿ�ϸŴ������� ���� ��ġ �޾ƿ� target index ����

	STileData* pData = g_pGameTileMgr->GetTileData(vPlayerIndex);//�÷��̾��� Ÿ�� ������ ����
	pData->m_iTileType = 0;

	pController->m_vPath = NULLVECTOR2;

	if (vTargetIndex != vPlayerIndex)//�÷��̾�� Ÿ���� �ٸ����
	{
		int iAngle = (int)(CUtil::GetDirection(&vPlayerIndex, &vTargetIndex));//�÷��̾� ��ġ�� Ÿ�� ��ġ�� ���� �ҷ���
		pObj->SetDirection((int)(iAngle / 45));//���� ����
	}

	if (CUtil::CalcDist(pObj, pController->GetEnemy()) > pObj->GetScope())
	{
		//������Ʈ�� ���� �Ÿ��� ���ع������� Ŭ���
		pObj->OnChangeAni(AT_NORMAL);//���� NORMAL�� ����
		pData->m_iTileType = 1;
	}
}


void CCreatureAI::OnBeginDie(DWORD dwObj)//���°� �׾��� ���
{
	CCreatureAI* pController = (CCreatureAI*)dwObj;//dwObjũ��ó ������ �Ҵ�
	CAniObj* pObj = pController->pGameObj();

	D3DXVECTOR2 vPlayerIndex = g_pGameTileMgr->FindTileIndex(*pObj->GetPos());

	STileData* pData = g_pGameTileMgr->GetTileData(vPlayerIndex);
	pData->m_iTileType = 1;
}