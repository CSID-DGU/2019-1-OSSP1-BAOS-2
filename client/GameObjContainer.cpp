#include "DXUT.h"
#include "Home.h"

extern CTexture* g_pTexture;
extern CGameTileMgr* g_pGameTileMgr;

CGameObjContainer::CGameObjContainer(void)//게임오브젝트 컨테이너 생성자
{
	//플레이오브젝트에 플레이어, 크리쳐, 타워 삽입
	m_setPlayObj.insert(EGAMEOBJ_PLAYER), m_setPlayObj.insert(EGAMEOBJ_CREATURE), m_setPlayObj.insert(EGAMEOBJ_TOWER);
}


CGameObjContainer::~CGameObjContainer(void)
{
	//게임오브젝트 컨테이너에 들어있는 게임오브젝트들을 모두 제거해줌
	for each(map< int, vector< CGameObj* >>::const_reference mr in m_mapObj)
		for each(vector<CGameObj*>::const_reference vr in mr.second)
			delete vr;

	m_mapObj.clear();//맵오브젝트 클리어
}

CUI* CGameObjContainer::UILoad(int iUIType, wstring wFile, wstring wName, D3DXVECTOR2 vPos, bool bAni, bool bWork)
{
	//vpos위치에 ani, work인 상태인 IUIType, wFile, wName인 오브젝트를 로드
	CUI* pUIObj = new CUI;
	if (pUIObj == NULL)
		return NULL;

	//새로운 UI오브젝트 생성 후 mapReserveObj에 저장
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
	//받아온 위치에 찾는 데이터가 있으면 로드하고 미리 가지고 있는 오브젝트 맵에 저장
	CGameObj* pObj = Alloc(iType);//iType이 있으면 할당, 없으면 NULL 리턴
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
	//iType 형태인 wName오브젝트 삭제 
	for each(vector< CGameObj* >::const_reference vr in m_mapObj[iType])
	{
		if (vr->GetObjName() == wName)
			vr->Destroy();
	}
}

void CGameObjContainer::PostProcess()
{
	// 예약된것을을 m_mapObj에 등록한다.
	for each(map<int, vector<CGameObj*>>::const_reference mr in m_mapReserveObj)
	{
		vector<CGameObj*>& vecObj = m_mapObj[mr.first];
		vecObj.insert(vecObj.end(), mr.second.begin(), mr.second.end());
	}

	m_mapReserveObj.clear();

	// 삭제될것을 처리
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
	//적을 목표로 잡기
	CGameObj* pTarget = NULL;
	int fMinDist = fLimitDist;

	for each(map< int, vector< CGameObj* >>::const_reference mr in m_mapObj)//맵오브젝트에 있는 
	{
		if (setType.find(mr.first) == setType.end())
			continue;

		for each(vector< CGameObj* >::const_reference vr in mr.second)
		{
			if (vr == pGameObj || vr->GetTeam() == pGameObj->GetTeam())//vr자체가 게임오브젝트거나 같은 팀일 경우 continue
				continue;

			if (vr->IsDestroy() == true || vr->GetAniCategory() == AT_DIE)//vr이 죽었을 경우
				continue;

			float fDist = CUtil::CalcDist(pGameObj, vr);//vr과 피게임오브젝트 사이의 거리

			if (fMinDist > fDist)//위의 fDist를 이용해서 목표물과 최소 거리 갱신
			{
				fMinDist = (int)fDist;
				pTarget = vr;
			}
		}
	}

	return pTarget;//타겟 리턴
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
			//피게임오브젝트와 vr의 거리가 두 오브젝트의 반지름보다 크면 멀리 떨어지 있는것
			//두 반지름의 합보다 작으면 두 오브젝트는 공격범위 내에 있다. 


			if (fRadiusGap >= 0.0f)//거리가 공격범위 내에 있지 않으므로 오브젝트 상태를 수정해야한다.
			{
				if (((CAniObj*)pGameObj)->GetAniCategory() != AT_ATTACK)//공격상태가 아닐경우
					((CAniObj*)pGameObj)->GetController()->SetEnemy(NULL);//적 설정 초기화

				if (((CAniObj*)vr)->GetAniCategory() != AT_ATTACK)
					((CAniObj*)vr)->GetController()->SetEnemy(NULL);

				if (((CAniObj*)pGameObj)->GetAniCategory() == AT_ATTACK)//공격상태인 경우
				{
					((CAniObj*)pGameObj)->GetController()->FindNode();//노드를 탐색.
					return;
				}
				else
				{
					//pGameObj->SetGoalPos( NULLVECTOR2 );
					//(( CAniObj* )pGameObj)->GetController()->FindNode();
				}

				if (fDist != 0 && vToObject != 0)//두 오브젝트가 똑같은 위치에 있지 않을 경우 게임오브젝트의 위치 갱신
					pGameObj->SetPos(*pGameObj->GetPos() + (vToObject / fDist) * fRadiusGap);
			}
		}
	}
}

void CGameObjContainer::SetRenderList()//렌더 리스트 설정
{
	m_setRenderList.clear();
	m_mapRenderObj.clear();
	m_vecViewObj.clear();

	for each(map< int, vector< CGameObj* >>::const_reference mr in m_mapObj)//맵 오브젝트만큼 반복
	{
		if (m_setPlayObj.find(mr.first) == m_setPlayObj.end())//진행할 내용이 없을 경우 continue
			continue;

		for each(vector< CGameObj* >::const_reference vr in mr.second)
		{
			m_mapRenderObj.insert(make_pair(vr->GetPos()->y, vr));//렌더리스트에 저장
			m_setRenderList.insert(vr->GetPos()->y);

			if (vr->GetTeam() == ETEAM_FRIEND || vr->GetTeam() == ETEAM_HERO)//아군과 영웅이 팀일 경우
				m_vecViewObj.push_back(vr);//뷰오브젝트벡터에 저장
		}
	}
}

