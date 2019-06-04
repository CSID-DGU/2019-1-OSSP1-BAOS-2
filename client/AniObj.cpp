#include "DXUT.h"
#include "Home.h"

extern GameDataMgr * g_pGameDataMgr;

CAniObj::CAniObj(void)://���� ������Ʈ ���� �� �ʱ�ȭ
	m_iAniCategory( -1 ),
	m_iInputIndex( -1 ),
	m_iChangeIndex( -1 ),
	m_iNextAniCategory( -1 ),
	m_pController( NULL ),
	m_bChangeNextAni( false )
{
}


CAniObj::~CAniObj(void)
{
	UnLoad();
}

void CAniObj::Load( wstring wFile )//wFile Load
{
	if( m_mapAniRender.empty() == false )//aniRender�� ������� ��� ����
		return ;

	const SAniObjData* pObjData = g_pGameDataMgr->GetAniObjData( wFile );
	if( pObjData == NULL )
		return ;


	SetScl( D3DXVECTOR2( pObjData->m_vScale ));//������ ������Ʈ�� ������ ����

	//������Ʈ �������� �ִ�ü��, ü��, ������ ����, ���ǵ�, ����, ������ ����
	m_iMaxHealth = pObjData->m_iMaxHealth;
	m_iHealth = pObjData->m_iHealth;

	m_iDamage = pObjData->m_iDamage;
	m_fSpeed = pObjData->m_fSpeed;

	m_iScope = pObjData->m_iScope;
	m_iRadius = pObjData->m_iRadius;

	map< int, SAniData >::const_iterator mit = pObjData->m_mapAni.begin();//������Ʈ ������ ���ͷ����� ����
	for( mit; mit != pObjData->m_mapAni.end(); ++mit )//������Ʈ ����Ʈ��ŭ �ݺ�
	{
		if( mit->second.m_wFile.empty() )//������� ��� ������
			continue;

		CRender* pRender;

		switch( m_iRenderType )//Ÿ�Կ� ���� ���������� 
		{
		case ERENDER_NORMAL:
			{
				pRender =new CAniRender( this );
				break; 
			}
		case ERENDER_DIRECTION: 
			{
				pRender = new CDirectionAniRender( this );
				break;
			}
		case ERENDER_UI:
			{
				pRender = new CUIAniRender( this );
				break ;
			}
		}

		pRender->Load( mit->second.m_wFile );
		m_mapAniRender.insert( make_pair( mit->first, pRender ));
	}
}

void CAniObj::UnLoad()//�ε� ����
{
	m_pRender = NULL;

	//Map�� ����Ǿ� �ִ� AniRender���� ���� �����ϰ� ����
	map< int, CRender* >::iterator mit = m_mapAniRender.begin();
	for( mit; mit != m_mapAniRender.end(); ++mit )
		SAFE_DELETE( mit->second );//�����ϰ� ����

	if( m_pController != NULL )//��Ʈ�ѷ��� �����Ѵ�.
		SAFE_DELETE( m_pController );

	m_mapAniRender.clear();
}

void CAniObj::OnFrameMove( float fElapsedTime )//�ǽð����� ������ ����
{
	if( m_pRender == NULL )
		return ;

	if( m_pController != NULL )
		m_pController->OnFrameMove( fElapsedTime );

	if( m_pRender->OnFrameMove( fElapsedTime ) == false )
		OnEndAni();

	if( m_bChangeNextAni )//���� �ִϸ��̼����� ��ȯ
	{
		if( (( CDirectionAniRender* ) m_pRender )->GetAniIndex() >= m_iChangeIndex )
			OnChangeAni( m_iNextAniCategory );
	}
}

void CAniObj::OnEndAni()//Ani ����
{
	if( m_pController != NULL )
		m_pController->OnEndAni( m_iAniCategory );
}

void CAniObj::OnFrameRender()//Frame Rendering
{
	if( m_pRender == NULL )
		return ;

	m_pRender->OnFrameRender();//������ ������
}

void CAniObj::OnChangeAni( int iAni )//Ani ��ȯ
{
	map< int, CRender* >::iterator mit = m_mapAniRender.find( iAni );//iAni�� ã�Ƽ� iterator ����
	if( mit == m_mapAniRender.end() )//ã�� ������ ���
	{
		Destroy();
		return ;
	}

	//�ִ� ��ȯ �غ����, �ʱ�ȭ
	m_iInputIndex = -1;
	m_iChangeIndex = -1;
	m_iNextAniCategory = -1;

	//�ִ� ī���ڸ� �缳��
	m_iAniCategory = iAni;

	m_pRender = mit->second;
	((CDirectionAniRender*)m_pRender)->SetAniIndex( 0 );

	m_pRender->UpdateWorld();//���� �ٽ� ����

	if( m_pController != NULL )//��Ʈ�ѷ� �ִ� ��ȯ
		m_pController->OnChangeAni( iAni );

}

void CAniObj::SetNextAni( int iInputIndex, int iChangeIndex, int iAniCategory )//���� �ִ� ����
{
	//�޾ƿ� �μ���� index�� ī���ڸ� ����
	m_iInputIndex = iInputIndex;
	m_iChangeIndex = iChangeIndex;
	m_iAniCategory = iAniCategory;
}

void CAniObj::TryNextAni()//���� �ִϸ��̼����� ��ȯ�õ�
{
	if( m_iNextAniCategory == NULL )//���� �ִ� ī�װ��� ������� ����
		return ;

	if( ((CDirectionAniRender*)m_pRender)->GetAniIndex() < m_iInputIndex )//���� index�� ������ �ִ� �ִ� �ε������� Ŭ���
		return ;

	m_bChangeNextAni = true;//��ȯ����Ȯ�ο� bool �ڷ���
}