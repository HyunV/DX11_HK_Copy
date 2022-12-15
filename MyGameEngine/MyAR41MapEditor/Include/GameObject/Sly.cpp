#include "Sly.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Animation/Animation2D.h"
#include "Resource/ResourceManager.h" 
#include "Input.h"
#include "Scene/Scene.h"
#include "Player2D.h"
#include "../UI/ShopUI.h"

CSly::CSly()
{
	SetTypeID<CSly>();
	m_ObjectTypeName = "Sly";
}

CSly::CSly(const CSly& Obj)	:
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("SlyBody");
	m_Sprite = (CSpriteComponent*)FindComponent("SlySprite");
	m_HearBox = (CSpriteComponent*)FindComponent("HearBox");
}

CSly::~CSly()
{
	CInput::GetInst()->DeleteBindFunction("Up", Input_Type::Down, this);
}

void CSly::Start()
{
	CGameObject::Start();

	m_Body->SetCollisionCallback(ECollision_Result::Collision, this,
		&CSly::CollisionBegin);

	m_Body->SetCollisionCallback(ECollision_Result::Release, this,
		&CSly::CollisionEnd);

	CInput::GetInst()->AddBindFunction<CSly>("Up", Input_Type::Down, this,
		&CSly::NPCUpKey, m_Scene);

	CAnimation2D* Anim = m_Sprite->GetAnimation();
	Anim->SetCurrentAnimation("SlyIdle");

	CResourceManager::GetInst()->LoadSound("Effect", "SlyShop", false, "NPC/Sly_shop_open.wav");
}

bool CSly::Init()
{
	CGameObject::Init();
	m_Body = CreateComponent<CColliderBox2D>("SlyBody");
	m_Sprite = CreateComponent<CSpriteComponent>("SlySprite");
	m_HearBox = CreateComponent<CSpriteComponent>("HearBox");

	SetRootComponent(m_Body);
	m_Body->AddChild(m_Sprite);
	m_Body->AddChild(m_HearBox);

	m_Body->SetWorldPosition(760.f, 50.f);
	m_Body->SetBoxSize(100.f, 65.f);

	m_Body->SetCollisionProfile("NPC");
	m_Sprite->SetAnimationFile("NPCS");
	m_Sprite->SetRenderLayerName("Back");

	float x = 80.f * g_SCALE;
	float y = 134.f * g_SCALE;
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

void CSly::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CSly::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CSly* CSly::Clone() const
{
	return new CSly(*this);
}

void CSly::NPCUpKey()
{
	if (m_CollisionCheck)
	{
		CResourceManager::GetInst()->SoundPlay("SlyShop");
		CShopUI* msg = m_Scene->GetViewport()->CreateUIWindow<CShopUI>("SlyShop");

		CPlayer2D* player = (CPlayer2D*)(m_Scene->FindObject("Player2D"));
		CheckDir(player->GetWorldPos().x);
		player->ContactNPC(m_Body->GetWorldPos().x);
	}
}

void CSly::CheckDir(float x)
{
	//닿은지점 확인해서 방향전환
	if (x < m_Body->GetWorldPos().x)
		m_Sprite->SetTextureReverse(false);
	else
		m_Sprite->SetTextureReverse(true);
}

void CSly::CollisionBegin(const CollisionResult& Result)
{
	float x = Result.Dest->GetWorldPos().x;
	CheckDir(x);

	m_CollisionCheck = true;
	m_HearBox->SetEnable(true);
}

void CSly::CollisionEnd(const CollisionResult& Result)
{
	m_CollisionCheck = false;
	m_HearBox->SetEnable(false);
}
