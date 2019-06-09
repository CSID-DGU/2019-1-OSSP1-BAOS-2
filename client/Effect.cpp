#include "DXUT.h"
#include "Home.h"


CEffect::CEffect(void):
m_pTarget( NULL )
{
}


CEffect::~CEffect(void)
{
}

void CEffect::Load( wstring wFile )//wfile 로드
{
	__super::Load( wFile );//부모클래스로부터 로드

	OnChangeAni( AT_NORMAL );//Normal 상태로 전환
}

void CEffect::OnFrameMove( float fElapsedTime )//프레임 갱신
{
	__super::OnFrameMove( fElapsedTime );//부모클래스로부터 프레임 갱신

	if( m_pTarget != NULL && m_pTarget->IsDestroy() == false )//타겟이 있을겅우
		SetPos( *m_pTarget->GetPos() );//타겟의 위치를 받아와 위치 설정

}

void CEffect::OnEndAni()//제거
{
	Destroy();
}