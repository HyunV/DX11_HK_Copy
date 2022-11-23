#pragma once
#include "GameObject\GameObject.h"
class CBrum :
    public CGameObject
{
    friend class CScene;

protected:
    CBrum();
    CBrum(const CBrum& Obj);
    virtual ~CBrum();

protected:
    CSharedPtr<class CSpriteComponent>	m_Sprite;
    CSharedPtr<class CColliderBox2D>	m_Body;
private:
    bool m_Check;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CBrum* Clone()    const;

private:
    void CollisionBegin(const CollisionResult& Result);
    void CollisionEnd(const CollisionResult& Result);
};

