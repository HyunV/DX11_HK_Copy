#pragma once
#include "SceneComponent.h"
class CPrimitiveComponent :
    public CSceneComponent
{
    friend class CGameObject;

protected:
    CPrimitiveComponent();
    CPrimitiveComponent(const CPrimitiveComponent& component);
    virtual ~CPrimitiveComponent();

protected:
    CSharedPtr<class CMesh> m_Mesh;
    CSharedPtr<class CShader> m_Shader;

public:
    void SetMesh(const std::string& Name);
    void SetMesh(class CMesh* Mesh);
    void SetShader(const std::string& Name);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CPrimitiveComponent* Clone()    const;
};
