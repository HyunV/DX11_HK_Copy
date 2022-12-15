#include "Hornet.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Animation/Animation2D.h"
#include "Resource/ResourceManager.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "../UI/MessageBoxUI.h"
#include "Player2D.h"
#include <time.h>

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
    m_HearBox = (CSpriteComponent*)FindComponent("HearBox");
}

CHornet::~CHornet()
{
    CInput::GetInst()->DeleteBindFunction("Up", Input_Type::Down, this);
}

void CHornet::Start()
{
    CGameObject::Start();

    m_Body->SetCollisionCallback(ECollision_Result::Collision, this,
        &CHornet::CollisionBegin);

    m_Body->SetCollisionCallback(ECollision_Result::Release, this,
        &CHornet::CollisionEnd);

    CInput::GetInst()->AddBindFunction<CHornet>("Up", Input_Type::Down, this,
        &CHornet::NPCUpKey, m_Scene);

    CAnimation2D* Anim = m_Sprite->GetAnimation();
    Anim->SetCurrentAnimation("HonnetIdle");

    Anim->SetPlayScale("HonnetIdle", 1.f);

    CResourceManager::GetInst()->LoadSound("Effect", "0HornetTalk", false, "NPC/Hornet_Dialogue_Generic_02.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "1HornetTalk", false, "NPC/Hornet_Dialogue_Generic_03.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "2HornetTalk", false, "NPC/Hornet_Dialogue_Generic_04.wav");
    CResourceManager::GetInst()->LoadSound("Effect", "3HornetTalk", false, "NPC/Hornet_Dialogue_Generic_05.wav");
}

bool CHornet::Init()
{
    CGameObject::Init();

    m_Body = CreateComponent<CColliderBox2D>("HornetBody");
    m_Sprite = CreateComponent<CSpriteComponent>("HornetSprite");
    m_HearBox = CreateComponent<CSpriteComponent>("HearBox");

    SetRootComponent(m_Body);
    m_Body->AddChild(m_Sprite);
    m_Body->AddChild(m_HearBox);

    m_Body->SetWorldPosition(900.f, 68.f);
    m_Body->SetBoxSize(60.f, 120.f);

    m_Body->SetCollisionProfile("NPC");

    m_Sprite->SetAnimationFile("NPCS");
    m_Sprite->SetRenderLayerName("Back");

    float x = 381.f * g_SCALE;
    float y = 249.f * g_SCALE;
    m_Sprite->SetWorldScale(x, y);
    m_Sprite->SetPivot(0.5f, 0.5f);

    m_HearBox->SetTexture("HearBox", TEXT("HollowKnight/NPCS/Dir/Hear.png"));
    m_HearBox->SetWorldScale(139.f, 147.f);
    m_HearBox->SetPivot(0.5f, 0.5f);
    m_HearBox->AddRelativePositionY(180.f);
    m_HearBox->SetEnable(false);

    m_Sprite->SetTextureReverse(false);
    m_CollisionCheck = false;

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

void CHornet::NPCUpKey()
{
    if (m_CollisionCheck)
    {
        int count = rand() % 4;
        char c[256] = {};
        sprintf_s(c, "%d", count);
        strcat_s(c, "HornetTalk");
        
        CResourceManager::GetInst()->SoundPlay(c);
        CMessageBoxUI* msg = m_Scene->GetViewport()->CreateUIWindow<CMessageBoxUI>("HonnetMessage");
        msg->HonnetMessage();

        CPlayer2D* player = (CPlayer2D*)(m_Scene->FindObject("Player2D"));
        CheckDir(player->GetWorldPos().x);
        player->ContactNPC(m_Body->GetWorldPos().x);
    }
}

void CHornet::CheckDir(float x)
{
    //닿은지점 확인해서 방향전환
    if (x < m_Body->GetWorldPos().x)
        m_Sprite->SetTextureReverse(false);
    else
        m_Sprite->SetTextureReverse(true);
}

void CHornet::CollisionBegin(const CollisionResult& Result)
{
    float x = Result.Dest->GetWorldPos().x;
    CheckDir(x);

    m_CollisionCheck = true;
    m_HearBox->SetEnable(true);
}

void CHornet::CollisionEnd(const CollisionResult& Result)
{
    m_CollisionCheck = false;
    m_HearBox->SetEnable(false);
}