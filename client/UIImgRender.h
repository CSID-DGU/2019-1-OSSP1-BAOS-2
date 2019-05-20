#pragma once

class CUIImgRender : public CRender
{
private:
	int m_iTexture;

	CRender* m_pRender;

private:
	CGameObj* m_pGameObj;

public:
	CUIImgRender( CGameObj* pGameObj );
	virtual ~CUIImgRender(void);

	virtual void Load( wstring wFile );
	virtual bool OnFrameMove( float fElapsedTime );
	virtual void OnFrameRender();

	virtual void UpdateWorld();
};

