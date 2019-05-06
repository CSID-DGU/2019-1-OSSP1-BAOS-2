#include "DXUT.h"
#include "Home.h"

extern CMouse* g_pMouse;
extern CGameObjMgr* g_pGameObjMgr;

CGameTileMgr::CGameTileMgr(void):
	m_bCheckAllTile( false ),
	m_vGridSize( 64, 64 ),
	m_iTileWidthCount( 32 ),
	m_iTileHeightCount(  32 )
{
}


CGameTileMgr::~CGameTileMgr(void)
{
}


void CGameTileMgr::Load( wstring wFile )
{
	FILE* fp;
	 _wfopen_s(  &fp, wFile.c_str(), L"rt" );

	if( fp == NULL )
		return ; 

	for( int y = 0; y < m_iTileHeightCount; ++y )
	{
		for( int x = 0; x < m_iTileWidthCount; ++x )
		{

			wstringstream os;
			os << x << '_' << y;

			int iTileType;

			STileData sData;
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

D3DXVECTOR2 CGameTileMgr::FindCenterPos( D3DXVECTOR2 vTileIndex )//타일 센터 좌표 찾기
{
	STileData* pData = GetTileData( vTileIndex );
	if( pData == NULL )
		return D3DXVECTOR2( 0, 0 );
	
	return D3DXVECTOR2( pData->m_vIndexCenter.x, pData->m_vIndexCenter.y ); 
}

D3DXVECTOR2 CGameTileMgr::FindIndexCenter( D3DXVECTOR2 vPos )//파일 인덱스 센터 좌표 찾기
{
	D3DXVECTOR2 vTileIndex;
	vTileIndex = FindTileIndex( vPos );

	STileData* pData = GetTileData( vTileIndex );
	if( pData == NULL )
		return D3DXVECTOR2( 0, 0 );
	
	return D3DXVECTOR2( pData->m_vIndexCenter.x, pData->m_vIndexCenter.y ); 
}

STileData* CGameTileMgr::GetTileData( D3DXVECTOR2 vIndex )//타일 데이터 얻기
{
	wstringstream os;
	os << vIndex.x << L'_' << vIndex.y;

	map<wstring, STileData>::iterator mit = m_mapInfoTile.find( os.str() );
	if( mit == m_mapInfoTile.end() )
		return NULL;

	return &mit->second;
}

void CGameTileMgr::RemoveTile()//타일 제거
{
	m_mapInfoTile.clear();
}