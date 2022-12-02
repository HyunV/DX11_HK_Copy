#include "Brum.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Animation/Animation2D.h"
#include "Resource/ResourceManager.h"

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
}

CBrum::~CBrum()

{
}

void CBrum::Start()
{
	CGameObject::Start();

	m_Body->SetCollisionCallback(ECollision_Result::Collision, this, 
		&CBrum::CollisionBegin);
	m_Body->SetCollisionCallback(ECollision_Result::Release, this,
		&CBrum::CollisionEnd);

	CAnimation2D* Anim = m_Sprite->GetAnimation();
	Anim->SetCurrentAnimation("BrumIdle");

	CResourceManager::GetInst()->LoadSound("BGM", "BrummTheme", true, "NPC/Brumm accordion - S83-14 Accordion.wav");
	//CResourceManager::GetInst()->SoundPlay("BrummTheme");
	m_Check = false;
}

bool CBrum::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderBox2D>("BrumBody");
	m_Sprite = CreateComponent<CSpriteComponent>("BrumSprite");

	SetRootComponent(m_Sprite);

	m_Body->SetCollisionProfile("NPC");
	m_Sprite->SetAnimationFile("BrumNPC");
	
	//д©╫╨ер
	m_Sprite->SetWorldPosition(100.f, 100.f);

	float x = 329.f * g_SCALE;
	float y = 344.f * g_SCALE;

	m_Sprite->SetWorldScale(x, y);
	m_Sprite->SetPivot(0.5f, 0.5f);




	m_Sprite->AddChild(m_Body);
	m_Body->SetBoxSize(150.f, 150.f);

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

void CBrum::CollisionBegin(const CollisionResult& Result)
{
	OutputDebugStringA("ho");
	if (!m_Check)
	{
		CResourceManager::GetInst()->SoundPlay("BrummTheme");
		CResourceManager::GetInst()->SetVolume("BGM", 100);
		m_Check = true;
	}
	else 
	{
		CResourceManager::GetInst()->SoundResume("BrummTheme");
	}

	CAnimation2D* Anim = m_Sprite->GetAnimation();
	//Anim->SetCurrentAnimation("HornetIdle");
}

void CBrum::CollisionEnd(const CollisionResult& Result)
{
	OutputDebugStringA("oh");
	CResourceManager::GetInst()->SoundPause("BrummTheme");

	CAnimation2D* Anim = m_Sprite->GetAnimation();
	Anim->SetCurrentAnimation("BrumIdle");
}
