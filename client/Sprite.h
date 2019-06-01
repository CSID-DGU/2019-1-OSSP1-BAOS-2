#pragma once

class CSprite//스프라이트, 사용자의 입력키, 좌표에 따라 원하는 행동이나 동작을 하는 이미지 출력
{
private:
	LPD3DXSPRITE m_pSprite;

public:
	CSprite(void);
	virtual ~CSprite(void);

	LPD3DXSPRITE GetSprite() { return m_pSprite; }//스프라이트 불러오기

	void OnResetDevice();//디바이스 리셋
	void OnLostDevice(); //디바이스 놓아줌

	void OnBegin();		//시작
	void OnEnd();		//끝

	void SetTransform( D3DXMATRIX *pmatTrans );	//전환 설정
	void OnDraw( LPDIRECT3DTEXTURE9 pTexture	//스프라이트 그려주기
		, const RECT* pRect
		, float fX
		, float fY );
};

