#include "DXUT.h"
#include "Home.h"


CGameArea::CGameArea( CGameStage* pGameStage )://gameArea Ŭ���� ����
m_pGameStage( pGameStage ),
	m_iNextArea( -1 )//���� Area �ε��� -1�� �ʱ�ȭ
{
}


CGameArea::~CGameArea(void)
{
}

