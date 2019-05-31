#pragma once

class CMouse
{
private:
	D3DXVECTOR2 m_vRMousePos;//�����ʸ��콺
	D3DXVECTOR2 m_vLMousePos;//���ʸ��콺

	D3DXVECTOR2 m_vOneRMousePos;
	D3DXVECTOR2 m_vOneLMousePos;

	D3DXVECTOR2 m_vWorldMousePos;//ī�޶� ���콺��ġ
	D3DXVECTOR2 m_vMousePos;

	bool m_bRClick;//��Ŭ��
	bool m_bLClick;//��Ŭ��

	bool m_bOneRClick;
	bool m_bOneLClick;

	float m_fLMouseTime;
	float m_fRMouseTime;

private://���콺 ��ġ������ private�� ����
	void SetMousePos();//���콺��ġ����
	void SetWorldMousePos();//���帶�콺��ġ����

	void SetRMousePos( float fElapsedTime );
	void SetLMousePos( float fElapsedTime );

public:
	CMouse(void);
	virtual ~CMouse(void);
	
	D3DXVECTOR2 GetMousePos() { return m_vMousePos; }
	D3DXVECTOR2 GetWorldMousePos() { return m_vWorldMousePos; }

	D3DXVECTOR2 GetRMousePos() { return m_vRMousePos; }
	D3DXVECTOR2 GetLMousePos() { return m_vLMousePos; }

	D3DXVECTOR2 GetOneRMousePos() { return m_vOneRMousePos; }
	D3DXVECTOR2 GetOneLMousePos() { return m_vOneLMousePos; }

	bool IsRClick() { return m_bRClick; }//Ŭ���ߴ��� �˻�
	bool IsLClick() { return m_bLClick; }

	bool IsOneRClick() { return m_bOneRClick; }
	bool IsOneLClick() { return m_bOneLClick; }

public:
	void OnFrameMove( float fElapsedTime );//�������� �����̸鼭 �˻�
};

