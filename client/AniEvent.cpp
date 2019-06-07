#include "DXUT.h"
#include "Home.h"

CAniEvent::PFONEVENT CAniEvent::m_pfEventFunc = NULL;

CAniEvent::CAniEvent(void)
{
}


CAniEvent::~CAniEvent(void)
{
}

void CAniEvent::Load( wstring wFile )//wFile 
{
	for( int i = 0; ; ++i )
	{
		if( Load( wFile, i ) == false )
			break; 
	}
}

bool CAniEvent::Load( wstring wFile, int iIndex )//wFile이름의 iIndex번 파일 로드 확인
{
	wstringstream strApp;
	strApp << L"Evt" << iIndex + 1;

	int iImgIndex = GetPrivateProfileInt( strApp.str().c_str(), L"ImgIndex", -1, wFile.c_str() );//이미지 index
	if( iImgIndex == -1 )//받아오지 못했을 경우
		return false;

	SAniEventData sData;//Data 받아오기
	sData.m_iType = GetPrivateProfileInt( strApp.str().c_str(), L"Type", -1, wFile.c_str() );

	for( int i=1; ; i++ )
	{
		wstringstream strKey;
		strKey<< L"TextParam" << i;

		WCHAR wcParam[MAX_PATH];//텍스트 저장 배열
		GetPrivateProfileString( strApp.str().c_str(), strKey.str().c_str(), L"", wcParam, MAX_PATH, wFile.c_str() );//텍스트 데이터 복사

		if( wcslen( wcParam ) == 0 )//변수 받아오기
			break;

		sData.m_vecTextParam.push_back( wcParam );
	}

	for( int i=0; ; ++i )
	{
		wstringstream strKey;//키 처리 stringstream
		strKey << L"IntParam" << i;

		int iParam = GetPrivateProfileInt( strApp.str().c_str(), strKey.str().c_str(), -1, wFile.c_str() );
		if( iParam == -1 )//못받았을 경우
			break;

		sData.m_vecIntParam.push_back( iParam );
	}

	m_mapData[iImgIndex].push_back( sData );

	return true;
}

void CAniEvent::OnEvent( CAniObj* pAniObj, int iIndex )//event
{
	map< int, vector< SAniEventData >>::iterator mit = m_mapData.find( iIndex );//iIndex에 맞는 데이터 iterator로 저장
	if( mit == m_mapData.end() )//못 찾았을 경우
		return ;

	OnEvent( pAniObj, mit->second );//event 실행
}

void CAniEvent::OnEvent( CAniObj* pAniObj, const vector< SAniEventData >& vecEvent )//
{
	if( m_pfEventFunc == NULL )//Data가 없는 경우
		return ;

	for( int i= 0; i < (int)vecEvent.size(); ++i )//데이터가 저장된 벡터의 사이즈만큼 반복
		m_pfEventFunc( pAniObj, vecEvent[i] );//이벤트 실행
}