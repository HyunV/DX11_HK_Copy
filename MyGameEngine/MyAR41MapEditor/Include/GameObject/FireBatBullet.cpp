#include "FireBatBullet.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Animation/Animation2D.h"

CFireBatBullet::CFireBatBullet()
{
    SetTypeID<CFireBatBullet>();

    m_ObjectTypeName = "FireBat";
}

CFireBatBullet::CFireBatBullet(const CFireBatBullet& Obj)   :
   	CGameObject(Obj)
{
}

CFireBatBullet::~CFireBatBullet()
{
}

void CFireBatBullet::SetDirection(float Dir)
{
    m_Dir = Dir;
}

void CFireBatBullet::SetTextureReverse(bool Enable)
{
    m_Sprite->SetTextureReverse(Enable);
}

void CFireBatBullet::Start()
{
    CGameObject::Start();
}

bool CFireBatBullet::Init()
{
    CGameObject::Init();
    SetLifeTime(2.f);

    m_Body = CreateComponent<CColliderBox2D>("FireBat");
    m_Sprite = CreateComponent<CSpriteComponent>("FireBatSprite");

    SetRootComponent(m_Body);
    m_Body->AddChild(m_Sprite);

    m_Body->SetBoxSize(100.f, 70.f);
    m_Body->SetCollisionProfile("MonsterAttack");

    m_Sprite->SetAnimationFile("GrimmBullet");
    CAnimation2D* Anim = m_Sprite->GetAnimation();
    Anim->SetCurrentAnimation("GrimmFireBatEffect");
    Anim->SetPlayScale("GrimmFireBatEffect", 3.f);

    m_Sprite->SetPivot(0.5f, 0.5f);
    m_Sprite->SetWorldScale(340.f * g_SCALE, 246.f * g_SCALE);

    m_Dir = 1.f;
    return true;
}

void CFireBatBullet::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
    AddWorldPositionX(m_Dir * 1800.f * DeltaTime);
}
