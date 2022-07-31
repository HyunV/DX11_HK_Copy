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
    ComponentType m_ComponentType;

public:
    ComponentType GetComponentType() const
    {
        return m_ComponentType;
    }

public:
    void Start();
    bool Init();
    void Update(float DeltaTime);
    void PostUpdate(float DeltaTime);
    void Render();
    CComponent* Clone() const;
};

