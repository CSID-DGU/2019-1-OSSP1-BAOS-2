#pragma once

class CGameTileMgr;

class CPlayer : public CAniObj //�ִϿ�����Ʈ ���
{
	//�÷��̾� ������Ʈ
public:
	CPlayer(void);
	virtual ~CPlayer(void);

	float m_fTime;

	virtual void Load( wstring wFile );
	virtual void OnFrameMove( float fElapsedTime );
	virtual void OnDamage(int iDamage, CGameObj* pGameObj);
};

