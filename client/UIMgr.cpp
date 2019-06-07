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

void CUIMgr::WorkUIMessage(int iMsg)//ui�� �����Ѵٴ� �޼��� Ŭ����
{
	switch (iMsg)//imsg�� ���� ���� ���� ���۰� ���� ��Ÿ����. 
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
	case UI_MINIDOT://�̴ϸ� ������ ��ġ ����
	{
		if (pUIObj->GetObj()->IsDestroy() || pUIObj->GetObj()->IsWork() == false)
			pUIObj->Destroy();

		D3DXVECTOR2 m_vPos = *pUIObj->GetObj()->GetPos() / 8;
		m_vPos += D3DXVECTOR2(768, 512);

		pUIObj->SetPos(m_vPos - D3DXVECTOR2(4, 4));

	}

	break;

	case UI_MOUSE://���콺 ui
	{
		pUIObj->SetPos(g_pMouse->GetWorldMousePos());//���콺�� ��ġ ��´�

		CGameObj* pTarget = g_pGameObjMgr->OnFindTarget(pUIObj, g_pGameObjMgr->m_setPlayObj, 300);

		bool bFind = false;

		if (pTarget != nullptr)//Ÿ���� �������
		{
			bFind = CUtil::Object_Mouse_Collision(pTarget, g_pMouse->GetWorldMousePos());//Ÿ�ٰ� ���콺��ġ�� �������
			if (bFind == true)
				g_pMouse->SetTarget(pTarget);
			else
				g_pMouse->SetTarget(nullptr);
		}


		if (bFind)//Ÿ���� ����� ��� ����
			pUIObj->OnChangeAni(AT_ATTACK);
		else
			pUIObj->OnChangeAni(AT_NORMAL);

		pTarget = NULL;
	}
	break;
	}
}