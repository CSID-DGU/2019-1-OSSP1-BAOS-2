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
	case UI_START:												// UI_START ��� �޼����� �޾��� ��� (������ �����ϴ� case)
		{														// Loading UI ������Ʈ�� Load�Ѵ�.
			g_pGameObjMgr->UILoad( UI_NULL, L"Loading", L"Loading", D3DXVECTOR2( 0, 0 ), false, true );
			g_pStage->OnChangeState( EMAP_NEOS );				// ���������� Loading UI ������Ʈ�� Load �ߴٸ�,
																// �� UI�� �ҷ����� ���� �غ� �Ѵ�. EMAP_NEOS flag = true;
			break;
		}
	case UI_EXIT:												// UI_EXIT ��� �޼����� �޾��� ��� (������ ����Ǵ� case)
		{
			exit( 0 );											// ���α׷��� �����Ѵ�.
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
			if( pUIObj->GetObj()->IsDestroy() || pUIObj->GetObj()->IsWork() == false )	// UI ������Ʈ�� release �ưų� ���� �۵����� ���� ���
				pUIObj->Destroy();														// UI ������Ʈ�� destroy �ϰڴٰ� �÷��׸� true�� ������ָ�,
																						// ���� CGameStage Ŭ������ End_Menu �Լ����� release �� ���̴�.
			D3DXVECTOR2 m_vPos = *pUIObj->GetObj()->GetPos() / 8;						
			m_vPos += D3DXVECTOR2( 768, 512 );

			pUIObj->SetPos( m_vPos - D3DXVECTOR2( 4, 4 ) );
		
		}
		
		break;

	case UI_MOUSE:
		{
			pUIObj->SetPos( g_pMouse->GetWorldMousePos() );								// ���콺 ��ġ�� �޾ƿ� UI������Ʈ�� ��ġ�� �������ش�.
																						// �ش� ��ġ�� �ٸ� ������Ʈ�� �ִ��� map���� �˻��Ѵ�.
			CGameObj* pTarget = g_pGameObjMgr->OnFindTarget( pUIObj, g_pGameObjMgr->m_setPlayObj, 300 );

			bool bFind = false;

			/* 
			����ڰ� ���콺�� Ŭ���� ��ġ�� �̵� UI�� ���������ϱ� ������
			�ش� ��ġ�� � �ٸ� ������Ʈ�� �ִٸ� �� ������Ʈ�� �ִ� ��ġ���� ��¦ �ٸ� ��ġ�� 
			�̵� UI�� ���������ϴ� ����� �����ؾ��Ѵ�. (������Ʈ�� ��ĥ �� �ִ��� �׽�Ʈ �غ����ҵ�)
				###  TODO  ###
				�� ����� ����ϴ� �Լ��� �����.
				�Լ��� ������ �κп��� bfind ���� �������ִ� ���ο� ���ǹ��� �־���Ѵ�.
					�ش� ��ġ�� ������Ʈ�� ���� ==> bfind = true
					�ش� ��ġ�� ������Ʈ�� ���� ==> bfind = false */

			if( bFind )											// �ش� ��ġ�� ������Ʈ�� �ִٸ�
				pUIObj->OnChangeAni( AT_ATTACK );				// ���ݿ� ��ġ UI ������Ʈ(������)�� �ִϸ��̼��� �ٲ۴�.
			else												// �ش� ��ġ�� ������Ʈ�� ���ٸ� (��, ���̶��)
				pUIObj->OnChangeAni( AT_NORMAL );				// �Ϲ� ��ġ UI ������Ʈ(�Ķ���)�� �ִϸ��̼��� �ٲ۴�.

			pTarget = NULL;										// ���� ���콺 �Է��� ���� �ʱ�ȭ�� ���ش�.
		}
		break;
	}
}