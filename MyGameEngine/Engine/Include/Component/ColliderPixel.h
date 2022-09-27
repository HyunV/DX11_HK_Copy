#pragma once
#include "Collider2D.h"
class CColliderPixel :
    public CCollider2D
{
    friend class CGameObject;
    friend class CScene;

protected:
    CColliderPixel();
    CColliderPixel(const CColliderPixel& component);
    virtual ~CColliderPixel();

protected:

public:

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CColliderPixel* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

