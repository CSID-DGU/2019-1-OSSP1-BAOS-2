#pragma once

struct SAniData//�ִ� ������ ����ü
{
	wstring m_wFile;

	void Load( wstring wAni, wstring wFile );
};

struct SAniObjData//�ִ� ������Ʈ ������ ����ü
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
	
	map< int, SAniData > m_mapAni;//�ִϵ����� ���� �� �ڷᱸ��

	SAniObjData()://������Ʈ ������ �ʱ�ȭ
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

struct SObjData//������Ʈ ������ ����ü
{
	wstring m_wFile;
	D3DXVECTOR2 m_vScale;

	void Load( wstring wFile );
};

class GameDataMgr//���� ������ ���� Ŭ����
{
private:
	map< wstring, SAniObjData > m_mapAniObj;//������Ʈ�� �ִϿ�����Ʈ ����
	map< wstring, SObjData > m_mapObj;
public:
	GameDataMgr( void );
	virtual ~GameDataMgr( void );

	void LoadAniObj( wstring wID, wstring wFile );
	void LoadObj( wstring wID, wstring wFile );

	const SAniObjData* GetAniObjData( wstring wFile );
	const SObjData* GetObjData( wstring wFile );

};