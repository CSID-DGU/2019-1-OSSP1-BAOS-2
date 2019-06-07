#pragma once

struct SAniData//애니 데이터 구조체
{
	wstring m_wFile;

	void Load( wstring wAni, wstring wFile );
};

struct SAniObjData//애니 오브젝트 데이터 구조체
{
	wstring m_wFile;

	D3DXVECTOR2 m_vScale;

	int m_iMaxHealth;
	int m_iMaxMana;

	int m_iHealth;
	int m_iMana;

	int m_iDamage;

	int m_iScope;
	int m_iRadius;

	float m_fSpeed;
	
	map< int, SAniData > m_mapAni;//애니데이터 저장 맵 자료구조

	SAniObjData()://오브젝트 데이터 초기화
	m_vScale( 1.0f, 1.0f ),
		m_iMaxHealth( 0 ),
		m_iMaxMana( 0 ),
		m_iHealth( 0 ),
		m_iMana( 0),
		m_iDamage( 0 ),
		m_fSpeed( 0 ),
		m_iScope( 0 ),
		m_iRadius( 0 )
	{
	}

	void Load( wstring wFile );	
};

struct SObjData//오브젝트 데이터 구조체
{
	wstring m_wFile;
	D3DXVECTOR2 m_vScale;

	void Load( wstring wFile );
};

class GameDataMgr//게임 데이터 관리 클래스
{
private:
	map< wstring, SAniObjData > m_mapAniObj;//오브젝트와 애니오브젝트 관리
	map< wstring, SObjData > m_mapObj;
public:
	GameDataMgr( void );
	virtual ~GameDataMgr( void );

	void LoadAniObj( wstring wID, wstring wFile );
	void LoadObj( wstring wID, wstring wFile );

	const SAniObjData* GetAniObjData( wstring wFile );
	const SObjData* GetObjData( wstring wFile );

};