#pragma once

class CICameraObj//카메라 오브젝트 클래스
{
public:
	CICameraObj() {}
	virtual ~CICameraObj() {}

	virtual const D3DXVECTOR2* GetPos() = 0;//카메라의 위치 리턴
};

class CCamera//카메라 클래스
{
private://
	CICameraObj* m_pObj;//카메라 오브젝트를 생성

	int m_iWidth;//카메라 너비
	int m_iHeight;//카메라 높이

	D3DXVECTOR2  m_vPos;//카메라 위치
	bool m_bUse;//카메라 사용여부

public:
	bool IsUse() { return m_bUse; }//사용중인지 확인
	void SetUse( bool bUse ) { m_bUse = bUse; }//사용중 설정

	int GetWidth() { return m_iWidth; }//너비 받아오기
	int GetHeight() { return m_iHeight; }//높이 받아오기

	D3DXVECTOR2 GetCameraPos(){ return m_vPos; }//카메라 위치 받아오기

public:
	CCamera(void);
	virtual ~CCamera(void);

	void InitSize( int iWidth, int iHeight );
	void OnFrameMove( float fElapsedTime );
	void OnUpdateScreen( float fElapsedTime );
	void SetCameraObj( CICameraObj* pObj ) { m_pObj = pObj; }
	void GetTransform( D3DXMATRIX * pmatTrans );
};

