#pragma once

enum MapName//�� �̸�
{
	EMAP_MENU,
	EMAP_NEOS
};

class CGameArea;

class CGameStage : public CFSM//FSM���� ���
{
private:
	CGameArea* m_pGameArea;//game Area ����

public:
	int m_iCurMap;//���� �� index
	int m_iNextMap;//���� �� index
	
public:
	CGameStage(void);
	virtual ~CGameStage(void);

	CGameArea* GetGameArea() { return m_pGameArea; }//GameArea ���� �ҷ�����

	void Load();

	void OnFrameMove( float fElapsedTime );//������ ����
	void OnChangeArea( int iMap );//���� Area ��ȯ

public:
	static void OnBeginMenu( DWORD dwObj );
	static void OnEndMenu( DWORD dwObj );

	static void OnBeginNeos( DWORD dwObj );

};

