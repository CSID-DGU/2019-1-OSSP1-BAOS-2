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

void CUIMgr::WorkUIMessage(int iMsg)//ui가 시작한다는 메세지 클래스
{
	switch (iMsg)//imsg의 값에 따라 게임 시작과 끝을 나타낸다. 
	{
	case UI_START:
	{
		//	g_pGameObjMgr->UILoad( UI_NULL, L"Loading", L"Loading", D3DXVECTOR2( 0, 0 ), false, true );
		g_pStage->OnChangeState(EMAP_NEOS);
		break;
	}
	case UI_EXIT:
	{
		exit(0);
		break;
	}
	}
}

void CUIMgr::AutoMeesage(int iMsg, CUI* pUIObj)
{
	switch (iMsg)
	{
	case UI_MINIDOT://미니맵 점들의 위치 설정
	{
		if (pUIObj->GetObj()->IsDestroy() || pUIObj->GetObj()->IsWork() == false)
			pUIObj->Destroy();

		D3DXVECTOR2 m_vPos = *pUIObj->GetObj()->GetPos() / 8;
		m_vPos += D3DXVECTOR2(768, 512);

		pUIObj->SetPos(m_vPos - D3DXVECTOR2(4, 4));

	}

	break;

	case UI_MOUSE://마우스 ui
	{
		pUIObj->SetPos(g_pMouse->GetWorldMousePos());//마우스의 위치 잡는다

		CGameObj* pTarget = g_pGameObjMgr->OnFindTarget(pUIObj, g_pGameObjMgr->m_setPlayObj, 300);

		bool bFind = false;

		if (pTarget != nullptr)//타겟이 있을경우
		{
			bFind = CUtil::Object_Mouse_Collision(pTarget, g_pMouse->GetWorldMousePos());//타겟과 마우스위치가 같을경우
			if (bFind == true)
				g_pMouse->SetTarget(pTarget);
			else
				g_pMouse->SetTarget(nullptr);
		}


		if (bFind)//타겟을 잡았을 경우 공격
			pUIObj->OnChangeAni(AT_ATTACK);
		else
			pUIObj->OnChangeAni(AT_NORMAL);

		pTarget = NULL;
	}
	break;
	}
}