#pragma once
class CDarkRender : public CImgRender//Dark map Render
{
protected:
	void MakeAlpha(DWORD* pDark, DWORD* pView, D3DXVECTOR2 vPos, const STextureInfo* pDarkInfo, const STextureInfo* pViewInfo);

	const STextureInfo* m_pDarkInfo;//dark¿« texture ¡§∫∏
	DWORD* m_pDarkColor;

public:
	CDarkRender(CGameObj* pGameObj);
	virtual ~CDarkRender();

	virtual void Load(wstring wsFile);

	void ClearDark();
	void SetDarkMode(D3DXVECTOR2 vPos, int iTexture);
};

