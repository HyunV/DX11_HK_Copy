#pragma once
#include "GameObject\GameObject.h"
class CDoor :
    public CGameObject
{
    friend class CScene;

protected:
    CDoor();
    CDoor(const CDoor& Obj);
    virtual ~CDoor();

private:
    CSharedPtr<class CColliderBox2D> m_Body;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CDoor* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);

public:
    void CollisionBegin(const CollisionResult& Result);
};

