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
#include "GrimmSpike.h"
#include "FlameBall.h"
#include "Effect.h"
#include "GrimmSmoke.h"

#include <time.h>
#include "Player2D.h"
#include "PlayerAttack.h"
//#include "Resource/Material/Material.h"
#define MAX_HP 50;

CNightMareKingGrimm::CNightMareKingGrimm()  :
    m_CurState(EBossState::Idle),
    m_PrevState(EBossState::Idle),
    m_NextState(EBossState::Idle),
    m_Dir(1.f),
    m_strDir("Right"),
    m_Time(0.f),
    m_MaterialChangeTime(0.f),
    m_SkillUseTime(0.f),
    m_NextSkillDelay(false),
    m_FireBatCount(0),
    m_FireBatDelay(0.f),
    m_FirePillarStart(false),
    m_FirePillarCount(0),
    m_SpikeStart(false),
    m_Spiking(false),
    m_SpikeEnd(false)
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

    m_GravityAgent = (CGravityAgent*)FindComponent("GravityAgent");

    m_Anim = CResourceManager::GetInst()->FindAnimation2D("NightMareKingGrimm");
}

CNightMareKingGrimm::~CNightMareKingGrimm()
{
    m_Anim->ClearAllNotify();
    CResourceManager::GetInst()->SoundStop("BossFireBall");
}

void CNightMareKingGrimm::SetSounds()
{
    CResourceManager::GetInst()->LoadSound("Effect", "BossAttack", false, "Boss/Grimm_attack_01.wav");
    //CResourceManager::GetInst()->LoadSound("Effect", "BossBalloon", true, "Boss/grimm_balloon_shooting_fireballs_loop.wav");
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

    CResourceManager::GetInst()->LoadSound("Effect", "SpikeStart", false, "Boss/grimm_spikes_pt_1_grounded.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "Spiking", false, "Boss/grimm_spikes_pt_2_shoot_up.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "SpikeEnd", false, "Boss/grimm_spikes_pt_3_shrivel_back.wav");

    CResourceManager::GetInst()->LoadSound("Effect", "BossScream", false, "Boss/grimm_scream.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "BossFireBall", true, "Boss/grimm_balloon_shooting_fireballs_loop.wav");

    CResourceManager::GetInst()->LoadSound("Effect", "BossGushing", false, "Boss/boss_gushing.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "BossDeath", false, "Boss/boss_explode.wav");  
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

    m_Anim->SetPlayScale("Grimm017 BallonAnticOn", 3.f);
    m_Anim->SetCurrentEndFunction("Grimm017 BallonAnticOn", this, &CNightMareKingGrimm::BalloonAnticEnd);

    m_Anim->SetPlayScale("Grimm018 BalloonOn", 2.f);

    m_Anim->SetPlayScale("Grimm019 BalloonEndOn", 3.f);
    m_Anim->SetCurrentEndFunction("Grimm019 BalloonEndOn", this, &CNightMareKingGrimm::FireBatEnd);

    m_Anim->SetPlayScale("Grimm020 Death", 3.f);
}

void CNightMareKingGrimm::SetCurAnim(EBossState State)
{
    //사운드, 모션 삽입용

    //애니메이션 세팅할때 이전 상태랑 같은거면 리턴
    if (m_PrevState == State)
        return;

    Vector3 Pos = m_Sprite->GetWorldPos();
    Vector2 Scale = Vector2(0.f, 0.f);
    float pivot = 0.f;

    m_Body->SetWorldPosition(Pos);

    switch (State)
    {
    case CNightMareKingGrimm::EBossState::Idle:
        m_Anim->SetCurrentAnimation("Grimm001 FirePillar");

        Scale = Vector2(262.f, 379.f);
        m_Body->SetBoxSize(200.f, 320.f);
        
        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionY(pivot);

        break;
    case CNightMareKingGrimm::EBossState::TeleIn:
        m_Anim->SetCurrentAnimation("Grimm002 TeleIn");
        CResourceManager::GetInst()->SoundPlay("BossTeleIn");
        CResourceManager::GetInst()->SoundPlay("BossCapeOpen");
        CreateSmokeEffect();
        CreateTeleportEffect();
        
        
        Scale = Vector2(221.f, 311.f);      
        m_Body->SetBoxSize(161.f, 311.f);

        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionY(pivot);
        m_Body->SetEnable(true);

        break;
    case CNightMareKingGrimm::EBossState::TeleOut:
        CResourceManager::GetInst()->SoundPlay("BossCapeOpen");
        CResourceManager::GetInst()->SoundPlay("BossTeleOut");
        m_Anim->SetCurrentAnimation("Grimm003 TeleOut");
        CreateSmokeEffect();
        CreateTeleportEffect();
       
        Scale = Vector2(221.f,311.f);
        m_Body->SetBoxSize(161.f, 311.f);

        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionY(pivot);

        break;
    case CNightMareKingGrimm::EBossState::AirDashDown:
        m_Anim->SetCurrentAnimation("Grimm004 AirDashDown");

        Scale = Vector2(630.f, 368.f);
        m_Body->SetBoxSize(295.f, 170.f);

        m_Body->AddWorldPositionY(120.f);

        break;
    case CNightMareKingGrimm::EBossState::AirDashStart:
        m_Anim->SetCurrentAnimation("Grimm005 AirDashStart");

        Scale = Vector2(630.f, 368.f);
        m_Body->SetBoxSize(170.f, 290.f);

        pivot = m_Sprite->GetWorldScale().y * 0.5f;
        m_Body->AddWorldPositionY(pivot);

        break;
    case CNightMareKingGrimm::EBossState::AirDashFall:
        m_Anim->SetCurrentAnimation("Grimm006 AirDashFall");
        CResourceManager::GetInst()->SoundPlay("BossFallDash");
        
        Scale = Vector2(630.f, 368.f);
        m_Body->SetBoxSize(20.f, 20.f);

        m_Body->AddWorldPositionY(50.f);
        //m_Main->AddWorldRotationZ(130.f);

        break;
    case CNightMareKingGrimm::EBossState::GroundDashStart:
        m_Anim->SetCurrentAnimation("Grimm008 GroundDashStart");
        CResourceManager::GetInst()->SoundPlay("BossGroundDash");

        Scale = Vector2(630.f, 368.f);
        m_Body->SetBoxSize(355.f, 170.f);

        m_Body->AddWorldPositionY(120.f);

        break;
    case CNightMareKingGrimm::EBossState::GroundDashing:
        m_Anim->SetCurrentAnimation("Grimm009 GroundDashing");
        Scale = Vector2(630.f, 368.f);
             
        m_Body->SetBoxSize(460.f, 190.f);

        m_Body->AddWorldPositionX(-30.f);
        m_Body->AddWorldPositionY(140.f);

        break;
    case CNightMareKingGrimm::EBossState::FireBat:
        m_Anim->SetCurrentAnimation("Grimm011 FireBat");
        Scale = Vector2(412.f, 351.f);

        m_Body->SetBoxSize(290.f, 300.f);

        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionX(-30.f);
        m_Body->AddWorldPositionY(pivot);

        break;
    case CNightMareKingGrimm::EBossState::FireBatEnd:
        m_Anim->SetCurrentAnimation("Grimm012 FireBatEnd");
        Scale = Vector2(412.f, 351.f);

        m_Body->SetBoxSize(290.f, 300.f);

        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionX(-30.f);
        m_Body->AddWorldPositionY(pivot);

        break;
    case CNightMareKingGrimm::EBossState::SlashStart:
        m_Anim->SetCurrentAnimation("Grimm013 SlashStart");
        Scale = Vector2(240.f, 251.f);

        m_Body->SetBoxSize(200.f, 251.f);

        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionY(pivot);

        break;
    case CNightMareKingGrimm::EBossState::Slash:
        m_Anim->SetCurrentAnimation("Grimm014 Slash");
        CResourceManager::GetInst()->SoundPlay("BossFallDash");

        Scale = Vector2(555.f, 307.f);

        m_Body->SetBoxSize(425.f, 257.f);

        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionY(pivot);
        //m_Main->AddWorldPositionY(-20.f);

        break;
    case CNightMareKingGrimm::EBossState::Uppercut:
        m_Anim->SetCurrentAnimation("Grimm015 Uppercut");
        CResourceManager::GetInst()->SoundPlay("BossSlash");
        Scale = Vector2(464.f, 551.f);

        m_Body->SetBoxSize(220.f, 445.f);

        pivot = Scale.y * 0.5f;
        m_Body->AddWorldPositionX(-20.f);
        m_Body->AddWorldPositionY(pivot+50.f);

        break;
    case CNightMareKingGrimm::EBossState::UppercutEnd:
        m_Anim->SetCurrentAnimation("Grimm016 UppercutEnd");
        CResourceManager::GetInst()->SoundPlay("BossUpperBoom");
        Scale = Vector2(464.f, 551.f);

        m_Body->SetBoxSize(180.f, 340.f);

        pivot = Scale.y * 0.5f;
        //m_Body->AddWorldPositionX(-20.f);
        m_Body->AddWorldPositionY(pivot);

        break;
    case CNightMareKingGrimm::EBossState::BallonAnticOn:
        m_Anim->SetCurrentAnimation("Grimm017 BallonAnticOn");
        CResourceManager::GetInst()->SoundPlay("BossScream");
        Scale = Vector2(365.f, 404.f);

        m_Body->SetBoxSize(10.f, 10.f);
        m_Body->SetEnable(false);

        break;
    case CNightMareKingGrimm::EBossState::BallonOn:
        m_Anim->SetCurrentAnimation("Grimm018 BalloonOn");
        CResourceManager::GetInst()->SoundPlay("BossFireBall");
        Scale = Vector2(365.f, 404.f);
        break;
    case CNightMareKingGrimm::EBossState::BallonEndOn:
        m_Anim->SetCurrentAnimation("Grimm019 BalloonEndOn");
        CResourceManager::GetInst()->SoundStop("BossFireBall");
        Scale = Vector2(365.f, 404.f);
        break;

    case CNightMareKingGrimm::EBossState::SpikeStart:
        m_Anim->SetCurrentAnimation("Grimm001 FirePillar");
        m_Sprite->SetEnable(false);

        m_Body->SetBoxSize(10.f, 10.f);
        CreateSpike();
       // Scale = Vector2(521.f * g_SCALE, 576.f * g_SCALE);
        break;

    case CNightMareKingGrimm::EBossState::Death:
        m_Anim->SetCurrentAnimation("Grimm020 Death");
        CResourceManager::GetInst()->SoundPlay("BossGushing");
        CResourceManager::GetInst()->SoundStop("Grimm");    

        {
            CPlayer2D* Player = (CPlayer2D*)(m_Scene->FindObject("Player2D"));
            //int PosCheck = Player->CheckPos(); // pos가 1: 가운데보다 오른쪽
            //                                   // else -1 왼쪽
            float PlayerX = Player->GetWorldPos().x;
            float thisX = GetWorldPos().x;

            if (PlayerX >= thisX)
                SetDir("Right");
            else if (PlayerX < thisX)
                SetDir("Left");
        }
        CreateExplodeEffect();
        
        
        Scale =Vector2(283.f, 304.f);
        
        m_Body->SetBoxSize(10.f, 10.f);
        m_Body->SetEnable(false);

        break;
    default:
        break;
    }

    m_Sprite->SetWorldScale(Scale);

    m_PrevState = State;
}

void CNightMareKingGrimm::Start()
{
    CGameObject::Start();

    //m_Body->SetBoxSize(100.f, 100.f);
    SetWorldPosition(860.f, 300.f);

    SetSounds();
    SetAnimation();
    
    srand((unsigned int)time(0));

    m_Body->SetCollisionCallback(ECollision_Result::Collision, this, &CNightMareKingGrimm::CollisionBegin);
    
    SetNextPattern();
}

bool CNightMareKingGrimm::Init()
{
    CGameObject::Init();
    m_Main = CreateComponent<CSceneComponent>("GrimmMain");
    m_Body = CreateComponent<CColliderBox2D>("GrimmBody");
    m_Sprite = CreateComponent<CSpriteComponent>("GrimmSprite");
    m_GravityAgent = CreateComponent<CGravityAgent>("GravityAgent");

    SetRootComponent(m_Main);
    m_Main->AddChild(m_Sprite);

    m_Main->AddChild(m_Body);

    //SetRootComponent(m_Sprite);
    //m_Sprite->AddChild(m_Body);
  
    m_GravityAgent->SetPhysicsSimulate(false);
    m_GravityAgent->SetSideWallCheck(true);

    m_Sprite->SetAnimationFile("NightMareKingGrimm");
    m_Anim = m_Sprite->GetAnimation();

    m_Body->SetCollisionProfile("Monster");
    
    //m_Body->SetEnable(false);

    m_CurState = EBossState::TeleIn;
    
    m_Sprite->SetPivot(0.5f, 0.f);

    m_HP = MAX_HP;

    SetWorldPosition(860.f, 300.f);
    return true;
}

void CNightMareKingGrimm::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
    
    m_BalloonCool += DeltaTime;

    //히트 머테리얼
    if (m_MaterialChangeTime >= 1.f)
    {
        m_MaterialChangeTime += DeltaTime;

        if (m_MaterialChangeTime >= 1.1f)
        {
            m_Sprite->GetMaterial(0)->SetBaseColor(1.f, 1.f, 1.f, 1.f);
            m_Sprite->GetMaterial(0)->SetOpacity(1.f);
            m_MaterialChangeTime = 0.f;
        }
    }

    //텔레포트 딜레이
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
                int PlayerX = (int)m_Scene->FindObject("Player2D")->GetWorldPos().x;
                float thisX = GetWorldPos().x;
                if (thisX > (float)PlayerX)
                    SetDir("Left");
                else if (thisX <= (float)PlayerX)
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
            m_SkillUseTime += DeltaTime;
            if (m_SkillUseTime >= 0.75f)
            {
                CreateFlameBall();
                m_SkillUseTime = 0.f;
                ++m_FireBallCount;
            }
            if (m_FireBallCount == 12)
            {
                m_CurState = EBossState::BallonEndOn;
                m_BalloonCool = 0.f;
                m_SkillUseTime = 0.f;
                m_FireBallCount = 0;
            }
                          
            break;
        case CNightMareKingGrimm::EBossState::BallonEndOn:
            break;
        case CNightMareKingGrimm::EBossState::SpikeStart:
            m_SkillUseTime += DeltaTime;
            if (m_SkillUseTime > 0.9f && !m_Spiking)
            {
                CResourceManager::GetInst()->SoundPlay("Spiking");
                m_Spiking = true;
            }
            if (m_SkillUseTime > 0.9f && !m_SpikeEnd)
            {
                CResourceManager::GetInst()->SoundPlay("SpikeEnd");
                m_SpikeEnd = true;
            }

            if (m_SkillUseTime >= 2.f)
            {
                SetNextPattern();
                
                while (m_NextState == EBossState::SpikeStart)              
                    SetNextPattern();
             
                m_SpikeStart = false;
                m_Spiking = false;
                m_SpikeEnd = false;
                m_Body->SetEnable(true);
                m_Sprite->SetEnable(true);
                m_CurState = EBossState::TeleIn;
              
            }
            break;
        case CNightMareKingGrimm::EBossState::Death:
            m_Time += DeltaTime;

            if (m_Time >= 3.f)
            {
                m_Sprite->SetEnable(false);
                
                if (!m_Death)
                {
                    CResourceManager::GetInst()->SoundPlay("BossDeath");
                    CreateDeathEffect();
                }
                    
                
                m_Death = true;             
            }

            if (m_Death && m_Time >= 10.f)
                Destroy();
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

    Vector3 v = GetWorldPos();
    if (v.x > 10000.f)
    {
        int a = (int)v.x;
        v.x = (float)a;       
    }
    else if (v.x < -10000.f)
    {
        int a = (int)v.x;
        v.x = (float)a;
    }
}

CNightMareKingGrimm* CNightMareKingGrimm::Clone() const
{
    return new CNightMareKingGrimm(*this);
}

//void CNightMareKingGrimm::CheckDir()
//{
//    bool Check = m_Sprite->GetTextureReverse();
//    m_Dir = Check ? 1.f : -1.f;
//    m_strDir = Check ? "Left" : "Right";
//}

//void CNightMareKingGrimm::ChangeDir()
//{
//    if (m_strDir == "Left")
//    {
//        m_strDir = "Right";
//        m_Dir = 1.f;
//    }
//    else if (m_strDir == "Right")
//    {
//        m_strDir = "Left";
//        m_Dir = -1.f;
//    }
//}

void CNightMareKingGrimm::SetDir(std::string LeftRight)
{
    if (LeftRight == "Left")
    {
        m_strDir = "Left";
        m_Dir = -1.f;
        m_Sprite->SetTextureReverse(false);
    }
    else if (LeftRight == "Right")
    {
        m_strDir = "Right";
        m_Dir = 1.f;
        m_Sprite->SetTextureReverse(true);
    }
    else
        return;
}

void CNightMareKingGrimm::SetNextPattern()
{
    int num = rand() % 6;
    //int num = 5;

    CPlayer2D* Player = (CPlayer2D*)(m_Scene->FindObject("Player2D"));
    int PosCheck = Player->CheckPos(); // pos가 1: 가운데보다 오른쪽
                                       // else 왼쪽
    Vector3 PlayerPos = Player->GetWorldPos();

    if (num == 5)
        if (m_BalloonCool <= 30.f)
            while (num == 5)            
                num = rand() % 6;               
            
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
        else if (PosCheck == -1)
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
            SetDir("Right");
            SetWorldPosition(300.f, 0.f);            
        }
        else if(PosCheck == -1)
        {
            SetDir("Left");
            SetWorldPosition(960.f, 0.f);            
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
        else if(PosCheck == -1)
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
            SetWorldPosition(300.f, 250.f);
            SetDir("Left");
        }
        else if (PosCheck == -1)
        {
            SetWorldPosition(960.f, 250.f);
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
        OutputDebugStringA("풍선");
        m_NextState = EBossState::BallonAnticOn;
        SetWorldPosition(650.f, 150.f);
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

    Vector3 v = GetWorldPos();
    if (v.x > 10000.f)
    {
        int a = (int)v.x;
        v.x = (float)a;
    }
    else if (v.x < -10000.f)
    {
        int a = (int)v.x;
        v.x = (float)a;
    }

    if(!m_SpikeStart)
        CResourceManager::GetInst()->SoundPlay("BossAttack");
}

void CNightMareKingGrimm::TeleportIn()
{
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
    SetWorldPosition(860.f, 300.f);
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
    m_CurState = EBossState::AirDashFall;
    
    m_SkillUseTime = 0.f;
    AddWorldPositionX(m_Dir* 200.f);

    if (m_Dir == 1.f)
        m_Sprite->SetWorldRotationZ(40.f);
    else if (m_Dir == -1.f)
        m_Sprite->SetWorldRotationZ(-40.f);    
}

void CNightMareKingGrimm::BalloonAnticEnd()
{
    m_SkillUseTime = 0.f;
    m_CurState = EBossState::BallonOn;
    CreateExplodeEffect(534.f, 492.f, 9.f);
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
        Flame->SetSpeed(1.5f);

        v.push_back(Flame);
    }
    v[1]->SetSpeed(0.9f);
    v[2]->SetSpeed(0.75f);
    v[3]->SetSpeed(0.9f);

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

    FirePillar->SetWorldPositionX((float)x);

}

void CNightMareKingGrimm::CreateSpike()
{
    CResourceManager::GetInst()->SoundPlay("SpikeStart");
    int num = rand() % 2;
    int count = 15;

    if (num == 1)
    {
        num = 50;
        count = 14;
    }
        

    for (int i = 0; i < count; i++)
    {
        std::string name = "Spike";
        name += std::to_string(i + 1);
        CGrimmSpike* Spike = m_Scene->CreateObject<CGrimmSpike>(name);
        Spike->SetWorldPositionX(-250.f + num + (i * 140.f));
    }
}

void CNightMareKingGrimm::CreateFlameBall()
{
    /*
    1 : 50 Down
    2: 130 Down

    3: 210.f Down
    4: 290 Down

    5: 470 Up
    6: 550 Up
    */ 

    std::vector<CFlameBall*> vec;

    for (int i = 0; i < 9; i++)
    {
        std::string name = "FlameBall";
        name += std::to_string(i + 1);
        CFlameBall* Ball = m_Scene->CreateObject<CFlameBall>(name);
        Ball->SetWorldPosition(GetWorldPos().x, 300.f);
        Ball->SetBallDir(EFireBallDirection::Down);
        vec.push_back(Ball);        
    }
    

    //왼쪽 방향, m_Dir -1이면 true
    //우측
    vec[0]->SetBallDir(EFireBallDirection::OnlyDown);

    vec[1]->SetDirection(m_Dir);
    vec[1]->SetHeight(50.f);

    vec[2]->SetDirection(m_Dir);
    vec[2]->SetHeight(210.f);

    vec[3]->SetDirection(m_Dir);
    vec[3]->SetHeight(470.f);
    vec[3]->SetBallDir(EFireBallDirection::Up);
    
    //좌측
    vec[4]->SetDirection(-m_Dir);   
    vec[4]->SetHeight(50.f);
    vec[4]->SetTextureReverse(true);

    vec[5]->SetDirection(-m_Dir);
    vec[5]->SetHeight(210.f);
    vec[5]->SetTextureReverse(true);

    vec[6]->SetDirection(-m_Dir);
    vec[6]->SetHeight(470.f);
    vec[6]->SetBallDir(EFireBallDirection::Up);    
    vec[6]->SetTextureReverse(true);

    vec[7]->SetBallDir(EFireBallDirection::OnlyDown);
    vec[7]->AddWorldPosition(-50.f, 20.f+(float)(rand()%50));
    vec[8]->SetBallDir(EFireBallDirection::OnlyDown);
    vec[8]->AddWorldPosition(50.f, 20.f+(float)(rand()%50));

    for (int i = 1; i < 7; i++)
    {
        int random = rand() % 2;
        vec[i]->SetHeight(vec[i]->GetHeight() + (random * 90));
    }    
}

void CNightMareKingGrimm::CreateSmokeEffect()
{
    CGrimmSmoke* smoke = m_Scene->CreateObject<CGrimmSmoke>("Smoke");
    smoke->SetWorldPosition(m_Sprite->GetWorldPos());
    smoke->AddWorldPositionY(170.f);
}

void CNightMareKingGrimm::CreateTeleportEffect()
{
    std::string s = "BossTeleportEffect";
    
    CEffect* Effect = m_Scene->CreateObject<CEffect>("TeleportEffect");
    Effect->SetLifeTime(0.3f);
    Effect->SetWorldPosition(m_Body->GetWorldPos());
    Effect->AddWorldPositionY(200.f);
    Effect->SetWorldScale(283.f, 866.f);

    Effect->SetCurAnimation(s, 5.f);
}

void CNightMareKingGrimm::CreateExplodeEffect(float sizex, float sizey, float time)
{
    std::string s = "BossExplodeEffect";

    CEffect* Effect = m_Scene->CreateObject<CEffect>("ExplodeEffect");
    Effect->SetLifeTime(time);
    Effect->SetWorldPosition(m_Body->GetWorldPos());
    Effect->AddWorldPositionY(180.f);
    Effect->SetWorldScale(sizex, sizey);

    Effect->SetCurAnimation(s, 5.f);

    CMaterial* Mat = Effect->GetMaterials();
    Mat->SetBaseColorUnsignedChar(255, 100, 100, 255);
}

void CNightMareKingGrimm::CreateDeathEffect()
{
    std::string s = "BossDeathEffect";

    CEffect* Effect = m_Scene->CreateObject<CEffect>("DeathEffect");
    Effect->SetLifeTime(0.5f);
    Effect->SetWorldPosition(m_Body->GetWorldPos());
    Effect->AddWorldPositionY(180.f);
    Effect->SetWorldScale(786.f, 718.f);

    Effect->SetCurAnimation(s, 5.f);

    CMaterial* Mat = Effect->GetMaterials();
    Mat->SetBaseColorUnsignedChar(255, 100, 100, 255);
}

void CNightMareKingGrimm::CollisionBegin(const CollisionResult& Result)
{
    OutputDebugStringA("보스 피격");

    std::string dest = Result.Dest->GetName();

    //공격 당하는 충돌일 시
    if (dest == "PlayerAttack" || dest == "PlayerBullet")
    {
        int Damage = 0;
        if (dest == "PlayerAttack")
        {
            CPlayerAttack* Attack = (CPlayerAttack*)(Result.Dest->GetOwner());
            Damage = Attack->GetDamage();
        }
        else if (dest == "PlayerBullet")
            Damage = 3;

        OutputDebugStringA("보스 맞음!");

        //색 변화 머테리얼
        m_Sprite->GetMaterial(0)->SetOpacity(0.7f);
        m_Sprite->GetMaterial(0)->SetBaseColor(255, 255, 255, 255);
        m_MaterialChangeTime = 1.f;

        //hp 감소
        m_HP -= Damage;
        if (m_HP <= 0) //사망
        {
            m_CurState = EBossState::Death;
            m_Body->SetEnable(false);                    
        }
    }
}




