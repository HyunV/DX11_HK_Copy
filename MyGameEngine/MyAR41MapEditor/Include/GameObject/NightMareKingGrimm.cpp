#include "NightMareKingGrimm.h"
#include "Component/SceneComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Scene/Scene.h"
#include "Animation/Animation2D.h"
#include "Component/GravityAgent.h"
#include "FireBatBullet.h"
#include "FlameParticle.h"
#include "FirePillarBullet.h"

#include <time.h>
#include "Player2D.h"
//#include "Resource/Material/Material.h"

CNightMareKingGrimm::CNightMareKingGrimm()
{
    SetTypeID<CNightMareKingGrimm>();

    m_ObjectTypeName = "NightMareKingGrimm";
}

CNightMareKingGrimm::CNightMareKingGrimm(const CNightMareKingGrimm& Obj)    :
    CGameObject(Obj)
{
    m_Main = (CSceneComponent*)FindComponent("GrimmMain");
    m_Sprite = (CSpriteComponent*)FindComponent("GrimmSprite");
    m_Body = (CColliderBox2D*)FindComponent("GrimmBody"); //루트
    
    //m_DashDownSprite = (CSpriteComponent*)FindComponent("DashDownSprite");
    //m_DashGroundSprite = (CSpriteComponent*)FindComponent("DashGroundSprite");

    m_GravityAgent = (CGravityAgent*)FindComponent("GravityAgent");

    m_Anim = CResourceManager::GetInst()->FindAnimation2D("NightMareKingGrimm");
}

CNightMareKingGrimm::~CNightMareKingGrimm()
{
    m_Anim->ClearAllNotify();
}

void CNightMareKingGrimm::SetSounds()
{
    CResourceManager::GetInst()->LoadSound("Effect", "BossAttack", false, "Boss/Grimm_attack_01.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "BossBalloon", true, "Boss/grimm_balloon_shooting_fireballs_loop.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "BossCapeOpen", false, "Boss/grimm_cape_open_for_cast.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "BossUpperBoom", false, "Boss/grimm_explode_into_bats.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "BossFireBat", false, "Boss/grimm_fireball_cast.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "BossSpikeStart", false, "Boss/grimm_spikes_pt_1_grounded.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "BossSpikeOn", false, "Boss/grimm_spikes_pt_2_shoot_up.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "BossTeleIn", false, "Boss/grimm_teleport_in.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "BossTeleOut", false, "Boss/grimm_teleport_out.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "BossSlash", false, "Boss/sword_5.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "BossFallDash", false, "Boss/falldash.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "BossGroundDash", false, "Boss/grounddash.wav");


}

void CNightMareKingGrimm::SetAnimation()
{
    //애니메이션 스케일, 함수 세팅
    m_Anim->SetPlayScale("Grimm001 FirePillar", 2.f);

    m_Anim->SetPlayScale("Grimm002 TeleIn", 2.f);
    m_Anim->SetCurrentEndFunction("Grimm002 TeleIn", this, &CNightMareKingGrimm::TeleportIn);

    m_Anim->SetPlayScale("Grimm003 TeleOut", 3.f);
    m_Anim->SetCurrentEndFunction("Grimm003 TeleOut", this, &CNightMareKingGrimm::TeleportOut);

    m_Anim->SetPlayScale("Grimm004 AirDashDown", 5.f);
    m_Anim->SetCurrentEndFunction("Grimm004 AirDashDown", this, &CNightMareKingGrimm::AirDashStart);

    m_Anim->SetPlayScale("Grimm005 AirDashStart", 3.f);
    m_Anim->SetCurrentEndFunction("Grimm005 AirDashStart", this, &CNightMareKingGrimm::FallStart);

    m_Anim->SetPlayScale("Grimm006 AirDashFall", 2.f);

    m_Anim->SetPlayScale("Grimm007 AirDashFallEffect", 2.f);

    m_Anim->SetPlayScale("Grimm008 GroundDashStart", 2.f);

    m_Anim->SetPlayScale("Grimm009 GroundDashing", 8.f);

    m_Anim->SetPlayScale("Grimm010 GroundDashEffect", 2.f);

    m_Anim->SetPlayScale("Grimm011 FireBat", 3.f);
    m_Anim->SetLoop("Grimm011 FireBat", true);

    m_Anim->SetPlayScale("Grimm012 FireBatEnd", 5.f);
    m_Anim->SetCurrentEndFunction("Grimm012 FireBatEnd", this, &CNightMareKingGrimm::FireBatEnd);

    m_Anim->SetPlayScale("Grimm013 SlashStart", 3.f);
    m_Anim->SetCurrentEndFunction("Grimm013 SlashStart", this, &CNightMareKingGrimm::Slash);

    m_Anim->SetPlayScale("Grimm014 Slash", 10.f);

    m_Anim->SetPlayScale("Grimm015 Uppercut", 1.f);

    m_Anim->SetPlayScale("Grimm016 UppercutEnd", 2.f);

    m_Anim->SetPlayScale("Grimm017 BallonAnticOn", 2.f);

    m_Anim->SetPlayScale("Grimm018 BalloonOn", 2.f);

    m_Anim->SetPlayScale("Grimm019 BalloonEndOn", 2.f);

    m_Anim->SetPlayScale("Grimm020 Death", 2.f);
}

void CNightMareKingGrimm::SpriteAnimationSetting()
{

    //m_DashDownSprite->SetAnimationFile("NightMareKingGrimm");
    //m_DashDownSprite->SetWorldScale(450.f, 573.f);
    //m_DashDownSprite->SetPivot(0.5f, 0.f);

    //CAnimation2D* Anim = m_DashDownSprite->GetAnimation();
    //Anim->SetCurrentAnimation("Grimm007 AirDashFallEffect");
    //Anim->SetLoop("Grimm007 AirDashFallEffect", true);

    //m_DashGroundSprite->SetAnimationFile("NightMareKingGrimm");
    //m_DashGroundSprite->SetWorldScale(832.f, 369.f);
    //m_DashGroundSprite->SetPivot(0.5f, 0.f);

    //CAnimation2D* Anim2 = m_DashGroundSprite->GetAnimation();
    //Anim2->SetCurrentAnimation("Grimm007 AirDashFallEffect");
    //Anim2->SetLoop("Grimm010 GroundDashEffect", true);
}

void CNightMareKingGrimm::SetCurAnim(EBossState State)
{
    //애니메이션 세팅할때 이전 상태랑 같은거면 리턴
    if (m_PrevState == State)
        return;


    Vector3 Pos = m_Sprite->GetWorldPos();
    Vector2 Scale;
    float pivot = 0.f;

    m_Body->SetWorldPosition(Pos);

    switch (State)
    {
    case CNightMareKingGrimm::EBossState::Idle:
        m_Anim->SetCurrentAnimation("Grimm001 FirePillar");

        Scale = Vector2(374.f * g_SCALE, 541.f * g_SCALE);
        m_Body->SetBoxSize(200.f, 320.f);
        
        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionY(pivot);

        break;
    case CNightMareKingGrimm::EBossState::TeleIn:
        m_Anim->SetCurrentAnimation("Grimm002 TeleIn");
        CResourceManager::GetInst()->SoundPlay("BossTeleIn");
        CResourceManager::GetInst()->SoundPlay("BossCapeOpen");
        

        Scale = Vector2(315.f * g_SCALE, 444.f * g_SCALE);      
        m_Body->SetBoxSize(Scale.x -60.f, Scale.y);

        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionY(pivot);
        m_Body->SetEnable(true);

        break;
    case CNightMareKingGrimm::EBossState::TeleOut:
        CResourceManager::GetInst()->SoundPlay("BossCapeOpen");
        CResourceManager::GetInst()->SoundPlay("BossTeleOut");
        m_Anim->SetCurrentAnimation("Grimm003 TeleOut");
       
        Scale = Vector2(315.f * g_SCALE, 444.f * g_SCALE);
        m_Body->SetBoxSize(Scale.x - 60.f, Scale.y);

        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionY(pivot);

        break;
    case CNightMareKingGrimm::EBossState::AirDashDown:
        m_Anim->SetCurrentAnimation("Grimm004 AirDashDown");

        Scale = Vector2(900.f * g_SCALE, 525.f * g_SCALE);
        m_Body->SetBoxSize(295.f, 170.f);

        m_Body->AddWorldPositionY(120.f);

        break;
    case CNightMareKingGrimm::EBossState::AirDashStart:
        m_Anim->SetCurrentAnimation("Grimm005 AirDashStart");

        Scale = Vector2(900.f * g_SCALE, 525.f * g_SCALE);
        m_Body->SetBoxSize(170.f, 290.f);

        pivot = m_Sprite->GetWorldScale().y * 0.5f;
        m_Body->AddWorldPositionY(pivot);

        break;
    case CNightMareKingGrimm::EBossState::AirDashFall:
        m_Anim->SetCurrentAnimation("Grimm006 AirDashFall");
        CResourceManager::GetInst()->SoundPlay("BossFallDash");

        Scale = Vector2(900.f * g_SCALE, 525.f * g_SCALE);
        m_Body->SetBoxSize(20.f, 20.f);

        m_Body->AddWorldPositionY(50.f);
        //m_Main->AddWorldRotationZ(130.f);

        break;
    case CNightMareKingGrimm::EBossState::GroundDashStart:
        m_Anim->SetCurrentAnimation("Grimm008 GroundDashStart");
        CResourceManager::GetInst()->SoundPlay("BossGroundDash");

        Scale = Vector2(900.f * g_SCALE, 525.f * g_SCALE);
        m_Body->SetBoxSize(355.f, 170.f);

        m_Body->AddWorldPositionY(120.f);

        break;
    case CNightMareKingGrimm::EBossState::GroundDashing:
        m_Anim->SetCurrentAnimation("Grimm009 GroundDashing");
        Scale = Vector2(900.f * g_SCALE, 525.f * g_SCALE);
             
        m_Body->SetBoxSize(460.f, 190.f);

        m_Body->AddWorldPositionX(-30.f);
        m_Body->AddWorldPositionY(140.f);

        break;
    case CNightMareKingGrimm::EBossState::FireBat:
        m_Anim->SetCurrentAnimation("Grimm011 FireBat");
        Scale = Vector2(588.f * g_SCALE, 501.f * g_SCALE);

        m_Body->SetBoxSize(290.f, 300.f);

        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionX(-30.f);
        m_Body->AddWorldPositionY(pivot);

        break;
    case CNightMareKingGrimm::EBossState::FireBatEnd:
        m_Anim->SetCurrentAnimation("Grimm012 FireBatEnd");
        Scale = Vector2(588.f * g_SCALE, 501.f * g_SCALE);

        m_Body->SetBoxSize(290.f, 300.f);

        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionX(-30.f);
        m_Body->AddWorldPositionY(pivot);

        break;
    case CNightMareKingGrimm::EBossState::SlashStart:
        m_Anim->SetCurrentAnimation("Grimm013 SlashStart");
        Scale = Vector2(342.f * g_SCALE, 438.f * g_SCALE);

        m_Body->SetBoxSize(Scale.x -40.f, Scale.y);

        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionY(pivot);

        break;
    case CNightMareKingGrimm::EBossState::Slash:
        m_Anim->SetCurrentAnimation("Grimm014 Slash");
        CResourceManager::GetInst()->SoundPlay("BossFallDash");

        Scale = Vector2(792.f * g_SCALE, 438.f * g_SCALE);

        m_Body->SetBoxSize(Scale.x- 130.f, Scale.y - 50.f);

        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionY(pivot);
        m_Main->AddWorldPositionY(-20.f);

        break;
    case CNightMareKingGrimm::EBossState::Uppercut:
        m_Anim->SetCurrentAnimation("Grimm015 Uppercut");
        CResourceManager::GetInst()->SoundPlay("BossSlash");
        Scale = Vector2(662.f * g_SCALE, 786.f * g_SCALE);

        m_Body->SetBoxSize(220.f, 445.f);

        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionX(-20.f);
        m_Body->AddWorldPositionY(pivot+50.f);

        break;
    case CNightMareKingGrimm::EBossState::UppercutEnd:
        m_Anim->SetCurrentAnimation("Grimm016 UppercutEnd");
        CResourceManager::GetInst()->SoundPlay("BossUpperBoom");
        Scale = Vector2(662.f * g_SCALE, 786.f * g_SCALE);

        m_Body->SetBoxSize(180.f, 340.f);

        pivot = Scale.y * 0.5f;
        //m_Body->AddWorldPositionX(-20.f);
        m_Body->AddWorldPositionY(pivot);

        break;
    case CNightMareKingGrimm::EBossState::BallonAnticOn:
        m_Anim->SetCurrentAnimation("Grimm017 BallonAnticOn");
        Scale = Vector2(521.f * g_SCALE, 576.f * g_SCALE);

        m_Body->SetBoxSize(10.f, 10.f);
        m_Body->SetEnable(false);

        break;
    case CNightMareKingGrimm::EBossState::BallonOn:
        m_Anim->SetCurrentAnimation("Grimm018 BalloonOn");
        Scale = Vector2(521.f * g_SCALE, 576.f * g_SCALE);
        break;
    case CNightMareKingGrimm::EBossState::BallonEndOn:
        m_Anim->SetCurrentAnimation("Grimm019 BalloonEndOn");
        Scale = Vector2(521.f * g_SCALE, 576.f * g_SCALE);
        break;

    case CNightMareKingGrimm::EBossState::SpikeStart:
        m_Anim->SetCurrentAnimation("Grimm001 FirePillar");
        m_Sprite->SetEnable(false);
       // Scale = Vector2(521.f * g_SCALE, 576.f * g_SCALE);
        break;

    case CNightMareKingGrimm::EBossState::Death:
        m_Anim->SetCurrentAnimation("Grimm020 Death");
        Scale =Vector2(403.f * g_SCALE, 433.f * g_SCALE);
        
        m_Body->SetBoxSize(10.f, 10.f);
        m_Body->SetEnable(false);

        break;
    default:
        break;
    }

    m_Sprite->SetWorldScale(Scale);

    //SetHitBox();
    m_PrevState = State;
}

void CNightMareKingGrimm::Start()
{
    CGameObject::Start();

    SetSounds();
    SetAnimation();
    SpriteAnimationSetting();

    //스킬 쿨 세팅======================

    //================================
    
    //m_CurState = EBossState::TeleIn;
    //SetCurAnim(EBossState::Idle);
    //m_Anim->SetCurrentAnimation("Grimm001 FirePillar");
    
    SetNextPattern();

    srand((unsigned int)time(0));
}

bool CNightMareKingGrimm::Init()
{
    CGameObject::Init();
    m_Main = CreateComponent<CSceneComponent>("GrimmMain");
    m_Body = CreateComponent<CColliderBox2D>("GrimmBody");
    m_Sprite = CreateComponent<CSpriteComponent>("GrimmSprite");
    //m_DashDownSprite = CreateComponent<CSpriteComponent>("DashDownSprite");
   // m_DashGroundSprite = CreateComponent<CSpriteComponent>("DashGroundSprite");
    m_GravityAgent = CreateComponent<CGravityAgent>("GravityAgent");

    SetRootComponent(m_Main);
    m_Main->AddChild(m_Sprite);
    //m_Main->AddChild(m_DashDownSprite);
    //m_Main->AddChild(m_DashGroundSprite);
    m_Main->AddChild(m_Body);

    m_Body->SetWorldPosition(100.f, 100.f);
    
    m_GravityAgent->SetPhysicsSimulate(false);
    m_GravityAgent->SetSideWallCheck(true);

    m_Sprite->SetAnimationFile("NightMareKingGrimm");
    m_Anim = m_Sprite->GetAnimation();

    m_Body->SetCollisionProfile("NPC");
    
    //m_Body->SetEnable(false);

    m_CurState = EBossState::TeleIn;
    

    m_Sprite->SetPivot(0.5f, 0.f);
    return true;
}

void CNightMareKingGrimm::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    if (m_NextSkillDelay)
    {
        m_SkillUseTime += DeltaTime;
        if (m_SkillUseTime >= 0.7f)
        {
            m_NextSkillDelay = false;
            SetNextPattern();
        }
            
    }
    else
    {
        switch (m_CurState)
        {
        case CNightMareKingGrimm::EBossState::Idle:
            m_SkillUseTime += DeltaTime;
            if (m_FirePillarStart)
            {
                if (m_SkillUseTime >= 0.5f && m_FirePillarCount == 0)
                {
                    CreateFirePillar();
                    m_FirePillarCount = 1;
                }
                else if (m_SkillUseTime >= 1.3f && m_FirePillarCount == 1)
                {
                    CreateFirePillar();
                    m_FirePillarCount = 2;
                }
                else if (m_SkillUseTime >= 2.1f && m_FirePillarCount == 2)
                {
                    CreateFirePillar();
                    m_FirePillarCount = 3;
                }
                else if (m_SkillUseTime >= 2.9f && m_FirePillarCount == 3)
                {
                    CreateFirePillar();
                    m_FirePillarCount = 4;
                }
                else if (m_SkillUseTime >= 5.f)
                {
                    m_FirePillarCount = 0;
                    m_SkillUseTime = 0.f;
                    m_CurState = EBossState::TeleOut;
                    m_FirePillarStart = false;
                }          
            }
            break;
        case CNightMareKingGrimm::EBossState::TeleIn:
            break;
        case CNightMareKingGrimm::EBossState::TeleOut:
            break;
        case CNightMareKingGrimm::EBossState::AirDashDown:
            break;
        case CNightMareKingGrimm::EBossState::AirDashStart:
            break;
        case CNightMareKingGrimm::EBossState::AirDashFall:
            AddWorldPosition(m_Dir * 1000.f * DeltaTime, -1500.f * DeltaTime);
            Box2DInfo Box = m_GravityAgent->GetWallInfo();
            m_SkillUseTime += DeltaTime;

            if(m_SkillUseTime >= 0.1f)
                CreateAfterFlame(m_Body->GetWorldPos().x +200.f *m_Dir*(-1.f), m_Body->GetWorldPos().y + 250.f);

            if (GetWorldPos().y < Box.Bottom)
            {
                float PlayerX = m_Scene->FindObject("Player2D")->GetWorldPos().x;
                float thisX = GetWorldPos().x;
                if (thisX > PlayerX)
                    SetDir("Left");
                else if (thisX <= PlayerX)
                    SetDir("Right");
              
                SetWorldPositionY(-20.f);
                m_Sprite->SetWorldRotationZ(0.f);
                m_CurState = EBossState::AirDashDown;
            }                         
            break;
        case CNightMareKingGrimm::EBossState::GroundDashStart:
            m_CurState = EBossState::GroundDashing;
            break;
        case CNightMareKingGrimm::EBossState::GroundDashing:
            m_SkillUseTime += DeltaTime;

            if (m_SkillUseTime >= 0.05f)
                CreateAfterFlame(m_Body->GetWorldPos().x, m_Body->GetWorldPos().y);

            AddWorldPositionX(m_Dir * 3000.f * DeltaTime);
            if (m_SkillUseTime >= 0.2f)
            {
                m_NextState = EBossState::TeleOut;
                m_CurState = EBossState::AirDashDown;
            }
                
            break;
        case CNightMareKingGrimm::EBossState::FireBat:
            m_SkillUseTime += DeltaTime;

            if (m_SkillUseTime >= 0.3f && m_FireBatCount == 0)
            {
                CResourceManager::GetInst()->SoundPlay("BossFireBat");
                OutputDebugStringA("1");
                CreateFireBat(m_FireBatCount, m_Dir);
                m_FireBatCount = 1;
            }

            else if (m_SkillUseTime >= 0.6f && m_FireBatCount == 1)
            {
                CResourceManager::GetInst()->SoundPlay("BossFireBat");
                OutputDebugStringA("2");
                CreateFireBat(m_FireBatCount, m_Dir);
                m_FireBatCount = 2;
            }
            
            else if (m_SkillUseTime >= 0.9f && m_FireBatCount == 2)
            {
                CResourceManager::GetInst()->SoundPlay("BossFireBat");
                OutputDebugStringA("3");
                CreateFireBat(m_FireBatCount, m_Dir);
                m_FireBatCount = 3;
            }

            else if (m_SkillUseTime >= 1.2f && m_FireBatCount == 3)
            {
                CResourceManager::GetInst()->SoundPlay("BossFireBat");
                OutputDebugStringA("4");
                CreateFireBat(m_FireBatCount, m_Dir);
                m_FireBatCount = 4;
            }

            if (m_SkillUseTime >= 2.f)
            {
                m_FireBatCount = 0;
                m_SkillUseTime = 0.f;
                m_CurState = EBossState::FireBatEnd;                
            }
            break;
        case CNightMareKingGrimm::EBossState::FireBatEnd:
            break;
        case CNightMareKingGrimm::EBossState::SlashStart:
            break;
        case CNightMareKingGrimm::EBossState::Slash:
            m_SkillUseTime += DeltaTime;
            AddWorldPositionX(m_Dir * 1500.f * DeltaTime);
            if (m_SkillUseTime >= 0.3f)
                m_CurState = EBossState::AirDashDown;           
            break;
        case CNightMareKingGrimm::EBossState::Uppercut:
            AddWorldPosition(m_Dir * 800.f * DeltaTime, 2000.f * DeltaTime);
            
            m_SkillUseTime += DeltaTime;
            if (m_SkillUseTime >= 0.2f)
                m_CurState = EBossState::UppercutEnd;
            break;
        case CNightMareKingGrimm::EBossState::UppercutEnd:
                m_Sprite->SetEnable(false);
                CreateFlame();
                m_CurState = EBossState::TeleOut;
            break;
        case CNightMareKingGrimm::EBossState::BallonAnticOn:
            break;
        case CNightMareKingGrimm::EBossState::BallonOn:
            break;
        case CNightMareKingGrimm::EBossState::BallonEndOn:
            break;
        case CNightMareKingGrimm::EBossState::SpikeStart:
            m_SkillUseTime += DeltaTime;
            if (m_SkillUseTime >= 3.f)
            {
                m_SpikeStart = false;
                m_Sprite->SetEnable(true);
                m_Body->SetEnable(true);
                SetNextPattern();
                
                while (m_NextState == EBossState::SpikeStart)              
                    SetNextPattern();
                
                m_CurState = EBossState::TeleIn;
              
            }
            break;
        case CNightMareKingGrimm::EBossState::Death:
            break;
        default:
            break;
        }
    }
    SetCurAnim(m_CurState);
}

void CNightMareKingGrimm::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

CNightMareKingGrimm* CNightMareKingGrimm::Clone() const
{
    return new CNightMareKingGrimm(*this);
}

void CNightMareKingGrimm::CheckDir()
{
    bool Check = m_Sprite->GetTextureReverse();
    m_Dir = Check ? 1.f : -1.f;
    m_strDir = Check ? "Left" : "Right";
}

void CNightMareKingGrimm::ChangeDir()
{
    if (m_strDir == "Left")
    {
        m_strDir = "Right";
        m_Dir = 1.f;
    }
    else if (m_strDir == "Right")
    {
        m_strDir = "Left";
        m_Dir = -1.f;
    }
}

void CNightMareKingGrimm::SetDir(std::string LeftRight)
{
    if (LeftRight == "Left")
    {
        m_strDir = "Left";
        m_Dir = -1.f;
        m_Sprite->SetTextureReverse(false);
        m_Body->SetWorldRotationZ(0.f);
    }
    else if (LeftRight == "Right")
    {
        m_strDir = "Right";
        m_Dir = 1.f;
        m_Sprite->SetTextureReverse(true);
        m_Body->SetRelativeRotationZ(90.f);
    }
    else
        return;
}

void CNightMareKingGrimm::AutoSetTextureReverse()
{
}

void CNightMareKingGrimm::SetNextPattern()
{
    int num = rand() % 5;
    //int num = 4;

    CPlayer2D* Player = (CPlayer2D*)(m_Scene->FindObject("Player2D"));
    bool WallCheck = Player->WallCheck();
    int PosCheck = Player->CheckPos(); //pos가 1: 가운데보다 오른쪽
                                       //else 왼쪽
    Vector3 PlayerPos = Player->GetWorldPos();

    switch (num)
    {
    case 0: //대시 어퍼컷
        OutputDebugStringA("대시 어퍼컷");
        m_NextState = EBossState::SlashStart;

        if (PosCheck == 1)
        {
            SetDir("Right");
            SetWorldPosition(PlayerPos.x - (400.f * m_Dir), 0.f);
        }
        else
        {
            SetDir("Left");
            SetWorldPosition(PlayerPos.x - (400.f * m_Dir), 0.f);
        }

        break;

    case 1: // 파이어뱃
        OutputDebugStringA("파이어뱃");
        m_NextState = EBossState::FireBat;

        if (PosCheck == 1) //
        {
            SetWorldPosition(0.f, 0.f);
            SetDir("Right");
        }
        else
        {
            SetWorldPosition(1260.f, 0.f);
            SetDir("Left");
        }

        break;
    case 2: //내려찍기 대시
        OutputDebugStringA("내려찍기 대시");
        m_NextState = EBossState::AirDashStart;

        if (PosCheck == 1)
        {
            SetDir("Right");
            SetWorldPosition(PlayerPos.x - (400.f * m_Dir), 300.f);
        }
        else
        {
            SetDir("Left");
            SetWorldPosition(PlayerPos.x - (400.f * m_Dir), 300.f);
        }

        break;
    case 3: //불기둥
        OutputDebugStringA("불기둥");
        m_NextState = EBossState::Idle;
        m_FirePillarStart = true;
        if (PosCheck == 1) //
        {
            SetWorldPosition(0.f, 250.f);
            SetDir("Left");
        }
        else
        {
            SetWorldPosition(1260.f, 250.f);
            SetDir("Right");
        }
        break;
    case 4: // 가시
        OutputDebugStringA("가시");     
        m_NextState = EBossState::SpikeStart;
        SetWorldPosition(1260.f, 250.f);
        m_Sprite->SetEnable(false);
        m_Body->SetEnable(false);
        m_SpikeStart = true;
        NextPatternStart();
        break;
    case 5: //풍선
        break;
    default:
        break;
    }

    if (!m_SpikeStart)
    {
        m_Sprite->SetEnable(true);
        m_CurState = EBossState::TeleIn;
    }
}

void CNightMareKingGrimm::NextPatternStart()
{
    m_CurState = m_NextState;
    m_SkillUseTime = 0.f;

    if(!m_SpikeStart)
        CResourceManager::GetInst()->SoundPlay("BossAttack");
}

void CNightMareKingGrimm::TeleportIn()
{
    //m_CurState = EBossState::TeleIn;
    m_Sprite->SetEnable(true);
    m_Body->SetEnable(true);
    NextPatternStart();
}

void CNightMareKingGrimm::TeleportOut()
{
    //텔레포트 끝나면 발동
    m_SkillUseTime = 0.f;
    m_CurState = EBossState::Idle;
    m_Sprite->SetEnable(false);
    m_Body->SetEnable(false);
    m_NextSkillDelay = true;    
}

void CNightMareKingGrimm::FireBatEnd()
{
    CResourceManager::GetInst()->SoundPlay("BossCapeOpen");
    m_CurState = EBossState::TeleOut;
}

void CNightMareKingGrimm::Slash()
{
    m_CurState = EBossState::Slash;
}

void CNightMareKingGrimm::AirDashStart()
{    
    switch (m_NextState)
    {
    case EBossState::SlashStart:
        m_CurState = EBossState::Uppercut;
        break;
    case EBossState::AirDashStart:
        m_CurState = EBossState::GroundDashStart;
        break;
    case EBossState::TeleOut:
        AddWorldPositionY(30.f);
        m_CurState = EBossState::TeleOut;
        break;
    }
    m_SkillUseTime = 0.f;
}

void CNightMareKingGrimm::FallStart()
{
    m_SkillUseTime = 0.f;
    AddWorldPositionX(m_Dir* 200.f);

    if (m_Dir == 1.f)
        m_Sprite->SetWorldRotationZ(45.f);
    else if (m_Dir == -1.f)
        m_Sprite->SetWorldRotationZ(-45.f);

    m_CurState = EBossState::AirDashFall;
}

void CNightMareKingGrimm::CreateFireBat(int count, float Dir)
{
    CFireBatBullet* Bullet = m_Scene->CreateObject<CFireBatBullet>("FireBat");
    Bullet->SetDirection(m_Dir);
    Bullet->SetWorldPosition(GetWorldPos());
    if (count % 2 == 0)      
        Bullet->SetWorldPositionY(320.f);
    else
        Bullet->SetWorldPositionY(70.f);

    if (Dir < 0)
        Bullet->SetTextureReverse(true);
}

void CNightMareKingGrimm::CreateFlame()
{
    std::vector<CFlameParticle*> v;
    float x = GetWorldPos().x;
    
    for (int i = 0; i < 5; i++)
    {
        std::string name = "FallFlame";
        name += std::to_string(i + 1);
        CFlameParticle* Flame = m_Scene->CreateObject<CFlameParticle>(name);
        Flame->EnableCollider(true);
        Flame->SetWorldPosition(x, 720.f);
        //Flame->SetWorldRotationZ(9.f);
        Flame->SetWorldRotationZ(210.f + (i * 30.f));        
        Flame->SetLifeTime(1.f);

        v.push_back(Flame);
    }
    //v[0]->SetWorldRotationZ(225.f);
    //v[0]->SetSpeed(0.7f);
    v[1]->SetSpeed(0.6f);
    v[2]->SetSpeed(0.5f);
    v[3]->SetSpeed(0.6f);
    //v[4]->SetWorldRotationZ(315.f);
    //v[4]->SetSpeed(0.7f);
}

void CNightMareKingGrimm::CreateAfterFlame(float x, float y)
{
    CFlameParticle* Flame = m_Scene->CreateObject<CFlameParticle>("AfterFlame");
    Flame->SetOpacity(0.7f);
    Flame->SetWorldPosition(x, y);
    Flame->EnableMineFlame();
    Flame->SetLifeTime(0.3f);
    Flame->EnableCollider(true);
    
}

void CNightMareKingGrimm::CreateFirePillar()
{
    float x = m_Scene->FindObject("Player2D")->GetWorldPos().x;

    CFirePillarBullet* FirePillar = m_Scene->CreateObject<CFirePillarBullet>("FirePillar");

    FirePillar->SetWorldPositionX(x);

}




