#pragma once

class CTile : public CGameObj
{
public:
	CTile(void);
	virtual ~CTile(void);

	virtual void Load( wstring wFile );
};

 