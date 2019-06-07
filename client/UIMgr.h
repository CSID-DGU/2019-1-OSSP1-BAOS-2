#pragma once

class CUIMgr
{
public:
	CUIMgr(void);
	virtual ~CUIMgr(void);

	void WorkUIMessage( int iMsg );
	void AutoMeesage( int iMsg, CUI* pUIObj );
};

