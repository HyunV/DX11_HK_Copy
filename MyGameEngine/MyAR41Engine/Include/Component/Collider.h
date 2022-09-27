#pragma once
#include "SceneComponent.h"
class CCollider :
    public CSceneComponent
{
    friend class CGameObject;
    friend class CScene;

protected:
    CCollider();
    CCollider(const CCollider& component);
    virtual ~CCollider();

protected:
    CSharedPtr<class CMesh> m_Mesh;
    Vector3                 m_Color;
    ECollider_Type          m_ColliderType;
    Vector3                 m_Min;
    Vector3                 m_Max;

public:
    const Vector3& GetMin() const
    {
        return m_Min;
    }

    const Vector3& GetMax() const
    {
        return m_Max;
    }

    ECollider_Type GetColliderType()    const
    {
        return m_ColliderType;
    }

public: 
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CCollider* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

