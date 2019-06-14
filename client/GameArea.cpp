#include "DXUT.h"
#include "Home.h"


CGameArea::CGameArea( CGameStage* pGameStage )://gameArea 클래스 생성
m_pGameStage( pGameStage ),
	m_iNextArea( -1 )//다음 Area 인덱스 -1로 초기화
{
}


CGameArea::~CGameArea(void)
{
}

