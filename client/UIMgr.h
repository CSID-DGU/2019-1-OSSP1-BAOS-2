#pragma once

class CUIMgr//ui���� Ŭ����
{
public:
	CUIMgr(void);
	virtual ~CUIMgr(void);

	void WorkUIMessage( int iMsg );
	void AutoMeesage( int iMsg, CUI* pUIObj );
};

