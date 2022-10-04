#pragma once
#include "SceneComponent.h"

class CSectionComponent :
    public CSceneComponent
{
    friend class CGameObject;
    friend class CScene;

protected:
    CSectionComponent();
    virtual ~CSectionComponent();

protected:
    CSharedPtr<class CMesh> m_Mesh; //콜라이더에 쓸 메시
    CSharedPtr<class CShader> m_Shader; // 콜라이더에 쓸 쉐이더
    Vector4                 m_Color; //테두리 색
    std::vector<class CCollisionSection2D*> m_vecSection;
    CScene* m_Scene;

public:
    virtual bool Init();
    virtual void Start();
    virtual void PostUpdate(float DeltaTime);
    virtual void Update(float DeltaTime);
    virtual void Render();
};

