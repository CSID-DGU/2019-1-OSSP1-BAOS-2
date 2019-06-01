#include "DXUT.h"
#include "Home.h"


CTexture::CTexture(void):
	m_iTexture( -1 )
{
}


CTexture::~CTexture(void)//�Ҹ���
{
	ReleaesAll();//��� �����ش�
}

int CTexture::Load( wstring wFile )//wFile Load
{
	map< wstring, STextureInfo* >::iterator mit = m_mapRefInfo.find( wFile ); //map �ڷᱸ���� wFile�� ����Ű�� iterator mit ����
	if( mit != m_mapRefInfo.end() )//iterator mit�� ã���� ���
	{
		++mit->second->m_iRefCount; //m_iRefCount�� 1 ������Ų��.

		return mit->second->m_iTexture;//
	}

	D3DXIMAGE_INFO TextureInfo;	//�̹��� ���� ���� ����ü
	LPDIRECT3DTEXTURE9 pTexture;//directx �������̽�

	//���ϸ� �ش�Ǵ� �ؽ��ĸ� �ҷ��´�. ���� S_OK �÷��װ� ���� �ʴٸ� �ε� �����̹Ƿ� ������ ȣ��
	if( D3DXCreateTextureFromFileEx( DXUTGetD3D9Device()
		, wFile.c_str()
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 1
		, 0
		, D3DFMT_A8R8G8B8
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE
		, D3DX_FILTER_NONE
		, 0
		, &TextureInfo
		, NULL
		, & pTexture ) != S_OK )
		return - 1;

	++m_iTexture;	//�ؽ��� ���� ����

	STextureInfo* pTextureInfo = new STextureInfo;	//�ؽ��� ���� ��ü �����Ҵ� �� �ʱ�ȭ
	pTextureInfo->m_iTexture  = m_iTexture;
	pTextureInfo->m_wFile = wFile;
	pTextureInfo->m_pTexture = pTexture;
	pTextureInfo->m_TextureInfo = TextureInfo;

	//�ؽ��Ŀ� �̹����� ����
	m_mapTexture.insert( make_pair( m_iTexture, pTextureInfo ));
	m_mapRefInfo.insert( make_pair( wFile, pTextureInfo ));

	return m_iTexture;
}

const STextureInfo* CTexture::GetTextureInfo( int iTexture )//�μ��� �˸��� �ؽ��� ���� ��������
{
	map< int, STextureInfo* >::iterator mit = m_mapTexture.find( iTexture );
	if( mit == m_mapTexture.end() )//ã�ƿ��� ������ ��� NULL return
		return NULL;

	return mit->second;
}

const STextureInfo* CTexture::GetTextureInfo( wstring wFile )//�μ��� �˸��� �ؽ��� ���� ��������
{
	map< wstring, STextureInfo* >::iterator mit = m_mapRefInfo.find( wFile );
	if( mit == m_mapRefInfo.end() )//ã�ƿ��� ������ ��� NULL return
		return NULL;

	return mit->second;
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture( int iTexture )//�μ��� �˸��� �ؽ��� ���� ��������
{
	map< int, STextureInfo* >::iterator mit = m_mapTexture.find( iTexture );
	if( mit == m_mapTexture.end() )//ã�ƿ��� ������ ��� NULL return
		return NULL;

	return mit->second->m_pTexture;
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture( wstring wFile )//�μ��� �˸��� �ؽ��� ���� ��������
{
	map< wstring, STextureInfo* >::iterator mit = m_mapRefInfo.find( wFile );
	if( mit == m_mapRefInfo.end() )//ã�ƿ��� ������ ��� NULL return
		return NULL;

	return mit->second->m_pTexture;
}

void CTexture::ReserveRelease( int iTexture )
{
	map< int, STextureInfo* >::iterator mit = m_mapTexture.find( iTexture );
	if( mit == m_mapTexture.end() )//ã�ƿ��� ������ ��� NULL return
		return ;

	m_vecTextureID.push_back( iTexture );//textureID�� ����
}

DWORD* CTexture::GetImgColorBits( int iTexture )//ImgColorBits ��������
{
	map< int, STextureInfo* >::iterator mit = m_mapTexture.find( iTexture );
	if( mit == m_mapTexture.end() )
		return NULL;

	D3DLOCKED_RECT* pRect = new D3DLOCKED_RECT;		//�簢�� ����ü ����
	mit->second->m_pTexture->LockRect( 0, pRect, NULL, 0 );

	D3DSURFACE_DESC drst;
	mit->second->m_pTexture->GetLevelDesc( 0, &drst );
	mit->second->m_ImgDesc = drst;

	if( mit->second->m_pColor == NULL )				//������ ���°��
	{
		//������ ���������ϰ�
		//�簢�� ����ü�� ����*���θ�ŭ�� �������� ����Ʈ�� color�� ����
		mit->second->m_pColor = new DWORD[ drst.Width * drst.Height ];
		memcpy( mit->second->m_pColor, pRect->pBits, drst.Width * drst.Height * sizeof( DWORD ) );
	}

	DWORD* pColor = (DWORD*)pRect->pBits;//Į�� �簢���� Bits�� ����
	SAFE_DELETE( pRect );//�簢���� �����Ҵ��� �������ش�

	mit->second->m_pTexture->UnlockRect( 0 );
	return pColor;
}

DWORD* CTexture::GetImgColorBits( wstring wFile )
{
	map< wstring, STextureInfo* >::iterator mit = m_mapRefInfo.find( wFile );
	if( mit == m_mapRefInfo.end() )
		return NULL;

	D3DLOCKED_RECT* pRect = new D3DLOCKED_RECT;
	mit->second->m_pTexture->LockRect( 0, pRect, NULL, 0 );

	D3DSURFACE_DESC drst;
	mit->second->m_pTexture->GetLevelDesc( 0, &drst );
	mit->second->m_ImgDesc = drst;

	if( mit->second->m_pColor == NULL )
	{
		mit->second->m_pColor = new DWORD[ drst.Width * drst.Height ];
		memcpy( mit->second->m_pColor, pRect->pBits, drst.Width * drst.Height * sizeof( DWORD ) );
	}

	DWORD* pColor = (DWORD*)pRect->pBits;
	SAFE_DELETE( pRect );

	mit->second->m_pTexture->UnlockRect( 0 );
	return pColor;
}

void CTexture::Release()//�����ֱ�
{
	for( int i = 0; i < (int)m_vecTextureID.size(); ++i )//�ؽ���ID�� ������ŭ ������ ����
	{
		map< int, STextureInfo* >::iterator mit = m_mapTexture.find( m_vecTextureID[i] );
		if( mit == m_mapTexture.end() )//�����Ͱ� ���� ��� return
			return ;

		--mit->second->m_iRefCount;

		if( mit->second->m_iRefCount > 0 )
			return ;

		map< wstring, STextureInfo* >::iterator mitRef = m_mapRefInfo.find( mit->second->m_wFile );
		if( mitRef != m_mapRefInfo.end() )//m_mapRefInfo�� ã�� �����Ͱ� �ִ� ��� �����ش�.
			m_mapRefInfo.erase( mitRef );

		SAFE_DELETE( mit->second );
		m_mapTexture.erase( mit );
	}
}

void CTexture::ReleaesAll()//���� �����ֱ�
{
	map< int, STextureInfo* >::iterator mit = m_mapTexture.begin();
	while( mit != m_mapTexture.end() )//ã���� ���
	{
		SAFE_DELETE( mit->second );//���� ����

		++mit;
	}

	m_mapTexture.clear();
	m_mapRefInfo.clear();
}

