#pragma once

enum MapName
{
	EMAP_MENU,
	EMAP_NEOS
};

class CGameArea : public CFSM {
public:
	CGameArea(int x=0) : info(x){}
	~CGameArea(){}

	int info;
	void OnFrameMove(float fElapsedTime);

	friend class CGameStage;
};

class CGameStage : public CFSM
{
private:
	CGameArea* m_pGameArea;

public:
	int m_iCurMap;
	int m_iNextMap;
	
public:
	CGameStage(void);
	virtual ~CGameStage(void);

	CGameArea* GetGameArea() { return m_pGameArea; }

	void Load();

	void OnFrameMove( float fElapsedTime );
	void OnChangeArea( int iMap );

public:
	static void OnBeginMenu( DWORD dwObj );
	static void OnEndMenu( DWORD dwObj );

	static void OnBeginNeos( DWORD dwObj );

	friend class CGameArea;
};

