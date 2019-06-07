#include "DXUT.h"
#include "Home.h"

extern GameDataMgr* g_pGameDataMgr;

CHealth::CHealth(void) ://�÷��̾� �ʱ�ȭ
	m_pPlayer(nullptr)
{
}


CHealth::~CHealth(void)
{
}

void CHealth::Load(wstring wFile)
{
	if (m_pRender != NULL)
		return;

	const SObjData* pObjData = g_pGameDataMgr->GetObjData(wFile);//������Ʈ������ ���� �ҷ�����
	if (pObjData == NULL)
		return;

	m_pRender = new CImgRender(this);//Render �Ҵ�
	m_pRender->Load(pObjData->m_wFile);//������Ʈ ������ Render
}

void CHealth::OnFrameMove(float fElapsedTime)//������ ����
{
	__super::OnFrameMove(fElapsedTime);

	if (m_pPlayer != nullptr)
	{
		if (m_pPlayer->IsDestroy())//�÷��̾ ���ŵǾ�����
		{
			Destroy();//����
			m_vScl.x = 0.0f;
			return;
		}

		//�÷��̾� ��ġ ����
		m_vPos = *m_pPlayer->GetPos();
		m_vPos -= D3DXVECTOR2(22.5, 0);


		if (m_pPlayer->GetHealth() == m_pPlayer->GetMaxHealth())//ü���� �̹� �ִ�ü���̸� return
			return;

		if (m_pPlayer->GetHealth() <= 0)//ü���� 0���ϸ� 
		{
			m_vScl.x = 0.0f;//�������� 0
			return;
		}

		//������ ����
		//�÷��̾� ü��/�ִ�ü��
		m_vScl.x = ((float)m_pPlayer->GetHealth() / (float)m_pPlayer->GetMaxHealth());
	}
}