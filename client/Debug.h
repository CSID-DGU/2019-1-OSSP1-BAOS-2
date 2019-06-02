#pragma once

class CDebug//디버그 내용 출력하기 위한 클래스
{

public:
	CDebug(void);
	virtual ~CDebug(void);

	void OnFrameMove( float fElapsedTime );
};

