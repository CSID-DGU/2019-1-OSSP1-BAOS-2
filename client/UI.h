#pragma once

class CUI : public CAniObj
{
private:
	CGameObj* m_pObj;

	bool m_bUse;
	bool m_bAni;
	
	int m_iUIType;

public:
	CUI(void);
	virtual ~CUI(void);

	bool IsAni() { return m_bAni; }
	void SetAni( bool bAni ) { m_bAni = bAni; }

	bool IsUse() { return m_bUse; }
	void SetUse( bool bUse ) { m_bUse = bUse; }

	void SetType( int iType ) { m_iUIType = iType; }
	int GetType() { return m_iUIType; }

	void SetObj( CGameObj* pObj ) { m_pObj = pObj; }
	CGameObj* GetObj() { return m_pObj; }

public:
	virtual void Load( wstring wFile );
	virtual void OnFrameMove( float fElapsedTime );
};

