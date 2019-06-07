#pragma once

class CAniObj;

struct SAniEventData
{
	int m_iType;
	vector< wstring > m_vecTextParam;
	vector< int > m_vecIntParam;

	SAniEventData():
	m_iType( -1 )
	{
	}

	const wstring GetTextParam( int iIndex ) const//텍스트 변수 받아오기
	{
		if( iIndex < 0 || iIndex >= (int)m_vecTextParam.size() )//변수 사이즈가 없거나 잘못 받아왔을 경우
			return L"";

		return m_vecTextParam[iIndex].c_str();
	}

	int GetIntParam( int iIndex ) const//정수형 변수 받아오기
	{
		if( iIndex < 0 || iIndex >= (int)m_vecIntParam.size() )
			return 0;

		return m_vecIntParam[iIndex];
	}
};

class CAniEvent
{
private:
	map< int, vector< SAniEventData >> m_mapData;//map 자료구조로 Ani Event Data 저장

	bool Load( wstring wFile, int iIndex );
	
public:
	CAniEvent(void);
	virtual ~CAniEvent(void);

	void Load( wstring wFile );

	void OnEvent( CAniObj* pAniObj, int iIndex );
	void OnEvent( CAniObj* pAniObj, const vector< SAniEventData >& vecEvent );

	typedef void (*PFONEVENT )( CAniObj*, const SAniEventData& );
	static PFONEVENT m_pfEventFunc;
};

