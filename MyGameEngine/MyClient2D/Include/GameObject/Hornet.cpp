#include "Hornet.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Animation/Animation2D.h"
#include "Resource/ResourceManager.h" 

CHornet::CHornet()
{
    SetTypeID<CHornet>();
    m_ObjectTypeName = "Hornet";
}

CHornet::CHornet(const CHornet& Obj)    :
    CGameObject(Obj)
{
    m_Body = (CColliderBox2D*)FindComponent("HornetBody");
    m_Sprite = (CSpriteComponent*)FindComponent("HornetSprite");
}

CHornet::~CHornet()
{
}

void CHornet::Start()
{
    CGameObject::Start();

    m_Body->SetCollisionCallback(ECollision_Result::Collision, this,
        &CHornet::CollisionCallback);

    CAnimation2D* Anim = m_Sprite->GetAnimation();
    Anim->SetCurrentAnimation("HonnetIdle");
}

bool CHornet::Init()
{
    CGameObject::Init();
    m_Body = CreateComponent<CColliderBox2D>("HornetBody");
    m_Sprite = CreateComponent<CSpriteComponent>("HornetSprite");

    SetRootComponent(m_Sprite);

    m_Body->SetCollisionProfile("NPC");
    m_Sprite->SetAnimationFile("NPCS");

    //float x = 381.f;
    //float y = 249.f;
    float x = 381.f * g_SCALE;
    float y = 249.f * g_SCALE;

    m_Sprite->SetWorldPosition(100.f, 100.f);
    m_Sprite->SetWorldScale(x, y);
    m_Sprite->SetPivot(0.5f, 0.5f);

    //CAnimation2D* Anim = m_Sprite->GetAnimation();
    //Anim->SetCurrentAnimation("HonnetIdle");

    m_Sprite->AddChild(m_Body);
    m_Body->SetBoxSize(100.f, 120.f);

    m_Sprite->SetTextureReverse(false);

    return true;
}

void CHornet::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
}

void CHornet::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

CHornet* CHornet::Clone() const
{
    return new CHornet(*this);
}

void CHornet::CollisionCallback(const CollisionResult& Result)
{
    //닿은지점 확인해서 방향전환
}
