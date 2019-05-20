#include "DXUT.h"
#include "Home.h"

extern CMouse* g_pMouse;
extern CGameStage* g_pStage;
extern CGameObjMgr* g_pGameObjMgr;

CUIMgr::CUIMgr(void)
{
}


CUIMgr::~CUIMgr(void)
{
}

void CUIMgr::WorkUIMessage( int iMsg )
{
	switch( iMsg )
	{
	case UI_START:												// UI_START 라는 메세지를 받았을 경우 (게임이 시작하는 case)
		{														// Loading UI 오브젝트를 Load한다.
			g_pGameObjMgr->UILoad( UI_NULL, L"Loading", L"Loading", D3DXVECTOR2( 0, 0 ), false, true );
			g_pStage->OnChangeState( EMAP_NEOS );				// 성공적으로 Loading UI 오브젝트를 Load 했다면,
																// 맵 UI를 불러오기 위한 준비를 한다. EMAP_NEOS flag = true;
			break;
		}
	case UI_EXIT:												// UI_EXIT 라는 메세지를 받았을 경우 (게임이 종료되는 case)
		{
			exit( 0 );											// 프로그램을 종료한다.
			break;
		}
	}
}

void CUIMgr::AutoMessage( int iMsg, CUI* pUIObj )
{
	switch( iMsg )
	{
	case UI_MINIDOT :
		{
			if( pUIObj->GetObj()->IsDestroy() || pUIObj->GetObj()->IsWork() == false )	// UI 오브젝트가 release 됐거나 정상 작동하지 않을 경우
				pUIObj->Destroy();														// UI 오브젝트를 destroy 하겠다고 플래그를 true로 만들어주면,
																						// 이후 CGameStage 클래스의 End_Menu 함수에서 release 될 것이다.
			D3DXVECTOR2 m_vPos = *pUIObj->GetObj()->GetPos() / 8;						
			m_vPos += D3DXVECTOR2( 768, 512 );

			pUIObj->SetPos( m_vPos - D3DXVECTOR2( 4, 4 ) );
		
		}
		
		break;

	case UI_MOUSE:
		{
			pUIObj->SetPos( g_pMouse->GetWorldMousePos() );								// 마우스 위치를 받아와 UI오브젝트의 위치로 설정해준다.
																						// 해당 위치에 다른 오브젝트가 있는지 map에서 검사한다.
			CGameObj* pTarget = g_pGameObjMgr->OnFindTarget( pUIObj, g_pGameObjMgr->m_setPlayObj, 300 );

			bool bFind = false;

			/* 
			사용자가 마우스로 클릭한 위치에 이동 UI를 출력해줘야하기 떄문에
			해당 위치에 어떤 다른 오브젝트가 있다면 그 오브젝트가 있는 위치보다 살짝 다른 위치에 
			이동 UI를 출력해줘야하는 기능을 구현해야한다. (오브젝트를 겹칠 수 있는지 테스트 해봐야할듯)
				###  TODO  ###
				그 기능을 담당하는 함수를 만든다.
				함수의 마지막 부분에는 bfind 값을 변경해주는 새로운 조건문이 있어야한다.
					해당 위치에 오브젝트가 있음 ==> bfind = true
					해당 위치에 오브젝트가 없음 ==> bfind = false */

			if( bFind )											// 해당 위치에 오브젝트가 있다면
				pUIObj->OnChangeAni( AT_ATTACK );				// 공격용 위치 UI 오브젝트(빨간색)로 애니메이션을 바꾼다.
			else												// 해당 위치에 오브젝트가 없다면 (즉, 땅이라면)
				pUIObj->OnChangeAni( AT_NORMAL );				// 일반 위치 UI 오브젝트(파란색)로 애니메이션을 바꾼다.

			pTarget = NULL;										// 다음 마우스 입력을 위해 초기화를 해준다.
		}
		break;
	}
}