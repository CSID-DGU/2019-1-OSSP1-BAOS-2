#include "DXUT.h"
#include "Home.h"

extern CTexture* g_pTexture;
extern CGameTileMgr* g_pGameTileMgr;

CGameObjContainer::CGameObjContainer(void)//���ӿ�����Ʈ �����̳� ������
{
	//�÷��̿�����Ʈ�� �÷��̾�, ũ����, Ÿ�� ����
	m_setPlayObj.insert(EGAMEOBJ_PLAYER), m_setPlayObj.insert(EGAMEOBJ_CREATURE), m_setPlayObj.insert(EGAMEOBJ_TOWER);
}


CGameObjContainer::~CGameObjContainer(void)
{
	//���ӿ�����Ʈ �����̳ʿ� ����ִ� ���ӿ�����Ʈ���� ��� ��������
	for each(map< int, vector< CGameObj* >>::const_reference mr in m_mapObj)
		for each(vector<CGameObj*>::const_reference vr in mr.second)
			delete vr;

	m_mapObj.clear();//�ʿ�����Ʈ Ŭ����
}

CUI* CGameObjContainer::UILoad(int iUIType, wstring wFile, wstring wName, D3DXVECTOR2 vPos, bool bAni, bool bWork)
{
	//vpos��ġ�� ani, work�� ������ IUIType, wFile, wName�� ������Ʈ�� �ε�
	CUI* pUIObj = new CUI;
	if (pUIObj == NULL)
		return NULL;

	//���ο� UI������Ʈ ���� �� mapReserveObj�� ����
	pUIObj->SetPos(vPos);
	pUIObj->SetAni(bAni);
	pUIObj->SetRenderType(ERENDER_UI);
	pUIObj->Load(wFile);
	pUIObj->SetObjName(wName);
	pUIObj->SetType(iUIType);
	pUIObj->SetWork(bWork);

	m_mapReserveObj[EGAMEOBJ_UI].push_back(pUIObj);
	return pUIObj;
}

CGameObj* CGameObjContainer::Load(int iType, int iTeam, wstring wFile, wstring wName, D3DXVECTOR2 vPos, int iDirection, int iRenderType, bool bWork)
{
	//�޾ƿ� ��ġ�� ã�� �����Ͱ� ������ �ε��ϰ� �̸� ������ �ִ� ������Ʈ �ʿ� ����
	CGameObj* pObj = Alloc(iType);//iType�� ������ �Ҵ�, ������ NULL ����
	if (pObj == NULL)
		return NULL;

	pObj->SetPos(vPos);
	pObj->SetRenderType(iRenderType);
	pObj->SetTeam(iTeam);
	pObj->SetObjName(wName);
	pObj->Load(wFile);
	pObj->SetDirection(iDirection);
	pObj->SetWork(bWork);

	m_mapReserveObj[iType].push_back(pObj);
	return pObj;
}

void CGameObjContainer::Destroy(int iType, wstring wName)
{
	//iType ������ wName������Ʈ ���� 
	for each(vector< CGameObj* >::const_reference vr in m_mapObj[iType])
	{
		if (vr->GetObjName() == wName)
			vr->Destroy();
	}
}

void CGameObjContainer::PostProcess()
{
	// ����Ȱ����� m_mapObj�� ����Ѵ�.
	for each(map<int, vector<CGameObj*>>::const_reference mr in m_mapReserveObj)
	{
		vector<CGameObj*>& vecObj = m_mapObj[mr.first];
		vecObj.insert(vecObj.end(), mr.second.begin(), mr.second.end());
	}

	m_mapReserveObj.clear();

	// �����ɰ��� ó��
	map<int, vector<CGameObj*>>::iterator mit = m_mapObj.begin();
	while (mit != m_mapObj.end())
	{
		for (int i = (int)mit->second.size() - 1; i >= 0; --i)
		{
			if (mit->second[i]->IsDestroy() == false)
				continue;

			SAFE_DELETE(mit->second[i]);
			mit->second.erase(mit->second.begin() + i);
		}

		if (mit->second.empty())
			mit = m_mapObj.erase(mit);
		else
			++mit;
	}
}

CGameObj* CGameObjContainer::OnFindTarget(CGameObj* pGameObj, set< int >& setType, int fLimitDist)
{
	//���� ��ǥ�� ���
	CGameObj* pTarget = NULL;
	int fMinDist = fLimitDist;

	for each(map< int, vector< CGameObj* >>::const_reference mr in m_mapObj)//�ʿ�����Ʈ�� �ִ� 
	{
		if (setType.find(mr.first) == setType.end())
			continue;

		for each(vector< CGameObj* >::const_reference vr in mr.second)
		{
			if (vr == pGameObj || vr->GetTeam() == pGameObj->GetTeam())//vr��ü�� ���ӿ�����Ʈ�ų� ���� ���� ��� continue
				continue;

			if (vr->IsDestroy() == true || vr->GetAniCategory() == AT_DIE)//vr�� �׾��� ���
				continue;

			float fDist = CUtil::CalcDist(pGameObj, vr);//vr�� �ǰ��ӿ�����Ʈ ������ �Ÿ�

			if (fMinDist > fDist)//���� fDist�� �̿��ؼ� ��ǥ���� �ּ� �Ÿ� ����
			{
				fMinDist = (int)fDist;
				pTarget = vr;
			}
		}
	}

	return pTarget;//Ÿ�� ����
}

void CGameObjContainer::NoneOverLap(CGameObj* pGameObj)
{

	for each(map< int, vector< CGameObj* >>::const_reference mr in m_mapObj)
	{
		if (m_setPlayObj.find(mr.first) == m_setPlayObj.end())
			continue;


		for each(vector< CGameObj* >::const_reference vr in mr.second)//
		{
			if (vr->IsDestroy() || pGameObj->IsDestroy())
				continue;

			if (vr == pGameObj)
				continue;

			if (((CAniObj*)pGameObj)->GetDirection() == AT_DIE)
				continue;


			D3DXVECTOR2 vToObject = *pGameObj->GetPos() - *vr->GetPos();
			float fDist = CUtil::CalcDist(pGameObj, vr);

			float fRadiusGap = pGameObj->GetRadius() + vr->GetRadius() - fDist;
			//�ǰ��ӿ�����Ʈ�� vr�� �Ÿ��� �� ������Ʈ�� ���������� ũ�� �ָ� ������ �ִ°�
			//�� �������� �պ��� ������ �� ������Ʈ�� ���ݹ��� ���� �ִ�. 


			if (fRadiusGap >= 0.0f)//�Ÿ��� ���ݹ��� ���� ���� �����Ƿ� ������Ʈ ���¸� �����ؾ��Ѵ�.
			{
				if (((CAniObj*)pGameObj)->GetAniCategory() != AT_ATTACK)//���ݻ��°� �ƴҰ��
					((CAniObj*)pGameObj)->GetController()->SetEnemy(NULL);//�� ���� �ʱ�ȭ

				if (((CAniObj*)vr)->GetAniCategory() != AT_ATTACK)
					((CAniObj*)vr)->GetController()->SetEnemy(NULL);

				if (((CAniObj*)pGameObj)->GetAniCategory() == AT_ATTACK)//���ݻ����� ���
				{
					((CAniObj*)pGameObj)->GetController()->FindNode();//��带 Ž��.
					return;
				}
				else
				{
					//pGameObj->SetGoalPos( NULLVECTOR2 );
					//(( CAniObj* )pGameObj)->GetController()->FindNode();
				}

				if (fDist != 0 && vToObject != 0)//�� ������Ʈ�� �Ȱ��� ��ġ�� ���� ���� ��� ���ӿ�����Ʈ�� ��ġ ����
					pGameObj->SetPos(*pGameObj->GetPos() + (vToObject / fDist) * fRadiusGap);
			}
		}
	}
}

void CGameObjContainer::SetRenderList()//���� ����Ʈ ����
{
	m_setRenderList.clear();
	m_mapRenderObj.clear();
	m_vecViewObj.clear();

	for each(map< int, vector< CGameObj* >>::const_reference mr in m_mapObj)//�� ������Ʈ��ŭ �ݺ�
	{
		if (m_setPlayObj.find(mr.first) == m_setPlayObj.end())//������ ������ ���� ��� continue
			continue;

		for each(vector< CGameObj* >::const_reference vr in mr.second)
		{
			m_mapRenderObj.insert(make_pair(vr->GetPos()->y, vr));//��������Ʈ�� ����
			m_setRenderList.insert(vr->GetPos()->y);

			if (vr->GetTeam() == ETEAM_FRIEND || vr->GetTeam() == ETEAM_HERO)//�Ʊ��� ������ ���� ���
				m_vecViewObj.push_back(vr);//�������Ʈ���Ϳ� ����
		}
	}
}

