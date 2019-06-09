#pragma once

class CEffect : public CAniObj//effect class
{
private:
	CGameObj* m_pTarget;//Ÿ�� ������Ʈ ����

public:
	CEffect(void);
	virtual ~CEffect(void);

	CGameObj* GetTarget() { return m_pTarget; }
	void SetTarget( CGameObj* pTarget )  { m_pTarget = pTarget; }

	virtual void Load( wstring wFile );
	virtual void OnFrameMove( float fElpasedTime );

	virtual void OnEndAni();
};

