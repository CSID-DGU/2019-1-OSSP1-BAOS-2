#pragma once

class CICameraObj//ī�޶� ������Ʈ Ŭ����
{
public:
	CICameraObj() {}
	virtual ~CICameraObj() {}

	virtual const D3DXVECTOR2* GetPos() = 0;//ī�޶��� ��ġ ����
};

class CCamera//ī�޶� Ŭ����
{
private://
	CICameraObj* m_pObj;//ī�޶� ������Ʈ�� ����

	int m_iWidth;//ī�޶� �ʺ�
	int m_iHeight;//ī�޶� ����

	D3DXVECTOR2  m_vPos;//ī�޶� ��ġ
	bool m_bUse;//ī�޶� ��뿩��

public:
	bool IsUse() { return m_bUse; }//��������� Ȯ��
	void SetUse( bool bUse ) { m_bUse = bUse; }//����� ����

	int GetWidth() { return m_iWidth; }//�ʺ� �޾ƿ���
	int GetHeight() { return m_iHeight; }//���� �޾ƿ���

	D3DXVECTOR2 GetCameraPos(){ return m_vPos; }//ī�޶� ��ġ �޾ƿ���

public:
	CCamera(void);
	virtual ~CCamera(void);

	void InitSize( int iWidth, int iHeight );
	void OnFrameMove( float fElapsedTime );
	void OnUpdateScreen( float fElapsedTime );
	void SetCameraObj( CICameraObj* pObj ) { m_pObj = pObj; }
	void GetTransform( D3DXMATRIX * pmatTrans );
};

