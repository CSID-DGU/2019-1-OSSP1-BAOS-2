#pragma once

class CUIMgr//ui관리 클래스
{
public:
	CUIMgr(void);
	virtual ~CUIMgr(void);

	void WorkUIMessage( int iMsg );
	void AutoMeesage( int iMsg, CUI* pUIObj );
};

