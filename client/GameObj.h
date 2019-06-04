#pragma once

enum EGAME_TEAM//아군 팀 Enum
{
	ETEAM_HERO,
	ETEAM_FRIEND,
	ETEAM_ENEMY,
	ETEAM_NENUTAL
};

enum EGAME_RENDER//game Render Enum
{
	ERENDER_NORMAL,
	ERENDER_DIRECTION,
	ERENDER_UI
};

class CRender;

class CGameObj : public CICameraObj//카메라 오브젝트 상속
{
protected:
	CRender* m_pRender;//render 생성

	CGameObj* m_pDamager;//damage 처리 오브젝트 생성

	wstring m_wObjName;//오브젝트 명칭 처리 설정

	D3DXVECTOR2 m_vPos;//위치 벡터
	D3DXVECTOR2 m_vGoalPos;//목표 위치 벡터

	D3DXVECTOR2 m_vDirectionVector;//방향벡터

	D3DXVECTOR2 m_vScl;//스케일 벡터
	D3DXVECTOR2 m_vImgSize;//이미지 사이즈 벡터

	vector< int > m_vecTextureID;//텍스쳐 id 저장벡터

	//게임 오브젝트들이 가지고 있어야 할 정보 세팅
	bool m_bDestroy;
	bool m_bWork;

	int m_iRenderType;

	float m_fSpeed;

	int m_iDirection;

	int m_iDamage;

	int m_iScope;
	int m_iRadius;

	int m_iCriticalDamage;
	int m_iCritiaclChance;

	int m_iMaxHealth;
	int m_iMaxMana;

	int m_iHealth;

	int m_iMana;

	int m_iTeam;

	bool m_bCamera;
	   
public:
	CGameObj(void);
	virtual ~CGameObj(void);

	virtual const D3DXVECTOR2* GetPos() { return &m_vPos; }//위치 불러오기
	virtual void SetPos(D3DXVECTOR2 vPos) { m_vPos = vPos; }//위치 설정

	const D3DXVECTOR2 * GetScl() { return &m_vScl; }//스케일 받아오기
	void SetScl(D3DXVECTOR2 vScl) { m_vScl = vScl; }//스케일 설정

	const D3DXVECTOR2* GetDirectionVector() { return &m_vDirectionVector; }//방향벡터 가져오기
	void SetDirectionVector(D3DXVECTOR2 vDirectionVector) { m_vDirectionVector = vDirectionVector; }//방향벡터 설정

	const D3DXVECTOR2 * GetImgSize() { return &m_vImgSize; }//이미지 사이즈 가져오기
	void SetImgSize(D3DXVECTOR2 vImgSize) { m_vImgSize = vImgSize; }//이미지 사이즈 설정

	const D3DXVECTOR2 * GetGoalPos() { return &m_vGoalPos; }//목표 위치 가져오기
	void SetGoalPos(D3DXVECTOR2 vGoalPos) { m_vGoalPos = vGoalPos; }//목표 위치 설정

	const wstring GetObjName() { return m_wObjName; }//오브젝트 이름 가져오기
	void SetObjName(wstring wObjName) { m_wObjName = wObjName; }//오브젝트 이름 설정

	CRender* GetRender() { return m_pRender; }//렌더 불러오기

	CGameObj* GetDamager() { return m_pDamager; }//데미지 처리 오브젝트 불러오기

	vector< int > GetTextureID() { return m_vecTextureID; }//textureID 벡터 불러오기
	void SetTextureID(vector< int > vecTextureID) { m_vecTextureID = vecTextureID; }//textureID 벡터 설정

	virtual int GetAniCategory() { return AT_NORMAL; }//애니 카테고리 불러오기, 디폴트는 NORMAL

	bool IsDestroy() { return m_bDestroy; }//파괴되었는지 검사
	void Destroy() { m_bDestroy = true; }//파괴

	int GetRenderType() { return m_iRenderType; }//렌더타입 불러오기
	void SetRenderType(int iRenderType) { m_iRenderType = iRenderType; }//렌더타입 설정

	bool IsWork() { return m_bWork; }//작동하는지 확인
	void SetWork(bool bWork) { m_bWork = bWork; }//작동 설정

	int GetMaxHealth() { return m_iMaxHealth; }//최대체력 정보 불러오기
	void SetMaxHealth(int iMaxHealth) { m_iMaxHealth = iMaxHealth; }//최대체력 설정

	int GetMaxMana() { return m_iMaxMana; }//최대마나 정보 불러오기
	void SetMacMana(int iMaxMana) { m_iMaxMana = iMaxMana; }//최대마나 설정

	float GetSpeed() { return m_fSpeed; }//스피드 정보 불러오기
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }//스피드 설정

	int GetDamage() { return m_iDamage; }//데미지 불러오기
	void SetDamage(int iDamage) { m_iDamage = iDamage; }//데미지 설정

	int GetScope() { return m_iScope; }//스코프 불러오기
	void SetScope(int iScope) { m_iScope = iScope; }//스코프 설정

	int GetRadius() { return m_iRadius; }//반지름 불러오기 
	void SetRadius(int iRadius) { m_iRadius = iRadius; }//반지름 설정

	int GetDirection() { return m_iDirection; }//방향 불러오기
	void SetDirection(int iDirection) { m_iDirection = iDirection; }//방향 설정

	int GetHealth() { return m_iHealth; }//체력 불러오기
	void SetHealth(int iHealth) { m_iHealth = iHealth; }//체력 설정

	int GetMana() { return m_iMana; }//마나 불러오기
	void SetMana(int iMana) { m_iMana = iMana; }//마나 설정

	int GetTeam() { return m_iTeam; }//팀 불러오기
	void SetTeam(int iTeam) { m_iTeam = iTeam; }//팀 설정

	bool IsCmeara() {//카메라 동작하는지 확인
		return m_bCamera;
	}

	void SetCameraUse(bool bCamera) {//카메라 사용여부 설정
		m_bCamera = bCamera;
	}

public:
	void OnAttack() {}
	virtual void OnDamage(int iDamage, CGameObj* pGameObj) {}

public:
	virtual void Load(wstring wFile) {};
	virtual void UnLoad();

	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender();

};