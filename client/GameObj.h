#pragma once

enum EGAME_TEAM
{
	ETEAM_HERO,
	ETEAM_FRIEND,
	ETEAM_ENEMY,
	ETEAM_NENUTAL
};

enum EGAME_RENDER
{
	ERENDER_NORMAL,
	ERENDER_DIRECTION,
	ERENDER_UI
};

class CRender;

class CGameObj : public CICameraObj
{
protected:
	CRender* m_pRender;

	CGameObj* m_pDamager;

	wstring m_wObjName;

	D3DXVECTOR2 m_vPos;
	D3DXVECTOR2 m_vGoalPos;

	D3DXVECTOR2 m_vDirectionVector;

	D3DXVECTOR2 m_vScl;
	D3DXVECTOR2 m_vImgSize;

	vector< int > m_vecTextureID;

	bool m_bDestroy;
	bool m_bWork;

	int m_iRenderType;
	
	float m_fSpeed;

	int m_iDirection;

	int m_iDamage;
	
	int m_iScope;
	int m_iRadius;

	int m_iCriticalDamage;
	int m_iCritiaclChance;

	int m_iMaxHealth;
	int m_iMaxMana;

	int m_iHealth;

	int m_iMana;

	int m_iTeam;

public:
	CGameObj(void);
	virtual ~CGameObj(void);

	virtual const D3DXVECTOR2* GetPos() { return &m_vPos; }
	virtual void SetPos( D3DXVECTOR2 vPos ) { m_vPos = vPos; }

	const D3DXVECTOR2 * GetScl() { return &m_vScl; }
	void SetScl( D3DXVECTOR2 vScl ) { m_vScl = vScl; }

	const D3DXVECTOR2* GetDirectionVector() { return &m_vDirectionVector; }
	void SetDirectionVector( D3DXVECTOR2 vDirectionVector ) { m_vDirectionVector = vDirectionVector; }

	const D3DXVECTOR2 * GetImgSize() { return &m_vImgSize; }
	void SetImgSize( D3DXVECTOR2 vImgSize )  { m_vImgSize = vImgSize; }

	const D3DXVECTOR2 * GetGoalPos() { return &m_vGoalPos; }
	void SetGoalPos( D3DXVECTOR2 vGoalPos ) { m_vGoalPos = vGoalPos; }

	const wstring GetObjName() { return m_wObjName; }
	void SetObjName( wstring wObjName ) { m_wObjName  = wObjName; }

	CRender* GetRender() { return m_pRender; }

	CGameObj* GetDamager() { return m_pDamager; }

	vector< int > GetTextureID() { return m_vecTextureID; }
	void SetTextureID( vector< int > vecTextureID ) { m_vecTextureID = vecTextureID; }

	bool IsDestroy() { return m_bDestroy; }
	void Destroy() { m_bDestroy = true ; }

	int GetRenderType() { return m_iRenderType ; }
	void SetRenderType( int iRenderType ) { m_iRenderType = iRenderType; }
	
	bool IsWork() { return m_bWork; }
	void SetWork( bool bWork ) { m_bWork = bWork; }

	int GetMaxHealth() { return m_iMaxHealth; }
	void SetMaxHealth( int iMaxHealth ) { m_iMaxHealth = iMaxHealth; }

	int GetMaxMana() { return m_iMaxMana; }
	void SetMacMana( int iMaxMana ) { m_iMaxMana = iMaxMana;}
	
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed( float fSpeed ) { m_fSpeed = fSpeed; }

	int GetDamage() { return m_iDamage; }
	void SetDamage( int iDamage ) { m_iDamage = iDamage; }

	int GetScope() { return m_iScope; }
	void SetScope( int iScope ) { m_iScope = iScope; }

	int GetRadius() { return m_iRadius; }
	void SetRadius( int iRadius ) { m_iRadius = iRadius; }

	int GetDirection() { return m_iDirection; }
	void SetDirection( int iDirection ) { m_iDirection = iDirection; }

	int GetHealth() { return m_iHealth; }
	void SetHealth( int iHealth ) { m_iHealth = iHealth; }

	int GetMana() { return m_iMana; }
	void SetMana( int iMana ) { m_iMana = iMana; }

	int GetTeam() { return m_iTeam ; }
	void SetTeam( int iTeam ) { m_iTeam = iTeam; }

public:
	void OnAttack() {}
	virtual void OnDamage( int iDamage, CGameObj* pGameObj ) {}

public:
	virtual void Load( wstring wFile ) {};
	virtual void UnLoad();

	virtual void OnFrameMove( float fElapsedTime );
	virtual void OnFrameRender();
	
};