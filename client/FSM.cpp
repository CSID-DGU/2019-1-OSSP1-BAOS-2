#include "DXUT.h"
#include "Home.h"


CFSM::CFSM(void):
m_pCurState( NULL ),
	m_pNextState( NULL )
{
}


CFSM::~CFSM(void)
{
}

void CFSM::AddState( int iState, const SFSMState& pState )//상태 추가
{
	map< int, SFSMState >::iterator mit = m_mapState.find( iState );
	if( mit != m_mapState.end() )//이미 상태 있을 경우 return
		return ;

	m_mapState.insert( make_pair( iState, pState ));//상태들이 저장된 map에 추가
}

SFSMState* CFSM::GetState( int iState )//상태 불러오기
{
	map< int, SFSMState >::iterator mit = m_mapState.find( iState );//mapState itorator 설정
	if( mit == m_mapState.end() )//찾지 못했을 경우 NULL return
		return NULL;

	return &mit->second;
}

bool CFSM::OnChangeState( int iState, bool bReserve )//상태 전환
{
	m_pNextState = GetState( iState );//다음 상태 불러옴
	if( m_pNextState == NULL )//다음 상태가 없을 경우 false return
		return false; 

	if( bReserve == false )
		OnChangeReserveState();

	return true;//상태 전환 성공
}

void CFSM::OnChangeReserveState()//
{
	if( m_pNextState == NULL )//다음 상태가 없는 경우 종료
		return ;

	if( m_pCurState != NULL && m_pCurState->m_pfEnd != NULL )//현재 상태가 존재할 경우
		( m_pCurState->m_pfEnd )( m_pCurState->m_dwArgs );//현재 상태의 끝을 가리키는 쪽으로 전환  

	m_pCurState = m_pNextState;//현재 상태를 다음 상태로 전환
	m_pNextState = NULL;

	if( m_pCurState->m_pfBegin != NULL )
		( m_pCurState->m_pfBegin )( m_pCurState->m_dwArgs );
}

void CFSM::OnUpdateState( float fElapsedTime )//현재 상태 갱신
{
	if( m_pCurState != NULL && m_pCurState->m_pfUpdate != NULL )//현 상태가 존재하고 업데이트할 상태가 존재할 경우
		( m_pCurState->m_pfUpdate )( m_pCurState->m_dwArgs, fElapsedTime );//현재 상태 없데이트
}