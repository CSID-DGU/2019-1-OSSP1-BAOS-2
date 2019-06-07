#include "DXUT.h"
#include "Home.h"

extern CGameObjMgr* g_pGameObjMgr;

CBullet::CBullet() :
	m_vDirectionVector(0.0f, 0.0f)//���� �� �ʱ�ȭ
{
}


CBullet::~CBullet()
{
}

void CBullet::Load(wstring wsFile)
{
	__super::Load(wsFile);//�θ�Ŭ���� CAniobj�� load���

	OnChangeAni(AT_NORMAL);//�ִϸ��̼� ���º�ȯ
}

void CBullet::OnFrameMove(float fElapsedTime)//������ ����
{
	__super::OnFrameMove(fElapsedTime);//�θ�Ŭ���� ������ ����

	m_vPos += m_vDirectionVector * (m_fSpeed * fElapsedTime);//bullet��ġ�� ���� ���ǵ�, ����ð�, ���⺤���� �� �����ָ鼭 ����

	CGameObj* pEnemy = g_pGameObjMgr->OnFindTarget(this, g_pGameObjMgr->m_setPlayObj, this->GetRadius());//�� ������Ʈ ����
	if (pEnemy == nullptr)//���� ������� ����
		return;

	pEnemy->OnDamage(this->GetDamage(), pEnemy);//������ �������� ����
	Destroy();//bullet ����
}

void CBullet::OnFrameRender()
{
	__super::OnFrameRender();//�θ�Ŭ���� frameRender
}

void CBullet::OnEndAni()
{
	Destroy();//bullet ����
}