#include "DXUT.h"
#include "Home.h"

extern CGameObjMgr* g_pGameObjMgr;
extern GameDataMgr* g_pGameDataMgr;
extern CTexture* g_pTexture;

CDark::CDark(void) ://Dark 클래스에 있는 변수 초기화
	m_iViewID(0),
	m_fDarkUpdateTimer(0.0f),
	m_fDarkResetTimer(GameSettingIndex::UpdateDarkResetTime)
{
}


CDark::~CDark(void)//소멸자
{
}

void CDark::Load(wstring wFile)
{
	if (m_pRender != NULL)//Render할 것이 있는경우
		return;

	const SObjData* pObjData = g_pGameDataMgr->GetObjData(wFile);//wFile이름의 오브젝트 데이터 정보 불러옴
	if (pObjData == NULL)//오브젝트 데이터를 못불러왔을경우
		return;

	if (m_wObjName == L"Dark")//오브젝트 이름이 Dark인경우
	{
		m_vScl = pObjData->m_vScale;
		m_pRender = new CDarkRender(this);//Dark Render 생성
	}

	if (m_wObjName == L"MiniDark")//오브젝트가 미니맵인경우
	{
		m_vPos += D3DXVECTOR2(768, 512);//위치에서 기준만큼 오브젝트 위치 이동
		m_vScl = m_vScl * 2;//스케일 설정
		m_pRender = new CDarkRender(this);
		m_bCamera = false;
	}

	m_pRender->Load(pObjData->m_wFile);//wFile의 오브젝트 데이터를 로드
	m_iViewID = g_pTexture->Load(L"Image/UI/View/CreatureView (0).png");//viewID를 이미지 위치에서 로드
}

void CDark::ResetDark()//Dark reset
{
	m_fDarkResetTimer = GameSettingIndex::UpdateDarkResetTime;//Dark resetTime 설정
	((CDarkRender*)m_pRender)->ClearDark();
}

void CDark::UpdateDark()//Dark Update
{
	m_fDarkUpdateTimer = GameSettingIndex::UpdateDarkTime;//Dark updatetime 설정
	vector< CGameObj* > m_vecViewObj = g_pGameObjMgr->GetViewObj();//게임 view 오브젝트 정보를 게임오브젝트매니저에서 불러옴
	if (m_vecViewObj.empty() == false)//비어있지 않을 경우
	{
		for (int i = 0; i <= (int)m_vecViewObj.size() - 1; ++i)
		{
			if (m_vecViewObj[i]->IsDestroy() == false)//제거되지 않았을 경우
			{
				D3DXVECTOR2 vViewPos = *m_vecViewObj[i]->GetPos() / 16;//view 위치 지정
				((CDarkRender*)m_pRender)->SetDarkMode(vViewPos, m_iViewID);
			}
		}
	}
}


void CDark::OnFrameMove(float fElapsedTime)//프레임 갱신
{
	if (m_pRender != NULL)//렌더가 할 것이 있을경우
		m_pRender->OnFrameMove(fElapsedTime);//프레임 갱신

	if (m_pRender == nullptr)
		return;

	m_fDarkUpdateTimer -= fElapsedTime;//업데이트 타이머에서 현재시간 갱신
	m_fDarkResetTimer -= fElapsedTime;//리셋 타이머에서 현재시간 갱신 

	if (m_fDarkResetTimer <= 0.0f)//리셋타이머가 0이하일 경우 
	{
		ResetDark();//게임 리셋후 다시 업데이트
		UpdateDark();
	}

	if (m_fDarkUpdateTimer <= 0.0f)
	{
		UpdateDark();//게임 업데이트
	}
}