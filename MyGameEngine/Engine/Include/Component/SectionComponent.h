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
    CSharedPtr<class CMesh> m_Mesh; //�ݶ��̴��� �� �޽�
    CSharedPtr<class CShader> m_Shader; // �ݶ��̴��� �� ���̴�
    Vector4                 m_Color; //�׵θ� ��
    std::vector<class CCollisionSection2D*> m_vecSection;
    CScene* m_Scene;

public:
    virtual bool Init();
    virtual void Start();
    virtual void PostUpdate(float DeltaTime);
    virtual void Update(float DeltaTime);
    virtual void Render();
};

