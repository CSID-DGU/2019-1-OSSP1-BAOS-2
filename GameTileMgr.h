#pragma once

struct STileData			// Ÿ�� ���� ����ü 
{
	D3DXVECTOR2 m_vIndex;		// Ÿ�� ��ȣ
	D3DXVECTOR2 m_vPos;			// Ÿ�� ��ġ
	D3DXVECTOR2 m_vIndexCenter;		// Ÿ�� �߾� 

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
	map< wstring, STileData > m_mapInfoTile;		// Ÿ�������� ������ �� �迭
	
	D3DXVECTOR2 m_vGridSize;		// Ÿ�� ������ 
	int m_iTileWidthCount;				// Ÿ�� ����
	int m_iTileHeightCount;			// Ÿ�ϰ��� 

public:
	CGameTileMgr(void);
	virtual ~CGameTileMgr(void);

	bool m_bCheckAllTile;				// ��� Ÿ���� �ҷ��Դ°�?

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

