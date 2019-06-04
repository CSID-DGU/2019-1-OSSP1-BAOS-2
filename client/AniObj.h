#pragma once

class CGameObjController;

class CAniObj : public CGameObj //게임 오브젝트 상속
{
protected:
	int m_iAniCategory;//애니 카테고리 index
	map< int, CRender* > m_mapAniRender;//Ani render 저장할 map 구조체

	int m_iInputIndex;//입력받은 index
	int m_iChangeIndex;//index 변환
	int m_iNextAniCategory;//다음 Ani index

	CGameObjController* m_pController;//게임 오브젝트 컨트롤러 생성

	bool m_bChangeNextAni;//다음 Ani로 변환 결정 위한 bool형

protected:
	virtual void OnEndAni();//Ani 종료

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

