#include "Zombie2.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Scene/Scene.h"
#include "Animation/Animation2D.h"
#include "Component/GravityAgent.h"
#include "Gio.h"
#include <time.h>

CZombie2::CZombie2()
{
    SetTypeID<CZombie2>();

    m_ObjectTypeName = "Zombie2";
}

CZombie2::CZombie2(const CZombie2& Obj)
{
    m_Body = (CColliderBox2D*)FindComponent("Zombie2Body"); //루트
    m_Sight = (CColliderBox2D*)FindComponent("Zombie2Sight");
    m_Sprite = (CSpriteComponent*)FindComponent("Zombie2Sprite");

    m_GravityAgent = (CGravityAgent*)FindComponent("Zombie2GravityAgent");
    m_Anim = CResourceManager::GetInst()->FindAnimation2D("Zombie2");
}

CZombie2::~CZombie2()
{
}

void CZombie2::SetSounds()
{
    CResourceManager::GetInst()->LoadSound("Effect", "MonWalk", true, "Enemy/zombie_five_footstep.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "MonAttack", false, "Enemy/zombie_shield_sword_1.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "MonDeath", false, "Enemy/zombie_death.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "MonDeathHit", false, "Enemy/enemy_death_sword.wav");
}

void CZombie2::SpriteAnimationSetting()
{
    m_Sprite->SetPivot(0.5f, 0.5f);

    float x = 239.f * g_SCALE;
    float y = 219.f * g_SCALE;
    m_Sprite->SetWorldScale(x, y);
    m_Sprite->SetRenderLayerName("Player");
    m_Sprite->GetMaterial(0)->SetRenderState("DepthDisable");
}

void CZombie2::SetAnimation()
{
    m_Anim->SetCurrentEndFunction("Zombie2_003_TurnOn", this, &CZombie2::ChangeDir);
    m_Anim->SetPlayScale("Zombie2_003_TurnOn", 5.f);

    m_Anim->SetCurrentEndFunction("Zombie2_004_Jump", this, &CZombie2::JumpEnd);
    m_Anim->SetPlayScale("Zombie2_004_Jump", 1.2f);
    
}

void CZombie2::Start()
{
    CGameObject::Start();
    //충돌세팅

    SetSounds();
    SpriteAnimationSetting();
    SetAnimation(); // 애니메이션 세팅
    srand((unsigned int)time(0));

    m_Sight->SetCollisionCallback(ECollision_Result::Collision, this, &CZombie2::SightCollisionBegin);

    m_Body->SetCollisionCallback(ECollision_Result::Collision, this, &CZombie2::CollisionBegin);

    SkillCoolDownInfo Attack = {};
    Attack.CoolDown = 2.f;
    m_vecCoolDown.push_back(Attack);
}

bool CZombie2::Init()
{
    CGameObject::Init();
    //컴포넌트
    m_Body = CreateComponent<CColliderBox2D>("Zombie2Body");
    m_Sight = CreateComponent<CColliderBox2D>("Zombie2Sight");
    m_Sprite = CreateComponent<CSpriteComponent>("Zombie2Sprite");
    // m_Body->SetName("Body");
    m_GravityAgent = CreateComponent<CGravityAgent>("Zombie2GravityAgent");
    //애니메이션
    m_Sprite->SetAnimationFile("Zombie2");
    m_Anim = m_Sprite->GetAnimation();
    m_Anim->SetCurrentAnimation("Zombie2_001_Idle");

    //계층구조
    SetRootComponent(m_Body);
    m_Body->AddChild(m_Sprite);
    m_Body->AddChild(m_Sight);

    m_Body->SetWorldPosition(100.f, 1200.f);
    m_Body->SetBoxSize(70.f, 140.f);
    m_Body->SetCollisionProfile("Monster");

    m_Sight->SetRelativePosition(-100.f, 0.f);
    m_Sight->SetBoxSize(80.f, 120.f);
    m_Sight->SetCollisionProfile("MonsterSight");

    m_GravityAgent->SetJumpVelocity(60.f);
    m_GravityAgent->SetGravityAccel(15.f);
    m_GravityAgent->SetPhysicsSimulate(true);
    m_CurState = EMonsterState::Idle;

    m_HP = 3;
    return true;
}

void CZombie2::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    CheckDir();

    //히트 머테리얼
    if (MaterialChangeTime >= 1.f)
    {
        MaterialChangeTime += DeltaTime;

        if (MaterialChangeTime >= 1.1f)
        {
            m_Sprite->GetMaterial(0)->SetBaseColor(1.f, 1.f, 1.f, 1.f);
            m_Sprite->GetMaterial(0)->SetOpacity(1.f);
            MaterialChangeTime = 0.f;
        }

    }

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
    case CZombie2::EMonsterState::Idle:
        break;
    case CZombie2::EMonsterState::Walk:
        m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * m_Dir * 100.f * g_DeltaTime);
        break;
    case CZombie2::EMonsterState::TurnOn:
        break;
    case CZombie2::EMonsterState::Attack: // 점프
        m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * m_Dir * 200.f * g_DeltaTime);
        break;
    case CZombie2::EMonsterState::Attacking:
        break;
    case CZombie2::EMonsterState::Death:
        if (m_GravityAgent->GetJump())
            m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * m_Dir * 80.f * g_DeltaTime);

        m_Time += DeltaTime;
        //죽으면 시간을 200초로 돌려놓고 멈춤. 그리고 3초 뒤
        if (m_Time >= 203.f)
        {
            float Opa = m_Sprite->GetMaterial(0)->GetOpacity();
            Opa -= DeltaTime;
            m_Sprite->GetMaterial(0)->SetOpacity(Opa);

            if (Opa <= 0.f)
                Destroy();
        }
        break;
    default:
        break;
    }

    if (m_CurState != EMonsterState::Death)
        m_Time -= DeltaTime;

    SetCurAnim(m_CurState);
}

void CZombie2::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

CZombie2* CZombie2::Clone() const
{
    return new CZombie2(*this);
}

void CZombie2::Attack()
{
    m_CurState = EMonsterState::Attack;
    m_Time = 1.f;

    m_vecCoolDown[0].CoolDownEnable = true;
    m_vecCoolDown[0].CoolDown = 1.f;
    //m_GravityAgent->Jump();
    m_GravityAgent->ObjectJump();
}

void CZombie2::JumpEnd()
{
    m_CurState = EMonsterState::Idle;
}

void CZombie2::CheckDir()
{
    //true 오른쪽 false 왼쪽
    bool Check = m_Sprite->GetTextureReverse();

    m_Dir = Check ? 1.f : -1.f;
    m_Angle = Check ? 0.f : 180.f;
}

void CZombie2::SetCurAnim(EMonsterState State)
{
    if (m_PrevState == State)
        return;

    switch (State)
    {
    case CZombie2::EMonsterState::Idle:
        m_Anim->SetCurrentAnimation("Zombie2_001_Idle");
        m_Time = 2.f;
        break;
    case CZombie2::EMonsterState::Walk:
        m_Anim->SetCurrentAnimation("Zombie2_002_Walk");
        //CResourceManager::GetInst()->SoundPlay("MonWalk");
        m_Time = 2.f;
        break;
    case CZombie2::EMonsterState::TurnOn:
        m_Anim->SetCurrentAnimation("Zombie2_003_TurnOn");
        break;
    case CZombie2::EMonsterState::Attack:
        m_Anim->SetCurrentAnimation("Zombie2_004_Jump");
        break;
    case CZombie2::EMonsterState::Attacking:
        break;
    case CZombie2::EMonsterState::Death:
        m_Anim->SetCurrentAnimation("Zombie2_006_Death");
        CResourceManager::GetInst()->SoundPlay("MonDeath");
        CResourceManager::GetInst()->SoundStop("MonWalk");
        break;
    default:
        break;
    }
    m_PrevState = State;
}

void CZombie2::ChangeDir()
{
    bool check = m_Sprite->GetTextureReverse();
    m_Sprite->SetTextureReverse(!check);
    //m_CurState = EMonsterState::Idle();
    m_Time = 0.f;
    m_Sight->SetRelativePosition(-90.f * m_Dir, 0.f);
}

void CZombie2::CreateGio()
{
    CScene* Scene = this->GetScene();

    int Count = (rand() % 5) + 1;

    for (int i = 0; i < Count; i++)
    {
        OutputDebugStringA("코인생성");
        CGio* Gio = Scene->CreateObject<CGio>("Gio");
        
        Vector3 v = this->GetWorldPos();
        Gio->SetWorldPosition(v);
        Gio->SetGravityPosGio(v.y);
        Gio->JumpGio();

        int Dir = rand() % 2;
        float x = 1.f;
        if (Dir == 0)
            x = -1.f;

        Gio->SetDir(x);

        int Range = (rand() + 300) % 300;
        Gio->SetRange((float)Range);
    }
}

void CZombie2::CollisionBegin(const CollisionResult& Result)
{
    std::string dest = Result.Dest->GetName();

    //공격 당하는 충돌일 시
    if (dest == "PlayerAttack" || dest == "PlayerBullet")
    {
        int Damage = 0;
        if (dest == "PlayerAttack")
            Damage = 1;
        else if (dest == "PlayerBullet")
            Damage = 3;

        OutputDebugStringA("좀비 맞음!");

        //색 변화 머테리얼
        m_Sprite->GetMaterial(0)->SetOpacity(0.7f);
        m_Sprite->GetMaterial(0)->SetBaseColor(255, 255, 255, 255);
        MaterialChangeTime = 1.f;

        //hp 감소
        m_HP -= Damage;
        if (m_HP <= 0) //사망
        {
            CreateGio();
            OutputDebugStringA("좀비 사망");
            CResourceManager::GetInst()->SoundPlay("MonDeathHit");
            m_GravityAgent->SetJumpVelocity(30.f);
            m_GravityAgent->ObjectJump();
            m_CurState = EMonsterState::Death;
            m_Body->SetEnable(false);
            m_Sight->SetEnable(false);
            m_Time = 200.f;
            m_Sprite->AddRelativePositionY(-20.f);


        }
    }
}

void CZombie2::SightCollisionBegin(const CollisionResult& Result)
{
    if (m_vecCoolDown[0].CoolDownEnable)
        return;
    OutputDebugStringA("시야들옴");
    m_CurState = EMonsterState::Attack;
    Attack();
    m_Time = 100.f;
}
