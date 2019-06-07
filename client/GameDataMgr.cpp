#include "DXUT.h"
#include "Home.h"

void SAniData::Load( wstring wFile, wstring wAni )
{
	WCHAR wcAni[MAX_PATH];
	GetPrivateProfileString( wAni.c_str(), L"AniFile", L"", wcAni, MAX_PATH, wFile.c_str() );
	m_wFile = wcAni;
}

void SAniObjData::Load( wstring wFile )//wFile인 애니오브젝트데이터 로드
{
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

	//오브젝트 설정
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

	SAniData sAniSkill1;
	sAniSkill1.Load(wFile, L"Skill1");
	m_mapAni.insert(make_pair(AT_SKILL1, sAniSkill1));

	SAniData sAniSkill2;
	sAniSkill2.Load(wFile, L"Skill2");
	m_mapAni.insert(make_pair(AT_SKILL2, sAniSkill2));
}

void SObjData::Load( wstring wFile )//wFile 로드
{
	m_vScale.x = (float)GetPrivateProfileInt( L"Common", L"Scale_X", 100, wFile.c_str() ) * 0.01f;
	m_vScale.y = (float)GetPrivateProfileInt( L"Common", L"Scale_Y", 100, wFile.c_str() ) * 0.01f;

	WCHAR wcFile[MAX_PATH];
	GetPrivateProfileString( L"Common", L"ImgFile", L"", wcFile, MAX_PATH, wFile.c_str() );

	m_wFile = wcFile;
}

GameDataMgr::GameDataMgr(void)
{
}


GameDataMgr::~GameDataMgr(void)
{
	m_mapAniObj.clear();
}

void GameDataMgr::LoadAniObj( wstring wID, wstring wFile )//애니 오브젝트 데이터 로드
{ 
	map< wstring, SAniObjData >::iterator mit = m_mapAniObj.find( wID );
	if( mit != m_mapAniObj.end() )
		return ;

	SAniObjData sData;
	sData.Load( wFile );//데이터 로드

	m_mapAniObj.insert( make_pair( wID, sData ));//애니 오브젝트 맵에 로드한 데이터 저장
}

void GameDataMgr::LoadObj( wstring wID, wstring wFile )//오브젝트 로드
{
	map< wstring, SObjData >::iterator mit = m_mapObj.find( wID );
	if( mit != m_mapObj.end() )
		return ;

	SObjData sData;
	sData.Load( wFile );

	m_mapObj.insert( make_pair( wID, sData ));//오브젝트 맵에 데이터 저장
}

const SAniObjData* GameDataMgr::GetAniObjData( wstring wID )//wID 게임 애니오브젝트 데이터 정보 불러오기
{
	map< wstring, SAniObjData >::iterator mit = m_mapAniObj.find( wID );
	if( mit == m_mapAniObj.end() )
		return NULL;

	return &mit->second;
}

const SObjData* GameDataMgr::GetObjData( wstring wID )//wID 오브젝트 데이터 정보 불러오기
{
	map< wstring, SObjData >::iterator mit = m_mapObj.find( wID );
	if( mit == m_mapObj.end() )
		return NULL;

	return &mit->second;
}