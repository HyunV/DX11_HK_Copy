#include "Brum.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Animation/Animation2D.h"
#include "Resource/ResourceManager.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "../UI/MessageBoxUI.h"
#include "Player2D.h"

CBrum::CBrum()
{
	SetTypeID<CBrum>();
	m_ObjectTypeName = "Brum";
}

CBrum::CBrum(const CBrum& Obj)	:
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("BrumBody");
	m_Sprite = (CSpriteComponent*)FindComponent("BrumSprite");
	m_HearBox = (CSpriteComponent*)FindComponent("HearBox");
}

CBrum::~CBrum()
{
	CInput::GetInst()->DeleteBindFunction("Up", Input_Type::Down, this);
}

void CBrum::Start()
{
	CGameObject::Start();

	m_Body->SetCollisionCallback(ECollision_Result::Collision, this, 
		&CBrum::CollisionBegin);
	m_Body->SetCollisionCallback(ECollision_Result::Release, this,
		&CBrum::CollisionEnd);

	CInput::GetInst()->AddBindFunction<CBrum>("Up", Input_Type::Down, this,
		&CBrum::NPCUpKey, m_Scene);

	CAnimation2D* Anim = m_Sprite->GetAnimation();
	Anim->SetCurrentAnimation("BrumIdle");

	CResourceManager::GetInst()->LoadSound("BGM", "BrummTheme", true, "NPC/Brumm accordion - S83-14 Accordion.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "0BrummTalk", false, "NPC/Brumm_talk_01.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "1BrummTalk", false, "NPC/Brumm_talk_02.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "2BrummTalk", false, "NPC/Brumm_talk_03.wav");
	
	m_Check = false;
}

bool CBrum::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderBox2D>("BrumBody");
	m_Sprite = CreateComponent<CSpriteComponent>("BrumSprite");
	m_HearBox = CreateComponent<CSpriteComponent>("HearBox");

	SetRootComponent(m_Body);
	m_Body->AddChild(m_Sprite);
	m_Body->AddChild(m_HearBox);

	m_Body->SetWorldPosition(100.f, 100.f);
	m_Body->SetBoxSize(150.f, 150.f);
	
	m_Body->SetCollisionProfile("NPC");
	m_Sprite->SetAnimationFile("BrumNPC");
	
	//д©╫╨ер	
	float x = 329.f * g_SCALE;
	float y = 344.f * g_SCALE;
	m_Sprite->SetWorldScale(x, y);
	m_Sprite->SetPivot(0.5f, 0.5f);

	m_HearBox->SetTexture("HearBox", TEXT("HollowKnight/NPCS/Dir/Hear.png"));
	m_HearBox->SetWorldScale(139.f, 147.f);
	m_HearBox->SetPivot(0.5f, 0.5f);
	m_HearBox->AddRelativePositionY(180.f);
	m_HearBox->SetEnable(false);

	m_CollisionCheck = false;
	return true;
}

void CBrum::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBrum::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBrum* CBrum::Clone() const
{
	return new CBrum(*this);
}

void CBrum::NPCUpKey()
{
	if (m_CollisionCheck)
	{
		int count = rand() % 3;
		char c[256] = {};
		sprintf_s(c, "%d", count);
		strcat_s(c, "BrummTalk");

		CResourceManager::GetInst()->SoundPlay(c);
		CMessageBoxUI* msg = m_Scene->GetViewport()->CreateUIWindow<CMessageBoxUI>("BrumMessage");
		msg->BrumMessage();

		CPlayer2D* player = (CPlayer2D*)(m_Scene->FindObject("Player2D"));
		player->ContactNPC(m_Body->GetWorldPos().x);
	}
}

void CBrum::CollisionBegin(const CollisionResult& Result)
{
	if (!m_Check)
	{
		CResourceManager::GetInst()->SoundPlay("BrummTheme");
		CResourceManager::GetInst()->SetVolume("BGM", 100);
		m_Check = true;
	}
	else 
		CResourceManager::GetInst()->SoundResume("BrummTheme");

	m_CollisionCheck = true;
	m_HearBox->SetEnable(true);
}

void CBrum::CollisionEnd(const CollisionResult& Result)
{	
	CResourceManager::GetInst()->SoundPause("BrummTheme");
	
	m_CollisionCheck = false;
	m_HearBox->SetEnable(false);
}
