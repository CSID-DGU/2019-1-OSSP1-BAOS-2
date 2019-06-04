#pragma once

enum EGAME_TEAM//�Ʊ� �� Enum
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

class CGameObj : public CICameraObj//ī�޶� ������Ʈ ���
{
protected:
	CRender* m_pRender;//render ����

	CGameObj* m_pDamager;//damage ó�� ������Ʈ ����

	wstring m_wObjName;//������Ʈ ��Ī ó�� ����

	D3DXVECTOR2 m_vPos;//��ġ ����
	D3DXVECTOR2 m_vGoalPos;//��ǥ ��ġ ����

	D3DXVECTOR2 m_vDirectionVector;//���⺤��

	D3DXVECTOR2 m_vScl;//������ ����
	D3DXVECTOR2 m_vImgSize;//�̹��� ������ ����

	vector< int > m_vecTextureID;//�ؽ��� id ���庤��

	//���� ������Ʈ���� ������ �־�� �� ���� ����
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

	virtual const D3DXVECTOR2* GetPos() { return &m_vPos; }//��ġ �ҷ�����
	virtual void SetPos(D3DXVECTOR2 vPos) { m_vPos = vPos; }//��ġ ����

	const D3DXVECTOR2 * GetScl() { return &m_vScl; }//������ �޾ƿ���
	void SetScl(D3DXVECTOR2 vScl) { m_vScl = vScl; }//������ ����

	const D3DXVECTOR2* GetDirectionVector() { return &m_vDirectionVector; }//���⺤�� ��������
	void SetDirectionVector(D3DXVECTOR2 vDirectionVector) { m_vDirectionVector = vDirectionVector; }//���⺤�� ����

	const D3DXVECTOR2 * GetImgSize() { return &m_vImgSize; }//�̹��� ������ ��������
	void SetImgSize(D3DXVECTOR2 vImgSize) { m_vImgSize = vImgSize; }//�̹��� ������ ����

	const D3DXVECTOR2 * GetGoalPos() { return &m_vGoalPos; }//��ǥ ��ġ ��������
	void SetGoalPos(D3DXVECTOR2 vGoalPos) { m_vGoalPos = vGoalPos; }//��ǥ ��ġ ����

	const wstring GetObjName() { return m_wObjName; }//������Ʈ �̸� ��������
	void SetObjName(wstring wObjName) { m_wObjName = wObjName; }//������Ʈ �̸� ����

	CRender* GetRender() { return m_pRender; }//���� �ҷ�����

	CGameObj* GetDamager() { return m_pDamager; }//������ ó�� ������Ʈ �ҷ�����

	vector< int > GetTextureID() { return m_vecTextureID; }//textureID ���� �ҷ�����
	void SetTextureID(vector< int > vecTextureID) { m_vecTextureID = vecTextureID; }//textureID ���� ����

	virtual int GetAniCategory() { return AT_NORMAL; }//�ִ� ī�װ� �ҷ�����, ����Ʈ�� NORMAL

	bool IsDestroy() { return m_bDestroy; }//�ı��Ǿ����� �˻�
	void Destroy() { m_bDestroy = true; }//�ı�

	int GetRenderType() { return m_iRenderType; }//����Ÿ�� �ҷ�����
	void SetRenderType(int iRenderType) { m_iRenderType = iRenderType; }//����Ÿ�� ����

	bool IsWork() { return m_bWork; }//�۵��ϴ��� Ȯ��
	void SetWork(bool bWork) { m_bWork = bWork; }//�۵� ����

	int GetMaxHealth() { return m_iMaxHealth; }//�ִ�ü�� ���� �ҷ�����
	void SetMaxHealth(int iMaxHealth) { m_iMaxHealth = iMaxHealth; }//�ִ�ü�� ����

	int GetMaxMana() { return m_iMaxMana; }//�ִ븶�� ���� �ҷ�����
	void SetMacMana(int iMaxMana) { m_iMaxMana = iMaxMana; }//�ִ븶�� ����

	float GetSpeed() { return m_fSpeed; }//���ǵ� ���� �ҷ�����
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }//���ǵ� ����

	int GetDamage() { return m_iDamage; }//������ �ҷ�����
	void SetDamage(int iDamage) { m_iDamage = iDamage; }//������ ����

	int GetScope() { return m_iScope; }//������ �ҷ�����
	void SetScope(int iScope) { m_iScope = iScope; }//������ ����

	int GetRadius() { return m_iRadius; }//������ �ҷ����� 
	void SetRadius(int iRadius) { m_iRadius = iRadius; }//������ ����

	int GetDirection() { return m_iDirection; }//���� �ҷ�����
	void SetDirection(int iDirection) { m_iDirection = iDirection; }//���� ����

	int GetHealth() { return m_iHealth; }//ü�� �ҷ�����
	void SetHealth(int iHealth) { m_iHealth = iHealth; }//ü�� ����

	int GetMana() { return m_iMana; }//���� �ҷ�����
	void SetMana(int iMana) { m_iMana = iMana; }//���� ����

	int GetTeam() { return m_iTeam; }//�� �ҷ�����
	void SetTeam(int iTeam) { m_iTeam = iTeam; }//�� ����

	bool IsCmeara() {//ī�޶� �����ϴ��� Ȯ��
		return m_bCamera;
	}

	void SetCameraUse(bool bCamera) {//ī�޶� ��뿩�� ����
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