#pragma once

class CGameObjController;

class CAniObj : public CGameObj //���� ������Ʈ ���
{
protected:
	int m_iAniCategory;//�ִ� ī�װ� index
	map< int, CRender* > m_mapAniRender;//Ani render ������ map ����ü

	int m_iInputIndex;//�Է¹��� index
	int m_iChangeIndex;//index ��ȯ
	int m_iNextAniCategory;//���� Ani index

	CGameObjController* m_pController;//���� ������Ʈ ��Ʈ�ѷ� ����

	bool m_bChangeNextAni;//���� Ani�� ��ȯ ���� ���� bool��

protected:
	virtual void OnEndAni();//Ani ����

public:
	CAniObj(void);
	virtual ~CAniObj(void);

	virtual void Load( wstring wFile );
	virtual void UnLoad();

	virtual void OnFrameMove( float fElapsedTime );
	virtual void OnFrameRender();

	CGameObjController* GetController() { return m_pController; }

	void OnChangeAni( int iAni );
	virtual int GetAniCategory() { return m_iAniCategory; }

	void SetNextAni( int iInputIndex, int iChangeIndex, int iAniCategory );
	void TryNextAni();
};

