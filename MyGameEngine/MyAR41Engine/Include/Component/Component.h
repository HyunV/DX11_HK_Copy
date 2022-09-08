#pragma once

#include "../Ref.h"

class CComponent :
    public CRef
{
    friend class CGameObject;

protected:
    CComponent();
    CComponent(const CComponent& Obj);
    virtual ~CComponent() = 0;

protected:
    ComponentType   m_ComponentType;
    class CScene* m_Scene;
    class CGameObject* m_Owner;
    std::string m_ComponentTypeName;

public:
    const std::string& GetComponentTypeName() const
    {
        return m_ComponentTypeName;
    }
    class CScene* GetScene()    const
    {
        return m_Scene;
    }

    class CGameObject* GetOwner()   const
    {
        return m_Owner;
    }

    virtual void SetScene(class CScene* Scene)
    {
        m_Scene = Scene;
    }

    virtual void SetOwner(class CGameObject* Owner)
    {
        m_Owner = Owner;
    }

    ComponentType GetComponentType()    const
    {
        return m_ComponentType;
    }

public:
    virtual void Destroy();
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CComponent* Clone()    const;
};


