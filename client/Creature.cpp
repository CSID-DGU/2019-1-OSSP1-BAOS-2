#include "DXUT.h"
#include "Home.h"

extern CGameObjMgr* g_pGameObjMgr;
extern CGameTileMgr* g_pGameTileMgr;

CCreature::CCreature(void)
{
}


CCreature::~CCreature(void)
{
}

void CCreature::Load( wstring wFile )//wFile ũ���� �ε�
{
	__super::Load( wFile );

	m_pController = new CCreatureAI( this );//ũ���� ai����

	//���� ������Ʈ �ų������� ü�� ������Ʈ �ε�
	CGameObj* pHealth = g_pGameObjMgr->Load( EGAMEOBJ_HEALTH, ETEAM_NENUTAL, L"Creature_Health", L"Health", D3DXVECTOR2( 0, 0 ), 0, ERENDER_NORMAL, true );
	((CHealth*)pHealth)->SetPlayer( this );

	CUI* pMiniDot = NULL;//ui minidot ���� �̴ϸʿ��� ������ ���� Dot�� �ǹ�

	if( m_iTeam == ETEAM_FRIEND )//���� �Ʊ� ���� ��� �ʷϻ����� Dot ����
		pMiniDot = g_pGameObjMgr->UILoad( UI_MINIDOT, L"GreenDot", L"GreenDot", D3DXVECTOR2( 0, 0 ), false, true );

	if( m_iTeam == ETEAM_ENEMY )//���� ���� ���� ��� ���������� Dot ����
		pMiniDot = g_pGameObjMgr->UILoad( UI_MINIDOT, L"RedDot", L"RedDot", D3DXVECTOR2( 0, 0 ), false, true );


	if( pMiniDot != NULL )//������ ���
		pMiniDot->SetObj( this );//������Ʈ ����


	SetPos( g_pGameTileMgr->FindCenterPos( m_vPos ) );//��ġ ����
	g_pGameObjMgr->Load( EGAMEOBJ_BEGINEFFECT, ETEAM_NENUTAL, L"Spawn", L"Spawn", m_vPos + D3DXVECTOR2( 0, 50 ), 0, ERENDER_NORMAL, true );

	OnChangeAni( AT_NORMAL );//NORMAL ���·� �ִ� ��ȯ
}

void CCreature::OnFrameMove( float fElapsedTime )//������ ����
{
	__super::OnFrameMove( fElapsedTime );
}

void CCreature::OnDamage( int iDamage, CGameObj* pObj )//������ ����
{
	m_iHealth -= iDamage;//���� ü�¿��� ��������ŭ ���־� ü�� ����

	if( m_iHealth <= 0 )//�������� 0���ϰ� �Ǹ� ���� ����
	{
		if( m_iAniCategory != AT_DIE )//���� ���°� �ƴ϶�� 
			OnChangeAni( AT_DIE );//���� ���·� �ִ� ��ȯ
	}

	if( pObj->IsDestroy() == false )//���ŵ��� �ʾҴٸ�
		m_pDamager = pObj;//������
}