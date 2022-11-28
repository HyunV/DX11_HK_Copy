#include "Zombie.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Scene/Scene.h"
#include "Animation/Animation2D.h"
#include "Component/GravityAgent.h"
#include <time.h>

CZombie::CZombie()
{
    SetTypeID<CZombie>();

    m_ObjectTypeName = "Zombie";
}

CZombie::CZombie(const CZombie& Obj)
{
    m_Body = (CColliderBox2D*)FindComponent("ZombieBody"); //루트
    m_Sight = (CColliderBox2D*)FindComponent("ZombieSight");
    m_Sprite = (CSpriteComponent*)FindComponent("ZombieSprite");
   
    m_GravityAgent = (CGravityAgent*)FindComponent("ZombieGravityAgent");
    m_Anim = CResourceManager::GetInst()->FindAnimation2D("Zombie");
}

CZombie::~CZombie()
{
}

void CZombie::Start()
{
    CGameObject::Start();
    //충돌세팅

    SetSounds();
    SpriteAnimationSetting();
    SetAnimation(); // 애니메이션 세팅
    srand((unsigned int)time(0));

    m_Sight->SetCollisionCallback(ECollision_Result::Collision, this, &CZombie::SightCollisionBegin);

    SkillCoolDownInfo Attack = {};
    Attack.CoolDown = 1.f;
    m_vecCoolDown.push_back(Attack);
}

bool CZombie::Init()
{
    CGameObject::Init();
    //컴포넌트
    m_Body = CreateComponent<CColliderBox2D>("ZombieBody");
    m_Sight = CreateComponent<CColliderBox2D>("ZombieSight");
    m_Sprite = CreateComponent<CSpriteComponent>("ZombieSprite");    
    m_Body->SetName("Body");
    m_GravityAgent = CreateComponent<CGravityAgent>("ZombieGravityAgent");
    //애니메이션
    m_Sprite->SetAnimationFile("Zombie");
    m_Anim = m_Sprite->GetAnimation();
    m_Anim->SetCurrentAnimation("Zombie_001_Idle");

    //계층구조
    SetRootComponent(m_Body);
    m_Body->AddChild(m_Sprite);
    m_Body->AddChild(m_Sight);

    m_Body->SetWorldPosition(450.f, 200.f);
    m_Body->SetBoxSize(90.f, 90.f);
    m_Body->SetCollisionProfile("Monster");

    m_Sight->SetRelativePosition(-90.f, 0.f);
    m_Sight->SetBoxSize(90.f, 90.f);
    m_Sight->SetCollisionProfile("MonsterSight");

    m_GravityAgent->SetPhysicsSimulate(true);
    m_CurState = EMonsterState::Idle;
    return true;
}

void CZombie::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    CheckDir();
    
    //쿨타임 돌리기
    size_t	Size = m_vecCoolDown.size();

    for (size_t i = 0; i < Size; ++i)
    {
        if (m_vecCoolDown[i].CoolDownEnable)
        {
            m_vecCoolDown[i].CoolDown -= DeltaTime;

            if (m_vecCoolDown[i].CoolDown <= 0.f)
                m_vecCoolDown[i].CoolDownEnable = false;
        }
    }

    if (m_Time <= 0.f)
    {
        int State = rand() % 3;
        m_CurState = (EMonsterState)State;
        m_Time = 2.f;
    }

    switch (m_CurState)
    {
    case CZombie::EMonsterState::Idle:
        break;
    case CZombie::EMonsterState::Walk:
        m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * m_Dir * 100.f * g_DeltaTime);
        break;
    case CZombie::EMonsterState::TurnOn:
        break;
    case CZombie::EMonsterState::Attack:
        break;
    case CZombie::EMonsterState::Attacking:
        m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * m_Dir * 1000.f * g_DeltaTime);
        break;
    case CZombie::EMonsterState::Death:
        break;
    default:
        break;
    }

    m_Time -= DeltaTime;
    SetCurAnim(m_CurState);
}

void CZombie::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

CZombie* CZombie::Clone() const
{
    return new CZombie(*this);
}

void CZombie::Attack()
{
    m_CurState = EMonsterState::Attacking;
    m_Time = 0.2f;

    m_vecCoolDown[0].CoolDownEnable = true;
    m_vecCoolDown[0].CoolDown = 1.f;
}

void CZombie::SetSounds()
{
}

void CZombie::SpriteAnimationSetting()
{
    m_Sprite->SetPivot(0.5f, 0.35f);

    float x = 239.f * g_SCALE;
    float y = 219.f * g_SCALE;
    m_Sprite->SetWorldScale(x, y);
    //m_Sprite->SetTextureReverse(true);
}

void CZombie::SetAnimation()
{
    m_Anim->SetCurrentEndFunction("Zombie_003_TurnOn", this, &CZombie::ChangeDir);
    m_Anim->SetPlayScale("Zombie_003_TurnOn", 5.f);
    
    m_Anim->SetCurrentEndFunction("Zombie_004_Attack", this, &CZombie::Attack);
    m_Anim->SetPlayScale("Zombie_004_Attack", 5.f);
}

void CZombie::CheckDir()
{
    //true 오른쪽 false 왼쪽
    bool Check = m_Sprite->GetTextureReverse();

    m_Dir = Check ? 1.f : -1.f;
    m_Angle = Check ? 0.f : 180.f;
}

void CZombie::SetNextState()
{
}

void CZombie::SetCurAnim(EMonsterState State)
{
    if (m_PrevState == State)
        return;

    switch (State)
    {
    case CZombie::EMonsterState::Idle:
        m_Anim->SetCurrentAnimation("Zombie_001_Idle");
        m_Time = 2.f;
        break;
    case CZombie::EMonsterState::Walk:
        m_Anim->SetCurrentAnimation("Zombie_002_Walk");
        m_Time = 2.f;
        break;
    case CZombie::EMonsterState::TurnOn:
        m_Anim->SetCurrentAnimation("Zombie_003_TurnOn");
        break;
    case CZombie::EMonsterState::Attack:
        m_Anim->SetCurrentAnimation("Zombie_004_Attack");
        break;
    case CZombie::EMonsterState::Attacking:
        m_Anim->SetCurrentAnimation("Zombie_005_Attacking");
        break;
    case CZombie::EMonsterState::Death:
        m_Anim->SetCurrentAnimation("Zombie_006_Death");
        break;
    default:
        break;
    }
    m_PrevState = State;
}

void CZombie::ChangeDir()
{
    bool check = m_Sprite->GetTextureReverse();
    m_Sprite->SetTextureReverse(!check);
    //m_CurState = EMonsterState::Idle();
    m_Time = 0.f;
    m_Sight->SetRelativePosition(-90.f *m_Dir, 0.f);
}

void CZombie::CollisionBegin(const CollisionResult& Result)
{
}

void CZombie::SightCollisionBegin(const CollisionResult& Result)
{
    if (m_vecCoolDown[0].CoolDownEnable)
        return;
    OutputDebugStringA("시야들옴");
    m_CurState = EMonsterState::Attack;
    m_Time = 100.f;
}
