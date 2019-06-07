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

bool CAniEvent::Load( wstring wFile, int iIndex )//wFile�̸��� iIndex�� ���� �ε� Ȯ��
{
	wstringstream strApp;
	strApp << L"Evt" << iIndex + 1;

	int iImgIndex = GetPrivateProfileInt( strApp.str().c_str(), L"ImgIndex", -1, wFile.c_str() );//�̹��� index
	if( iImgIndex == -1 )//�޾ƿ��� ������ ���
		return false;

	SAniEventData sData;//Data �޾ƿ���
	sData.m_iType = GetPrivateProfileInt( strApp.str().c_str(), L"Type", -1, wFile.c_str() );

	for( int i=1; ; i++ )
	{
		wstringstream strKey;
		strKey<< L"TextParam" << i;

		WCHAR wcParam[MAX_PATH];//�ؽ�Ʈ ���� �迭
		GetPrivateProfileString( strApp.str().c_str(), strKey.str().c_str(), L"", wcParam, MAX_PATH, wFile.c_str() );//�ؽ�Ʈ ������ ����

		if( wcslen( wcParam ) == 0 )//���� �޾ƿ���
			break;

		sData.m_vecTextParam.push_back( wcParam );
	}

	for( int i=0; ; ++i )
	{
		wstringstream strKey;//Ű ó�� stringstream
		strKey << L"IntParam" << i;

		int iParam = GetPrivateProfileInt( strApp.str().c_str(), strKey.str().c_str(), -1, wFile.c_str() );
		if( iParam == -1 )//���޾��� ���
			break;

		sData.m_vecIntParam.push_back( iParam );
	}

	m_mapData[iImgIndex].push_back( sData );

	return true;
}

void CAniEvent::OnEvent( CAniObj* pAniObj, int iIndex )//event
{
	map< int, vector< SAniEventData >>::iterator mit = m_mapData.find( iIndex );//iIndex�� �´� ������ iterator�� ����
	if( mit == m_mapData.end() )//�� ã���� ���
		return ;

	OnEvent( pAniObj, mit->second );//event ����
}

void CAniEvent::OnEvent( CAniObj* pAniObj, const vector< SAniEventData >& vecEvent )//
{
	if( m_pfEventFunc == NULL )//Data�� ���� ���
		return ;

	for( int i= 0; i < (int)vecEvent.size(); ++i )//�����Ͱ� ����� ������ �����ŭ �ݺ�
		m_pfEventFunc( pAniObj, vecEvent[i] );//�̺�Ʈ ����
}