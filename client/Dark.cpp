#include "DXUT.h"
#include "Home.h"

extern CGameObjMgr* g_pGameObjMgr;
extern GameDataMgr* g_pGameDataMgr;
extern CTexture* g_pTexture;

CDark::CDark(void) ://Dark Ŭ������ �ִ� ���� �ʱ�ȭ
	m_iViewID(0),
	m_fDarkUpdateTimer(0.0f),
	m_fDarkResetTimer(GameSettingIndex::UpdateDarkResetTime)
{
}


CDark::~CDark(void)//�Ҹ���
{
}

void CDark::Load(wstring wFile)
{
	if (m_pRender != NULL)//Render�� ���� �ִ°��
		return;

	const SObjData* pObjData = g_pGameDataMgr->GetObjData(wFile);//wFile�̸��� ������Ʈ ������ ���� �ҷ���
	if (pObjData == NULL)//������Ʈ �����͸� ���ҷ��������
		return;

	if (m_wObjName == L"Dark")//������Ʈ �̸��� Dark�ΰ��
	{
		m_vScl = pObjData->m_vScale;
		m_pRender = new CDarkRender(this);//Dark Render ����
	}

	if (m_wObjName == L"MiniDark")//������Ʈ�� �̴ϸ��ΰ��
	{
		m_vPos += D3DXVECTOR2(768, 512);//��ġ���� ���ظ�ŭ ������Ʈ ��ġ �̵�
		m_vScl = m_vScl * 2;//������ ����
		m_pRender = new CDarkRender(this);
		m_bCamera = false;
	}

	m_pRender->Load(pObjData->m_wFile);//wFile�� ������Ʈ �����͸� �ε�
	m_iViewID = g_pTexture->Load(L"Image/UI/View/CreatureView (0).png");//viewID�� �̹��� ��ġ���� �ε�
}

void CDark::ResetDark()//Dark reset
{
	m_fDarkResetTimer = GameSettingIndex::UpdateDarkResetTime;//Dark resetTime ����
	((CDarkRender*)m_pRender)->ClearDark();
}

void CDark::UpdateDark()//Dark Update
{
	m_fDarkUpdateTimer = GameSettingIndex::UpdateDarkTime;//Dark updatetime ����
	vector< CGameObj* > m_vecViewObj = g_pGameObjMgr->GetViewObj();//���� view ������Ʈ ������ ���ӿ�����Ʈ�Ŵ������� �ҷ���
	if (m_vecViewObj.empty() == false)//������� ���� ���
	{
		for (int i = 0; i <= (int)m_vecViewObj.size() - 1; ++i)
		{
			if (m_vecViewObj[i]->IsDestroy() == false)//���ŵ��� �ʾ��� ���
			{
				D3DXVECTOR2 vViewPos = *m_vecViewObj[i]->GetPos() / 16;//view ��ġ ����
				((CDarkRender*)m_pRender)->SetDarkMode(vViewPos, m_iViewID);
			}
		}
	}
}


void CDark::OnFrameMove(float fElapsedTime)//������ ����
{
	if (m_pRender != NULL)//������ �� ���� �������
		m_pRender->OnFrameMove(fElapsedTime);//������ ����

	if (m_pRender == nullptr)
		return;

	m_fDarkUpdateTimer -= fElapsedTime;//������Ʈ Ÿ�̸ӿ��� ����ð� ����
	m_fDarkResetTimer -= fElapsedTime;//���� Ÿ�̸ӿ��� ����ð� ���� 

	if (m_fDarkResetTimer <= 0.0f)//����Ÿ�̸Ӱ� 0������ ��� 
	{
		ResetDark();//���� ������ �ٽ� ������Ʈ
		UpdateDark();
	}

	if (m_fDarkUpdateTimer <= 0.0f)
	{
		UpdateDark();//���� ������Ʈ
	}
}