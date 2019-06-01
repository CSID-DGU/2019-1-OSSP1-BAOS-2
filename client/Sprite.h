#pragma once

class CSprite//��������Ʈ, ������� �Է�Ű, ��ǥ�� ���� ���ϴ� �ൿ�̳� ������ �ϴ� �̹��� ���
{
private:
	LPD3DXSPRITE m_pSprite;

public:
	CSprite(void);
	virtual ~CSprite(void);

	LPD3DXSPRITE GetSprite() { return m_pSprite; }//��������Ʈ �ҷ�����

	void OnResetDevice();//����̽� ����
	void OnLostDevice(); //����̽� ������

	void OnBegin();		//����
	void OnEnd();		//��

	void SetTransform( D3DXMATRIX *pmatTrans );	//��ȯ ����
	void OnDraw( LPDIRECT3DTEXTURE9 pTexture	//��������Ʈ �׷��ֱ�
		, const RECT* pRect
		, float fX
		, float fY );
};

