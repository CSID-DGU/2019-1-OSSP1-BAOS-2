#include "DXUT.h"
#include "Home.h"


CEffect::CEffect(void):
m_pTarget( NULL )
{
}


CEffect::~CEffect(void)
{
}

void CEffect::Load( wstring wFile )
{
	__super::Load( wFile );

	OnChangeAni( AT_NORMAL );
}

void CEffect::OnFrameMove( float fElapsedTime )
{
	__super::OnFrameMove( fElapsedTime );

	if( m_pTarget != NULL && m_pTarget->IsDestroy() == false )
		SetPos( *m_pTarget->GetPos() );

}

void CEffect::OnEndAni()
{
	Destroy();
}