#include "DXUT.h"
#include "Home.h"


CRender::CRender( CGameObj* pGameObj ):
m_pGameObj( pGameObj )
{
	D3DXMatrixIdentity( &m_matWorld );
}


CRender::~CRender(void)
{
}

void CRender::MakeRot( D3DXMATRIX &matRot )
{
	if( m_pGameObj == NULL )
		return ;

	D3DXMatrixIdentity( &matRot );

	switch( m_pGameObj->GetRenderType() )
	{
	case ERENDER_NORMAL:
		{
			D3DXMatrixRotationZ( &matRot, (float)m_pGameObj->GetDirection() );
			break;
		}

	case ERENDER_DIRECTION:
		{
			if( m_pGameObj->GetDirection() > 4 )
				D3DXMatrixRotationY( &matRot, D3DXToRadian( 180 ) );

			break;
		}
	}
}

void CRender::MakeScale( D3DXMATRIX &matScale )
{
	if( m_pGameObj == NULL )
		return ;

	D3DXMatrixIdentity( &matScale );
	matScale._11 = m_pGameObj->GetScl()->x;
	matScale._22 = m_pGameObj->GetScl()->y;
}

void CRender::MakeTrans( D3DXMATRIX &matTrans )
{
	if( m_pGameObj == NULL )
		return ;

	D3DXMatrixIdentity( &matTrans );
	matTrans._41 = m_pGameObj->GetPos()->x;
	matTrans._42 = m_pGameObj->GetPos()->y;
}

void CRender::MakeAlpha( DWORD* pDark, DWORD* pView, D3DXVECTOR2 vPos, const STextureInfo* DarkInfo, const STextureInfo* ViewInfo )
{
	D3DXVECTOR2 vCenter( vPos.x - ( int )ViewInfo->m_TextureInfo.Width * 0.5f, vPos.y - (int)ViewInfo->m_TextureInfo.Height * 0.5f );

	//for( int y = 0; y < (int)DarkInfo->m_TextureInfo.Height; ++y )
	//	for( int x = 0; x < (int)DarkInfo->m_TextureInfo.Width; ++x )
	//	{
	//		int iDarkIndex = ( y * (int)DarkInfo->m_ImgDesc.Width ) + x;
	//		D3DXCOLOR DarkColor = pDark[ iDarkIndex ];

	//		if( DarkColor < 1 )
	//			DarkColor = 1;

	//		pDark[ iDarkIndex ] = DarkColor; 
	//	}


	for( int y = 0; y < (int)ViewInfo->m_TextureInfo.Height; ++y )
		for( int x = 0; x < (int)ViewInfo->m_TextureInfo.Width; ++x )
		{
			int iDarkX = ( (int)vCenter.x + x );  // �������̹����� �������κ��� ��ġ���̴�.
			int iDarkY = ( (int)vCenter.y + y );

			int iDarkIndex = ( iDarkY * (int)DarkInfo->m_ImgDesc.Width ) + iDarkX; // ������ �̹��� ������ �Ͽ��� ����Ǿ��ִ� �̸� ã�����ؼ� ���� ũ�� * �� + X���̴�. 
			int iViewIndex = ( y * (int)ViewInfo->m_TextureInfo.Width ) + x; // �Ϸķε� �迭���� ��ġ���� ����Ѵ�. // ���� 1 * 1024 + 1, 3* 1024 + 5  
		
			if( iDarkX < 0 || iDarkX >= (int)DarkInfo->m_ImgDesc.Width || iDarkY < 0 || iDarkY >= (int)DarkInfo->m_ImgDesc.Height ) 
					continue;

				D3DXCOLOR DarkColor = pDark[iDarkIndex]; // �迭���� ��ġ�� ( �ε��� ) �� �̿��Ͽ� ������ �����´�.
				D3DXCOLOR ViewColor = pView[iViewIndex];

				if( DarkColor.a > ViewColor.a ) // 1.0f �� ������ 0.0f �� ����ִ»�
					DarkColor.a = ViewColor.a; // ���İ��� ���Ͽ� �������� �ִ´�.

				pDark[ iDarkIndex ] = DarkColor; 
		}
}