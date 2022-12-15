#include "FirePillarBullet.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Animation/Animation2D.h"
#include "FlameParticle.h"
#include "Resource/Material/Material.h"
#include "Scene/Scene.h"

CFirePillarBullet::CFirePillarBullet()
{
	SetTypeID<CFirePillarBullet>();

	m_ObjectTypeName = "FirePillar";
}

CFirePillarBullet::CFirePillarBullet(const CFirePillarBullet& Obj)	:
	CGameObject(Obj)
{
}

CFirePillarBullet::~CFirePillarBullet()
{
}

void CFirePillarBullet::Start()
{
	CGameObject::Start();
	CResourceManager::GetInst()->LoadSound("Effect", "FirePillar", false, "Boss/grimm_explode_into_bats.wav");
}

bool CFirePillarBullet::Init()
{
	CGameObject::Init();
	SetLifeTime(3.f);

	m_Body = CreateComponent<CColliderBox2D>("FirePillar");
	m_Sprite = CreateComponent<CSpriteComponent>("FirePillarSprite");

	SetRootComponent(m_Body);
	m_Body->AddChild(m_Sprite);
	m_Body->SetEnable(false);

	m_Body->SetBoxSize(50.f, 2000.f);
	m_Body->SetCollisionProfile("MonsterAttack");

	m_Sprite->SetAnimationFile("GrimmBullet");
	CAnimation2D* Anim = m_Sprite->GetAnimation();
	Anim->SetCurrentAnimation("Grimm FireMineEffect");
	Anim->SetPlayScale("Grimm FireMineEffect", 3.f);
	Anim->SetPlayScale("Grimm FirePillarEffect", 3.f);
	m_Sprite->SetPivot(0.5f, 0.f);
	m_Sprite->SetWorldScale(387.f, 865.f);
	m_Sprite->SetWorldPosition(0.f, -40.f);
	m_Sprite->GetMaterial(0)->SetBaseColorUnsignedChar(255, 100, 100, 255);
	m_flick = true;

	return true;
}

void CFirePillarBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Time += DeltaTime;

	if (m_flick)
	{
		if (m_Opacity)
		{
			m_Sprite->GetMaterial(0)->SetOpacity(0.5f);
			m_Opacity = false;
		}
		else
		{
			m_Sprite->GetMaterial(0)->SetOpacity(1.f);
			m_Opacity = true;
		}
	}

	if (m_Time >= 0.5f)
	{
		if (!m_FireStart)
		{	
			CAnimation2D* Anim = m_Sprite->GetAnimation();
			Anim->SetCurrentAnimation("Grimm FirePillarEffect");
			CResourceManager::GetInst()->SoundPlay("FirePillar");
			m_flick = false;
			m_Sprite->GetMaterial(0)->SetOpacity(1.f);
			m_Body->SetEnable(true);
		}
		m_FireStart = true;					
	}
	if (m_Time >= 1.1f)
	{
		CFlameParticle* Part = m_Scene->CreateObject<CFlameParticle>("FlameDummy");
		Part->SetWorldPosition(GetWorldPos());
		Part->EnableMineFlame();
		Part->SetLifeTime(1.f);
		Part->SetFlick(true);
		Part->EnableCollider(true);
		Destroy();
	}
}
