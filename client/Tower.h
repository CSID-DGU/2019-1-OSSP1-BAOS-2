#pragma once

class CTower : public CAniObj//Aniobj ���
{
public:
	CTower(void);
	virtual ~CTower(void);

	virtual void OnDamage(int iDamage, CGameObj* pGameObj);
	virtual void Load( wstring wFile );
	virtual void OnFrameMove( float fElapsedTime );
};

