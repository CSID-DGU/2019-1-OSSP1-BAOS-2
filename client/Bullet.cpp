#include "DXUT.h"
#include "Home.h"

extern CGameObjMgr* g_pGameObjMgr;

CBullet::CBullet() :
	m_vDirectionVector(0.0f, 0.0f)
{
}


CBullet::~CBullet()
{
}

void CBullet::Load(wstring wsFile)
{
	__super::Load(wsFile);

	OnChangeAni(AT_NORMAL);
}

void CBullet::OnFrameMove(float fElapsedTime)
{
	__super::OnFrameMove(fElapsedTime);

	m_vPos += m_vDirectionVector * (m_fSpeed * fElapsedTime);

	CGameObj* pEnemy = g_pGameObjMgr->OnFindTarget(this, g_pGameObjMgr->m_setPlayObj, this->GetRadius());
	if (pEnemy == nullptr)
		return;

	pEnemy->OnDamage(this->GetDamage(), pEnemy);
	Destroy();
}

void CBullet::OnFrameRender()
{
	__super::OnFrameRender();
}

void CBullet::OnEndAni()
{
	Destroy();
}