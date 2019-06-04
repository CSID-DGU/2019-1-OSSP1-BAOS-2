#pragma once

struct SFSMState//FSM ���� ����� ����ü
{
	//������ ���� �Լ� Ÿ��ȭ 
	typedef void (*PFBEGIN)(DWORD);//
	typedef void (*PFUPDATE)(DWORD , float );//������Ʈ
	typedef void (*PFEND)(DWORD);//���� �װų� ���� ����

	//���º� ����ü ����
	PFBEGIN m_pfBegin;//ó�� ���� 
	PFUPDATE m_pfUpdate;//������Ʈ ����
	PFEND m_pfEnd;//���� ����

	DWORD m_dwArgs;

	SFSMState( DWORD dwArgs, PFBEGIN pfBegin, PFUPDATE pfUpdate, PFEND pfEnd )://�ʱ�ȭ �κ�
	m_dwArgs( dwArgs ),
		m_pfBegin( pfBegin ),
		m_pfUpdate( pfUpdate ),
		m_pfEnd( pfEnd )
	{
	}
};

class CFSM
{
private:
	map< int, SFSMState > m_mapState;//�� ���� map�ڷᱸ���� ����
protected:
	SFSMState* m_pCurState;//������� FSM
	SFSMState* m_pNextState;//�������� FSM
public:
	CFSM(void);
	virtual ~CFSM(void);

	void AddState( int iState, const SFSMState& pState );//���� �߰�
	SFSMState* GetState( int iState );//���� ���� �ҷ�����

	bool CFSM::OnChangeState( int iState, bool bReserve = true );
	void OnChangeReserveState();//����� ���� ��ȯ

	void OnUpdateState( float fElapsedTime );//���� ������Ʈ
};

