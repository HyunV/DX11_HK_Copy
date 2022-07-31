#pragma once
#include "Ref.h"

class CGameObject :
    public CRef
{
    friend class CScene;

protected:
    CGameObject();
    CGameObject(const CGameObject& Obj);
    virtual ~CGameObject();

public:
    void Start();
    bool Init();
    void Update(float DeltaTime);
    void PostUpdate(float DeltaTime);
    CGameObject* Clone() const;
};

