#include "DXUT.h"
#include "Home.h"


CEffect::CEffect(void):
m_pTarget( NULL )
{
}


CEffect::~CEffect(void)
{
}

void CEffect::Load( wstring wFile )//wfile �ε�
{
	__super::Load( wFile );//�θ�Ŭ�����κ��� �ε�

	OnChangeAni( AT_NORMAL );//Normal ���·� ��ȯ
}

void CEffect::OnFrameMove( float fElapsedTime )//������ ����
{
	__super::OnFrameMove( fElapsedTime );//�θ�Ŭ�����κ��� ������ ����

	if( m_pTarget != NULL && m_pTarget->IsDestroy() == false )//Ÿ���� �����Ͽ�
		SetPos( *m_pTarget->GetPos() );//Ÿ���� ��ġ�� �޾ƿ� ��ġ ����

}

void CEffect::OnEndAni()//����
{
	Destroy();
}