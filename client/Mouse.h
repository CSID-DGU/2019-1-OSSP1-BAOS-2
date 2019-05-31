#pragma once

class CMouse
{
private:
	D3DXVECTOR2 m_vRMousePos;//오른쪽마우스
	D3DXVECTOR2 m_vLMousePos;//왼쪽마우스

	D3DXVECTOR2 m_vOneRMousePos;
	D3DXVECTOR2 m_vOneLMousePos;

	D3DXVECTOR2 m_vWorldMousePos;//카메라 마우스위치
	D3DXVECTOR2 m_vMousePos;

	bool m_bRClick;//우클릭
	bool m_bLClick;//좌클릭

	bool m_bOneRClick;
	bool m_bOneLClick;

	float m_fLMouseTime;
	float m_fRMouseTime;

private://마우스 위치설정은 private로 지정
	void SetMousePos();//마우스위치설정
	void SetWorldMousePos();//월드마우스위치설정

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

	bool IsRClick() { return m_bRClick; }//클릭했는지 검사
	bool IsLClick() { return m_bLClick; }

	bool IsOneRClick() { return m_bOneRClick; }
	bool IsOneLClick() { return m_bOneLClick; }

public:
	void OnFrameMove( float fElapsedTime );//프레임을 움직이면서 검사
};

