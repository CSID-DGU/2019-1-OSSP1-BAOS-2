#pragma once

struct SFSMState//FSM 정보 저장용 구조체
{
	//다형성 위한 함수 타입화 
	typedef void (*PFBEGIN)(DWORD);//
	typedef void (*PFUPDATE)(DWORD , float );//업데이트
	typedef void (*PFEND)(DWORD);//몬스터 죽거나 게임 종료

	//상태별 구조체 형설
	PFBEGIN m_pfBegin;//처음 상태 
	PFUPDATE m_pfUpdate;//업데이트 상태
	PFEND m_pfEnd;//종료 상태

	DWORD m_dwArgs;

	SFSMState( DWORD dwArgs, PFBEGIN pfBegin, PFUPDATE pfUpdate, PFEND pfEnd )://초기화 부분
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
	map< int, SFSMState > m_mapState;//맵 상태 map자료구조에 저장
protected:
	SFSMState* m_pCurState;//현재상태 FSM
	SFSMState* m_pNextState;//다음상태 FSM
public:
	CFSM(void);
	virtual ~CFSM(void);

	void AddState( int iState, const SFSMState& pState );//상태 추가
	SFSMState* GetState( int iState );//상태 정보 불러오기

	bool CFSM::OnChangeState( int iState, bool bReserve = true );
	void OnChangeReserveState();//예약된 상태 전환

	void OnUpdateState( float fElapsedTime );//상태 업데이트
};

