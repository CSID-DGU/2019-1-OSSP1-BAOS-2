#pragma once

struct SAniData
{
	//애니메이션 데이터 저장시킬 구조체
	wstring m_wFile;

	void Load( wstring wAni, wstring wFile );
};

struct SAniObjData//애니메이션 오브젝트 데이터 구조체
{
	wstring m_wFile;

	D3DXVECTOR2 m_vScale;

	//체력 최대치, 마나 최대치, 현재 체력과 마나, 입은 데미지와 범위, 스피드 설정
	int m_iMaxHealth;
	int m_iMaxMana;

	int m_iHealth;
	int m_iMana;

	int m_iDamage;

	int m_iScope;
	int m_iRadius;

	float m_fSpeed;
	
	map< int, SAniData > m_mapAni;

	SAniObjData()://애니 오브젝트의 초기 데이터 설정
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

class CGameObjPool//게임 오브젝트 풀 클래스
{
	//오브젝트와 애니메이션을 미리 로드
private:
	map< wstring, SAniObjData > m_mapAniObj;
	map< wstring, SObjData > m_mapObj;
public:
	CGameObjPool( void );
	virtual ~CGameObjPool( void );

	void LoadAniObj( wstring wID, wstring wFile );
	void LoadObj( wstring wID, wstring wFile );

	const SAniObjData* GetAniObjData( wstring wFile );
	const SObjData* GetObjData( wstring wFile );

};