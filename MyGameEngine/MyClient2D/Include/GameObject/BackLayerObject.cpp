#include "BackLayerObject.h"
#include "Component/SpriteComponent.h"
#include "Resource/Material/Material.h"

CBackLayerObject::CBackLayerObject()
{
    SetTypeID<CBackLayerObject>();

    m_ObjectTypeName = "BackLayerObject";
}

CBackLayerObject::CBackLayerObject(const CBackLayerObject& Obj) :
    CGameObject(Obj)
{
    m_Sprite = (CSpriteComponent*)FindComponent("BackSprite");
}

CBackLayerObject::~CBackLayerObject()
{
}

void CBackLayerObject::Start()
{
    CGameObject::Start();

    //다른 구조들 배치
}

bool CBackLayerObject::Init()
{
    CGameObject::Init();

    m_Sprite = CreateComponent<CSpriteComponent>("BackSprite");
    SetRootComponent(m_Sprite);
    m_Sprite->SetPivot(0.5f, 0.5f);
    m_Sprite->SetTexture("BackMap", TEXT("Back.jpg"));
    m_Sprite->GetMaterial(0)->SetShader("TileMapBackShader");
    m_Sprite->SetWorldScale(1280.f, 720.f);
    m_Sprite->SetWorldPosition(640.f, 360.f);
    return true;
}

void CBackLayerObject::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
}

void CBackLayerObject::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

CBackLayerObject* CBackLayerObject::Clone() const
{
    return new CBackLayerObject(*this);
}
