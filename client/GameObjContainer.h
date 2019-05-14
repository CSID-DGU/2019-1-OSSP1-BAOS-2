#pragma once

class CGameObj; class CUI;

class CGameObjContainer
{
private:
	vector< CGameObj* > m_vecObj;

protected:
	map< int, vector< CGameObj* >>m_mapObj;
	map< int, vector< CGameObj* >>m_mapReserveObj;

	map< int, vector< CGameObj* >>m_mapUnWorkObj;

	multimap< float, CGameObj* > m_mapRenderObj;
	set< float > m_setRenderList;

	vector< CGameObj* > m_vecViewObj;

	virtual CGameObj* Alloc( int iType ) { return NULL; }
	void PostProcess();

public:
	CGameObjContainer(void);
	virtual ~CGameObjContainer(void);

	set< int > m_setPlayObj;
	
	void Destroy( int iType, wstring wName );

	void SetWork( int iType, wstring wName, bool bWork );
	void SetRenderList();

	vector< CGameObj* > GetViewObj() { return m_vecViewObj; }

	CGameObj* OnFindTarget( CGameObj* pGameObj, set< int >& setType, int fLimitDist );

	virtual CUI* UILoad( int iUIType, wstring wFile, wstring wName, D3DXVECTOR2 vPos, bool bAni, bool bWork );
	virtual CGameObj* CGameObjContainer::Load( int iType, int iTeam, wstring wFile, wstring wName, D3DXVECTOR2 vPos, int iDirection, int iRenderType, bool bWork );

	void NoneOverLap( CGameObj* pGameObj );
};

