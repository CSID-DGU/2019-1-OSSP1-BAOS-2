#include "DXUT.h"
#include "Home.h"

extern CMouse* g_pMouse;
extern CGameObjMgr* g_pGameObjMgr;

CGameTileMgr::CGameTileMgr(void)://타일매니저 초기화 및 생성
	m_bCheckAllTile( false ),
	m_vGridSize( 64, 64 ),
	m_iTileWidthCount( 32 ),
	m_iTileHeightCount(  32 )
{
}


CGameTileMgr::~CGameTileMgr(void)
{
}


void CGameTileMgr::Load( wstring wFile )//wFile Load
{
	FILE* fp;
	 _wfopen_s(  &fp, wFile.c_str(), L"rt" );//파일 open

	if( fp == NULL )//불러오지 못했다면 종료
		return ; 

	for( int y = 0; y < m_iTileHeightCount; ++y )//타일 높이와 너비만큼 반복
	{
		for( int x = 0; x < m_iTileWidthCount; ++x )
		{

			wstringstream os;//문자열 처리 위한 stringstream 사용
			os << x << '_' << y;

			int iTileType;

			STileData sData;//TileData 설정, 할당 및 데이터 저장
			sData.m_vIndex.x = (float)(int)x;
			sData.m_vIndex.y = (float)(int)y;
			sData.m_vPos.x = x * m_vGridSize.x;
			sData.m_vPos.y = y * m_vGridSize.y;
			sData.m_vIndexCenter.x = (x * m_vGridSize.x) + (m_vGridSize.x/2);
			sData.m_vIndexCenter.y = (y * m_vGridSize.y) + (m_vGridSize.y/2);

			fwscanf_s( fp, L"%d",  &iTileType );
			sData.m_iTileType = iTileType;

			m_mapInfoTile.insert( make_pair( os.str(), sData ));
		}
	}
	_fcloseall();
}

void CGameTileMgr::OnFrameMove( float fElapsedTime )
{
}

D3DXVECTOR2 CGameTileMgr::FindTileIndex( D3DXVECTOR2 vPos )			// 타일 번호 반환
{
	D3DXVECTOR2 vTileIndex;
	vTileIndex.x = (float)(int)(( vPos.x  ) / m_vGridSize.x );
	vTileIndex.y = (float)(int)(( vPos.y  ) / m_vGridSize.y );

	return vTileIndex;
}

D3DXVECTOR2 CGameTileMgr::FindCenterPos( D3DXVECTOR2 vTileIndex )	//vTileIndex로 center 위치 탐색
{
	STileData* pData = GetTileData( vTileIndex );
	if( pData == NULL )
		return D3DXVECTOR2( 0, 0 );
	
	return D3DXVECTOR2( pData->m_vIndexCenter.x, pData->m_vIndexCenter.y ); //알맞은 데이터가 있으면 리턴
}

D3DXVECTOR2 CGameTileMgr::FindIndexCenter( D3DXVECTOR2 vPos )		//vpos로 indexcenter 탐색
{
	D3DXVECTOR2 vTileIndex;
	vTileIndex = FindTileIndex( vPos );

	STileData* pData = GetTileData( vTileIndex );
	if( pData == NULL )
		return D3DXVECTOR2( 0, 0 );
	
	return D3DXVECTOR2( pData->m_vIndexCenter.x, pData->m_vIndexCenter.y ); 
}

STileData* CGameTileMgr::GetTileData( D3DXVECTOR2 vIndex )	//tile data 정보 불러오기
{
	wstringstream os;
	os << vIndex.x << L'_' << vIndex.y;

	map<wstring, STileData>::iterator mit = m_mapInfoTile.find( os.str() );//os에 정보 저장
	if( mit == m_mapInfoTile.end() )
		return NULL;

	return &mit->second;
}

void CGameTileMgr::RemoveTile()//타일 제거
{
	m_mapInfoTile.clear();
}