#include "DXUT.h"
#include "Home.h"


CGameObj::CGameObj(void) ://���ӿ�����Ʈ ������ - �ʿ��� ���� �ʱ�ȭ����
	m_pRender(NULL),
	m_vPos(0.0f, 0.0f),
	m_vScl(1.0f, 1.0f),
	m_vImgSize(0.0f, 0.0f),
	m_vDirectionVector(0.0f, 0.0f),
	m_vGoalPos(NULLVECTOR2),
	m_iDirection(0),
	m_iHealth(0),
	m_iDamage(0),
	m_iScope(0),
	m_iMana(0),
	m_iTeam(-1),
	m_fSpeed(0.0f),
	m_bDestroy(false),
	m_iRadius(0),
	m_bWork(false),
	m_pDamager(NULL),
	m_iRenderType(-1),
	m_bCamera(true)
{
}

CGameObj::~CGameObj(void)//�Ҹ���
{
	UnLoad();
}

void CGameObj::UnLoad()//���� ������
{
	SAFE_DELETE(m_pRender);
}

void CGameObj::OnFrameMove(float fElapsedTime)//�����ӹ���
{
	if (m_pRender == NULL)
		return;

	m_pRender->OnFrameMove(fElapsedTime);
}

void CGameObj::OnFrameRender()//�����ӷ�����
{
	if (m_pRender == NULL)
		return;

	m_pRender->OnFrameRender();
}