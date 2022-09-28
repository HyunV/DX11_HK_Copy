#pragma once
#include "Collider2D.h"
class CColliderOBB2D :
    public CCollider2D
{
    friend class CGameObject;
    friend class CScene;

protected:
    CColliderOBB2D();
    CColliderOBB2D(const CColliderOBB2D& component);
    virtual ~CColliderOBB2D();

protected:

public:

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CColliderOBB2D* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
    virtual bool Collision(CCollider* Dest);
};

