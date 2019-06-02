#include "DXUT.h"
#include "Home.h"

void SAniData::Load( wstring wFile, wstring wAni )//wFile에 맞는 wAni데이터 로드 
{
	WCHAR wcAni[MAX_PATH];
	GetPrivateProfileString( wAni.c_str(), L"AniFile", L"", wcAni, MAX_PATH, wFile.c_str() );
	m_wFile = wcAni;
}

void SAniObjData::Load( wstring wFile )
{
	// wFile에 맞는 저장되어 있는 애니오브젝트데이터값 로드
	m_vScale.x = (float)GetPrivateProfileInt( L"Common", L"Scale_X", 100, wFile.c_str() ) * 0.01f;
	m_vScale.y = (float)GetPrivateProfileInt( L"Common", L"Scale_Y", 100, wFile.c_str() ) * 0.01f;

	m_iRadius = GetPrivateProfileInt( L"Common", L"Radius", 0, wFile.c_str() );

	m_iMaxHealth = GetPrivateProfileInt( L"Common", L"MaxHealth", 0, wFile.c_str() );
	m_iMaxMana = GetPrivateProfileInt( L"Common", L"MaxMana", 0, wFile.c_str() );

	m_iHealth = m_iMaxHealth;
	m_iMana = m_iMaxMana;

	m_iDamage = GetPrivateProfileInt( L"Common", L"Damage", 0, wFile.c_str() );
	m_fSpeed = (float)GetPrivateProfileInt( L"Common", L"Speed", 0, wFile.c_str() );

	m_iDamage = GetPrivateProfileInt( L"Common", L"Damage", 0, wFile.c_str() );
	m_iScope = GetPrivateProfileInt( L"Common", L"Scope", 0, wFile.c_str() );

	//애니메이션의 상태를 저장해줌
	//평소상태, 걷는상태, 데미지를 입은 상태, 죽은 상태, 끝난 상태에 따라 저장
	SAniData sAniNormal;
	sAniNormal.Load( wFile, L"Normal" );
	m_mapAni.insert( make_pair( AT_NORMAL, sAniNormal ));

	SAniData sAniWalk;
	sAniWalk.Load( wFile, L"Move" );
	m_mapAni.insert( make_pair( AT_MOVE, sAniWalk ));

	SAniData sAniDamage;
	sAniDamage.Load( wFile, L"Attack" );
	m_mapAni.insert( make_pair( AT_ATTACK, sAniDamage ));

	SAniData sAniDie;
	sAniDie.Load( wFile, L"Die" );
	m_mapAni.insert( make_pair( AT_DIE, sAniDie ));

	SAniData sAniEnd;
	sAniEnd.Load( wFile, L"End" );
	m_mapAni.insert( make_pair( AT_END, sAniEnd ));
}

void SObjData::Load( wstring wFile )
{
	//오브젝트 데이터 로드
	m_vScale.x = (float)GetPrivateProfileInt( L"Common", L"Scale_X", 100, wFile.c_str() ) * 0.01f;
	m_vScale.y = (float)GetPrivateProfileInt( L"Common", L"Scale_Y", 100, wFile.c_str() ) * 0.01f;

	WCHAR wcFile[MAX_PATH];
	GetPrivateProfileString( L"Common", L"ImgFile", L"", wcFile, MAX_PATH, wFile.c_str() );

	m_wFile = wcFile;
}

CGameObjPool::CGameObjPool(void)
{
}


CGameObjPool::~CGameObjPool(void)
{
	m_mapAniObj.clear();
}

void CGameObjPool::LoadAniObj( wstring wID, wstring wFile )
{ 
	//애니 오브젝트 로드
	map< wstring, SAniObjData >::iterator mit = m_mapAniObj.find( wID );
	if( mit != m_mapAniObj.end() )
		return ;

	SAniObjData sData;
	sData.Load( wFile );

	m_mapAniObj.insert( make_pair( wID, sData ));
}

void CGameObjPool::LoadObj( wstring wID, wstring wFile )
{
	//오브젝트 로드
	map< wstring, SObjData >::iterator mit = m_mapObj.find( wID );
	if( mit != m_mapObj.end() )
		return ;

	SObjData sData;
	sData.Load( wFile );

	m_mapObj.insert( make_pair( wID, sData ));
}

const SAniObjData* CGameObjPool::GetAniObjData( wstring wID )
{
	//애니오브젝트 데이터 불러오기
	map< wstring, SAniObjData >::iterator mit = m_mapAniObj.find( wID );
	if( mit == m_mapAniObj.end() )
		return NULL;

	return &mit->second;
}

const SObjData* CGameObjPool::GetObjData( wstring wID )
{
	//오브젝트데이터 불러오기
	map< wstring, SObjData >::iterator mit = m_mapObj.find( wID );
	if( mit == m_mapObj.end() )
		return NULL;

	return &mit->second;
}