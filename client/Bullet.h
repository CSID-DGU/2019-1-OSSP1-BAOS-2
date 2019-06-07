#pragma once

class CBullet : public CAniObj
{
private:
	D3DXVECTOR2 m_vDirectionVector;

public:
	CBullet();
	virtual ~CBullet();

	void SetDirectionVector(D3DXVECTOR2 vDirectionVector) {
		m_vDirectionVector = vDirectionVector;
	}

	virtual void Load(wstring wsFile);
	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender();

	virtual void OnEndAni();
};

