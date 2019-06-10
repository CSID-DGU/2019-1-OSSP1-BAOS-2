#include "DXUT.h"
#include "../Home.h"

extern CTexture * g_pTexture;
extern CSprite * g_pSprite;
extern CCamera * g_pCamera;

CAniRender::CAniRender( CAniObj * pGameObj )://AniRender ���� �� �ʱ�ȭ
CRender( pGameObj ),
m_fTrackTime( 0.0f ),
m_fTrackSpeed( 0.0f ),
m_iCurIndex( 0 ),
m_bLoop( false )
{
}

CAniRender::~CAniRender(void)
{
	for( int i = 0; i < (int)m_vecTexture.size(); ++i )	// �迭���鼭 ���� 
		g_pTexture->ReserveRelease( m_vecTexture[i] );	// ������� ���� 
}


void CAniRender::Load( wstring wFile )
{
	m_bLoop = ( GetPrivateProfileInt( L"Data", L"Loop", 0, wFile.c_str() )  == 1 );     // �ݺ�
	m_fTrackSpeed = (float)GetPrivateProfileInt( L"Data", L"TrackSpeed", 0, wFile.c_str() ) * 0.01f;	// ����ӵ�
	int iImgCount = GetPrivateProfileInt( L"Data", L"ImgCount", 0, wFile.c_str() );				// �̹��� ���

	WCHAR wcFileName[MAX_PATH]; // �̹��� �̸�
	WCHAR wcFileExit[MAX_PATH];	// �̹��� ������

	GetPrivateProfileString( L"Data", L"ImgFileName", L"", wcFileName, MAX_PATH, wFile.c_str() );
	GetPrivateProfileString( L"Data", L"ImgFileExit", L"", wcFileExit, MAX_PATH, wFile.c_str() );

	for( int i = 0; i < iImgCount; ++i )
	{
		wstringstream os;
		os<< wcFileName << i << wcFileExit;

		m_vecTexture.push_back( g_pTexture->Load( os.str().c_str() ) );//���Ϳ� �ؽ��� ���� ����
	}

	m_AniEvent.Load( wFile );
};

bool CAniRender::OnFrameMove( float fElapsedTime )
{
	UpdateWorld();	// ��� ������Ʈ
	
	m_fTrackTime += fElapsedTime;	// �ð����ϱ�

	bool bChange = m_fTrackTime > m_fTrackSpeed; // �̹��� ����ð��̶� �ð� �� 

	if( bChange )
	{
		m_AniEvent.OnEvent( (CAniObj*)m_pGameObj, m_iCurIndex );

		int iIndex = m_iCurIndex + 1;	// �̹��� ��� �߰�

		if( iIndex >= (int)m_vecTexture.size() )	// ����� �ؽ��� ũ�� ��
		{
			if( m_bLoop )	// �ݺ��Ұ��ΰ�?
				SetAniIndex( 0 );
			else
				return false; 
		}
		else
			SetAniIndex( iIndex ); // �ε��� ��ȣ 
	}
	return true;
}


void CAniRender::UpdateWorld()
{
	D3DXMATRIX matLocal;
	MakeLocal( matLocal );

	D3DXMATRIX matRot;
	MakeRot( matRot );

	D3DXMATRIX matTrans;
	MakeTrans( matTrans );	// ��� 

	D3DXMATRIX matScale;
	MakeScale( matScale );

	m_matWorld = matLocal * matRot * matScale * matTrans;
	m_matWorld._43 = 0.0f;
}

void CAniRender::OnFrameRender()//Frame Render 
{
	if( m_iCurIndex < 0 || m_iCurIndex >= (int)m_vecTexture.size() )	// �̹��� ����� �ؽ��� �迭ũ�� ��
		return ;

	D3DXMATRIX matView;
	D3DXMatrixIdentity( &matView );		// ī�޶� 
	g_pCamera->GetTransform( &matView );//ī�޶� ��ġ �޾ƿ�

	D3DXMATRIX matWorld = m_matWorld * matView;
	matWorld._43 = 0.0f;

	g_pSprite->SetTransform( &matWorld );//��������Ʈ�� ��ȯ ��ġ matWorld�� ����
	g_pSprite->OnDraw( g_pTexture->GetTexture( m_vecTexture[m_iCurIndex] ), NULL, 0.0f, 0.0f );
}


void CAniRender::MakeLocal( D3DXMATRIX &matTrans )	// ���ϸ��̼� ��� 
{
	D3DXMatrixIdentity( &matTrans );	// ��ġ

	if( m_iCurIndex < 0 || m_iCurIndex >= (int)m_vecTexture.size() )	// �̹��� ����� �迭ũ�� ��
		return ;

	const STextureInfo* pTextureInfo = g_pTexture->GetTextureInfo( m_vecTexture[m_iCurIndex] );	// �ؽ��� ���� �ҷ�����
	if( pTextureInfo == NULL )
		return ;

	matTrans._41 -= ( pTextureInfo->m_TextureInfo.Width * 0.5f );	// ��ġ ��� 
	matTrans._42 -= ( pTextureInfo->m_TextureInfo.Height * 1.0f );	// ��ġ ���
}

void CAniRender::SetAniIndex( int iIndex )	// �̹��� ��� ��ȯ
{
	m_iCurIndex = iIndex;
	m_fTrackTime = 0.0f;
}
