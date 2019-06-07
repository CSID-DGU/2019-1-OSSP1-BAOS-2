#include "DXUT.h"
#include "Home.h"

extern GameDataMgr* g_pGameDataMgr;

CHealth::CHealth(void) ://플레이어 초기화
	m_pPlayer(nullptr)
{
}


CHealth::~CHealth(void)
{
}

void CHealth::Load(wstring wFile)
{
	if (m_pRender != NULL)
		return;

	const SObjData* pObjData = g_pGameDataMgr->GetObjData(wFile);//오브젝트데이터 정보 불러오기
	if (pObjData == NULL)
		return;

	m_pRender = new CImgRender(this);//Render 할당
	m_pRender->Load(pObjData->m_wFile);//오브젝트 데이터 Render
}

void CHealth::OnFrameMove(float fElapsedTime)//프레임 갱신
{
	__super::OnFrameMove(fElapsedTime);

	if (m_pPlayer != nullptr)
	{
		if (m_pPlayer->IsDestroy())//플레이어가 제거되었으면
		{
			Destroy();//제거
			m_vScl.x = 0.0f;
			return;
		}

		//플레이어 위치 받음
		m_vPos = *m_pPlayer->GetPos();
		m_vPos -= D3DXVECTOR2(22.5, 0);


		if (m_pPlayer->GetHealth() == m_pPlayer->GetMaxHealth())//체력이 이미 최대체력이면 return
			return;

		if (m_pPlayer->GetHealth() <= 0)//체력이 0이하면 
		{
			m_vScl.x = 0.0f;//스케일이 0
			return;
		}

		//스케일 설정
		//플레이어 체력/최대체력
		m_vScl.x = ((float)m_pPlayer->GetHealth() / (float)m_pPlayer->GetMaxHealth());
	}
}