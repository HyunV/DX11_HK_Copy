#pragma once
#include "GameObject\GameObject.h"
class CHornet :
    public CGameObject
{
    friend class CScene;

protected:
    CHornet();
    CHornet(const CHornet& Obj);
    virtual ~CHornet();

protected:
    CSharedPtr<class CSpriteComponent>	m_Sprite;
    CSharedPtr<class CColliderBox2D>	m_Body;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CHornet* Clone()    const;

private:
    void CollisionCallback(const CollisionResult& Result);
};

