#include "DXUT.h"
#include "Home.h"

extern CGameObjMgr* g_pGameObjMgr;

CBullet::CBullet() :
	m_vDirectionVector(0.0f, 0.0f)//생성 및 초기화
{
}


CBullet::~CBullet()
{
}

void CBullet::Load(wstring wsFile)
{
	__super::Load(wsFile);//부모클래스 CAniobj의 load사용

	OnChangeAni(AT_NORMAL);//애니메이션 상태변환
}

void CBullet::OnFrameMove(float fElapsedTime)//프레임 갱신
{
	__super::OnFrameMove(fElapsedTime);//부모클래스 프레임 갱신

	m_vPos += m_vDirectionVector * (m_fSpeed * fElapsedTime);//bullet위치는 현재 스피드, 현재시간, 방향벡터의 곱 더해주면서 갱신

	CGameObj* pEnemy = g_pGameObjMgr->OnFindTarget(this, g_pGameObjMgr->m_setPlayObj, this->GetRadius());//적 오브젝트 생성
	if (pEnemy == nullptr)//적이 없을경우 리턴
		return;

	pEnemy->OnDamage(this->GetDamage(), pEnemy);//적에게 데미지를 가함
	Destroy();//bullet 제거
}

void CBullet::OnFrameRender()
{
	__super::OnFrameRender();//부모클래스 frameRender
}

void CBullet::OnEndAni()
{
	Destroy();//bullet 제거
}