#pragma once
#include "GameObject\GameObject.h"
class CGlobalWall :
    public CGameObject
{
    friend class CScene;

protected:
    CGlobalWall();
    CGlobalWall(const CGlobalWall& Obj);
    virtual ~CGlobalWall();

protected:
    //CSharedPtr<class CSpriteComponent>	m_Sprite;
    CSharedPtr<class CColliderBox2D>	m_Wall;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CGlobalWall* Clone()    const;

private:
    void CollisionCallback(const CollisionResult& Result);
};

