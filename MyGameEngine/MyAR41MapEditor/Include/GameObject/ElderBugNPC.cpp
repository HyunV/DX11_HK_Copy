#include "ElderBugNPC.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Animation/Animation2D.h"
#include "Resource/ResourceManager.h" 
#include "Input.h"
#include "Scene/Scene.h"
#include "../UI/MessageBoxUI.h"
#include "Player2D.h"
#include <time.h>

CElderBugNPC::CElderBugNPC()
{
    SetTypeID<CElderBugNPC>();
    m_ObjectTypeName = "ElderBugNPC";
}

CElderBugNPC::CElderBugNPC(const CElderBugNPC& Obj) :
    CGameObject(Obj)
{
    m_Body = (CColliderBox2D*)FindComponent("Body");
    m_Sprite = (CSpriteComponent*)FindComponent("Sprite");
    m_HearBox = (CSpriteComponent*)FindComponent("HearBox");
}

CElderBugNPC::~CElderBugNPC()
{
    CInput::GetInst()->DeleteBindFunction("Up", Input_Type::Down, this);
}


void CElderBugNPC::Start()
{
    CGameObject::Start();

    m_Body->SetCollisionCallback(ECollision_Result::Collision, this,
        &CElderBugNPC::CollisionBegin);

    m_Body->SetCollisionCallback(ECollision_Result::Release, this,
        &CElderBugNPC::CollisionEnd);

    CInput::GetInst()->AddBindFunction<CElderBugNPC>("Up", Input_Type::Down, this,
        &CElderBugNPC::NPCUpKey, m_Scene);

    CAnimation2D* Anim = m_Sprite->GetAnimation();
    Anim->SetCurrentAnimation("ElderbugIdle");

    CResourceManager::GetInst()->LoadSound("Effect", "0ElderBugTalk", false, "NPC/Elderbug_01.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "1ElderBugTalk", false, "NPC/Elderbug_02.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "2ElderBugTalk", false, "NPC/Elderbug_03.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "3ElderBugTalk", false, "NPC/Elderbug_04.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "4ElderBugTalk", false, "NPC/Elderbug_05.wav");
}

bool CElderBugNPC::Init()
{
    CGameObject::Init();

    m_Body = CreateComponent<CColliderBox2D>("Body");
    m_Sprite = CreateComponent<CSpriteComponent>("Sprite");
    m_HearBox = CreateComponent<CSpriteComponent>("HearBox");

    SetRootComponent(m_Body);
    m_Body->AddChild(m_Sprite);
    m_Body->AddChild(m_HearBox);

    m_Body->SetWorldPosition(600.f, 75.f);
    m_Body->SetBoxSize(100.f, 120.f);

    m_Body->SetCollisionProfile("NPC");
    m_Sprite->SetAnimationFile("NPCS");

    //커스텀
    float X = 124.f;
    float Y = 172.f;
    m_Sprite->SetWorldScale(X, Y);
    m_Sprite->SetPivot(0.5f, 0.5f);

    m_HearBox->SetTexture("HearBox", TEXT("HollowKnight/NPCS/Dir/Hear.png"));
    m_HearBox->SetWorldScale(139.f, 147.f);
    m_HearBox->SetPivot(0.5f, 0.5f);
    m_HearBox->AddRelativePositionY(180.f);
    m_HearBox->SetEnable(false);
    
    m_Sprite->SetTextureReverse(false);

    return true;
}

void CElderBugNPC::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
}

void CElderBugNPC::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

CElderBugNPC* CElderBugNPC::Clone() const
{
    return new CElderBugNPC(*this);
}

void CElderBugNPC::NPCUpKey()
{
    if (m_CollisionCheck)
    {
        int count = rand() % 5;
        char c[256] = {};
        sprintf_s(c, "%d", count);
        strcat_s(c, "ElderBugTalk");

        CResourceManager::GetInst()->SoundPlay(c);
        CMessageBoxUI* msg = m_Scene->GetViewport()->CreateUIWindow<CMessageBoxUI>("ElderBugMessage");
        msg->ElderBugMessage();

        CPlayer2D* player= (CPlayer2D*)(m_Scene->FindObject("Player2D"));
        CheckDir(player->GetWorldPos().x);
        player->ContactNPC(m_Body->GetWorldPos().x);

    }
}

void CElderBugNPC::CheckDir(float x)
{
    //닿은지점 확인해서 방향전환
    if (x < m_Body->GetWorldPos().x)
        m_Sprite->SetTextureReverse(true);
    else
        m_Sprite->SetTextureReverse(false);
}

void CElderBugNPC::CollisionBegin(const CollisionResult& Result)
{
    float x = Result.Dest->GetWorldPos().x;
    CheckDir(x);
    
    m_CollisionCheck = true;
    m_HearBox->SetEnable(true);
}

void CElderBugNPC::CollisionEnd(const CollisionResult& Result)
{
    m_CollisionCheck = false;
    m_HearBox->SetEnable(false);
}
