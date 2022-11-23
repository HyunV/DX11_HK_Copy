#include "Sly.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Animation/Animation2D.h"
#include "Resource/ResourceManager.h" 

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
}

CSly::~CSly()
{
}

void CSly::Start()
{
	CGameObject::Start();

	m_Body->SetCollisionCallback(ECollision_Result::Collision, this,
		&CSly::CollisionCallback);

	CAnimation2D* Anim = m_Sprite->GetAnimation();
	Anim->SetCurrentAnimation("SlyIdle");
}

bool CSly::Init()
{
	CGameObject::Init();
	m_Body = CreateComponent<CColliderBox2D>("SlyBody");
	m_Sprite = CreateComponent<CSpriteComponent>("SlySprite");

	SetRootComponent(m_Sprite);

	m_Body->SetCollisionProfile("NPC");
	m_Sprite->SetAnimationFile("NPCS");

	float x = 80.f * g_SCALE;
	float y = 134.f * g_SCALE;

	m_Sprite->SetWorldPosition(100.f, 100.f);
	m_Sprite->SetWorldScale(x, y);
	m_Sprite->SetPivot(0.5f, 0.5f);



	m_Sprite->AddChild(m_Body);
	m_Body->SetBoxSize(100.f, 65.f);

	m_Sprite->SetTextureReverse(false);

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

void CSly::CollisionCallback(const CollisionResult& Result)
{
}
