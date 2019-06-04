#pragma once

enum MapName//맵 이름
{
	EMAP_MENU,
	EMAP_NEOS
};

class CGameArea;

class CGameStage : public CFSM//FSM에서 상속
{
private:
	CGameArea* m_pGameArea;//game Area 생성

public:
	int m_iCurMap;//현재 맵 index
	int m_iNextMap;//다음 맵 index
	
public:
	CGameStage(void);
	virtual ~CGameStage(void);

	CGameArea* GetGameArea() { return m_pGameArea; }//GameArea 정보 불러오기

	void Load();

	void OnFrameMove( float fElapsedTime );//프레임 갱신
	void OnChangeArea( int iMap );//게임 Area 전환

public:
	static void OnBeginMenu( DWORD dwObj );
	static void OnEndMenu( DWORD dwObj );

	static void OnBeginNeos( DWORD dwObj );

};

