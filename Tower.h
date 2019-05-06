#pragma once

class CTower : public CAniObj
{
public:
	CTower(void);
	virtual ~CTower(void);

	virtual void Load( wstring wFile );
	virtual void OnFrameMove( float fElapsedTime );
	virtual void OnDamage( int iDamage );
};

