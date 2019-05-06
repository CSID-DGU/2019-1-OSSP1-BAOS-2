#pragma once

class CMouse
{
private:
	D3DXVECTOR2 m_vRMousePos;
	D3DXVECTOR2 m_vLMousePos;

	D3DXVECTOR2 m_vOneRMousePos;
	D3DXVECTOR2 m_vOneLMousePos;

	D3DXVECTOR2 m_vWorldMousePos;
	D3DXVECTOR2 m_vMousePos;

	bool m_bRClick;
	bool m_bLClick;

	bool m_bOneRClick;
	bool m_bOneLClick;

	float m_fLMouseTime;
	float m_fRMouseTime;

private:
	void SetMousePos();
	void SetWorldMousePos();

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

	bool IsRClick() { return m_bRClick; }
	bool IsLClick() { return m_bLClick; }

	bool IsOneRClick() { return m_bOneRClick; }
	bool IsOneLClick() { return m_bOneLClick; }

public:
	void OnFrameMove( float fElapsedTime );
};

