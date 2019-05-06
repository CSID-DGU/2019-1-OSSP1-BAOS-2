#pragma once

struct STileData			// 타일 정보 구조체 
{
	D3DXVECTOR2 m_vIndex;		// 타일 번호
	D3DXVECTOR2 m_vPos;			// 타일 위치
	D3DXVECTOR2 m_vIndexCenter;		// 타일 중앙 

	int m_iTileType;

	STileData():
		m_vIndex( 0.0f, 0.0f ),
		m_vPos( 0.0f, 0.0f ),
		m_vIndexCenter( 0.0f, 0.0f ),
		m_iTileType( -1 )
	{
	}
};

class CGameTileMgr : public CGameObj
{
private:
	map< wstring, STileData > m_mapInfoTile;		// 타일정보를 저장한 맵 배열
	
	D3DXVECTOR2 m_vGridSize;		// 타일 사이즈 
	int m_iTileWidthCount;				// 타일 개수
	int m_iTileHeightCount;			// 타일개수 

public:
	CGameTileMgr(void);
	virtual ~CGameTileMgr(void);

	bool m_bCheckAllTile;				// 모든 타일을 불러왔는가?

	void Load( wstring wFile );
	virtual void OnFrameMove( float fElapsedTime );

	D3DXVECTOR2 FindTileIndex( D3DXVECTOR2 vPos );
	D3DXVECTOR2 FindCenterPos( D3DXVECTOR2 vPos );

	D3DXVECTOR2 FindIndexCenter( D3DXVECTOR2 vPos );
	D3DXVECTOR2 ChangeCenterIndex( D3DXVECTOR2 vIndex );

	STileData* GetTileData( D3DXVECTOR2 vIndex );

	vector< D3DXVECTOR2 > GetNeighberTile( D3DXVECTOR2 vTile, int iSize );

	void RemoveTile();

	int GetTileWidthCount() { return m_iTileWidthCount; }
	int GetTileHeightCount() { return m_iTileHeightCount; }

	D3DXVECTOR2 GetTileGridSize() { return m_vGridSize; }

	void CreateTile();

};

