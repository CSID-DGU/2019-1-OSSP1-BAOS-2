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

void CFSM::AddState( int iState, const SFSMState& pState )//���� �߰�
{
	map< int, SFSMState >::iterator mit = m_mapState.find( iState );
	if( mit != m_mapState.end() )//�̹� ���� ���� ��� return
		return ;

	m_mapState.insert( make_pair( iState, pState ));//���µ��� ����� map�� �߰�
}

SFSMState* CFSM::GetState( int iState )//���� �ҷ�����
{
	map< int, SFSMState >::iterator mit = m_mapState.find( iState );//mapState itorator ����
	if( mit == m_mapState.end() )//ã�� ������ ��� NULL return
		return NULL;

	return &mit->second;
}

bool CFSM::OnChangeState( int iState, bool bReserve )//���� ��ȯ
{
	m_pNextState = GetState( iState );//���� ���� �ҷ���
	if( m_pNextState == NULL )//���� ���°� ���� ��� false return
		return false; 

	if( bReserve == false )
		OnChangeReserveState();

	return true;//���� ��ȯ ����
}

void CFSM::OnChangeReserveState()//
{
	if( m_pNextState == NULL )//���� ���°� ���� ��� ����
		return ;

	if( m_pCurState != NULL && m_pCurState->m_pfEnd != NULL )//���� ���°� ������ ���
		( m_pCurState->m_pfEnd )( m_pCurState->m_dwArgs );//���� ������ ���� ����Ű�� ������ ��ȯ  

	m_pCurState = m_pNextState;//���� ���¸� ���� ���·� ��ȯ
	m_pNextState = NULL;

	if( m_pCurState->m_pfBegin != NULL )
		( m_pCurState->m_pfBegin )( m_pCurState->m_dwArgs );
}

void CFSM::OnUpdateState( float fElapsedTime )//���� ���� ����
{
	if( m_pCurState != NULL && m_pCurState->m_pfUpdate != NULL )//�� ���°� �����ϰ� ������Ʈ�� ���°� ������ ���
		( m_pCurState->m_pfUpdate )( m_pCurState->m_dwArgs, fElapsedTime );//���� ���� ������Ʈ
}