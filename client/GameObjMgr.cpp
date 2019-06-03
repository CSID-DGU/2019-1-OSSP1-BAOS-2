#include "DXUT.h"
#include "Home.h"

CGameObjMgr::CGameObjMgr(void)
{
}


CGameObjMgr::~CGameObjMgr(void)
{
}

CGameObj* CGameObjMgr::Alloc(int iType)
{
	switch (iType)//�޾ƿ� Ÿ�Կ� �´� ������Ʈ �Ҵ�
	{
	case EGAMEOBJ_TILE: return new CTile;
	case EGAMEOBJ_BEGINEFFECT: return new CEffect;
	case EGAMEOBJ_PLAYER: return new CPlayer;
	case EGAMEOBJ_CREATURE: return new CCreature;
	case EGAMEOBJ_TOWER: return new CTower;
	case EGAMEOBJ_HEALTH: return new CHealth;
	case EGAMEOBJ_EFFECT: return new CEffect;
	case EGAMEOBJ_DARK: return new CDark;
	case EGAMEOBJ_MINIDARK: return new CDark;
	}

	return NULL;
}

void CGameObjMgr::OnFrameMove(float fElapsedTime)//�����ӹ��� 
{
	PostProcess();

	for each(map< int, vector< CGameObj* >>::const_reference mr in m_mapObj)//map_obj�� ������ ������
	{
		OnFrameMove(mr.second, fElapsedTime);

		if (m_setPlayObj.find(mr.first) != m_setPlayObj.end())
			for each(vector<CGameObj*>::const_reference vr in mr.second)
				NoneOverLap(vr);
	}
}

void CGameObjMgr::OnFrameMove(const std::vector<CGameObj*> &vecObj, float fElapsedTime)//�����ӹ���
{
	for each(vector<CGameObj*>::const_reference vr in vecObj)
	{
		vr->OnFrameMove(fElapsedTime);
	}
}

void CGameObjMgr::OnFrameRender()
{
	SetRenderList();//���� ����Ʈ ����

	for each(map< int, vector<CGameObj*>>::const_reference mr in m_mapObj)
	{
		if (m_setPlayObj.find(mr.first) == m_setPlayObj.end())
			OnFrameRender(mr.second);
		else
			ListFrameRender();
	}
}

void CGameObjMgr::OnFrameRender(const std::vector<CGameObj*> &vecObj)//���ӿ�����Ʈ ������ ������
{
	for each(vector<CGameObj*>::const_reference vr in vecObj)
	{
		vr->OnFrameRender();
	}
}

void CGameObjMgr::ListFrameRender()//�����ӷ��� ����Ʈ
{
	set< float >::iterator sit = m_setRenderList.begin();
	for (sit; sit != m_setRenderList.end(); ++sit)
	{
		multimap< float, CGameObj* >::iterator mit = m_mapRenderObj.find(*sit);
		if (mit != m_mapRenderObj.end())
			mit->second->OnFrameRender();
	}
}
