#pragma once
#include "GameObject\GameObject.h"
class CZombie2 :
    public CGameObject
{
    friend class CScene;

protected:
	CZombie2();
	CZombie2(const CZombie2& Obj);
	virtual ~CZombie2();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CColliderBox2D>	m_Body;
	//CSharedPtr<class CColliderPixel>	m_Body;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CZombie2* Clone()    const;
};

