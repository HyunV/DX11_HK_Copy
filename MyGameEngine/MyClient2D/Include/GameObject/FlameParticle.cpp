#include "FlameParticle.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderSphere2D.h"
#include "Resource/Material/Material.h"

CFlameParticle::CFlameParticle()
{
	SetTypeID<CFlameParticle>();

	m_ObjectTypeName = "FlameParticle";
}

CFlameParticle::CFlameParticle(const CFlameParticle& Obj)	:
	CGameObject(Obj)
{
}

CFlameParticle::~CFlameParticle()
{
}

void CFlameParticle::EnableCollider(bool Enable)
{
	m_Body->SetEnable(Enable);
}

void CFlameParticle::SetFlick(bool Enable)
{
	m_flick = Enable;

	if (!m_flick)
	{
		m_Sprite->GetMaterial(0)->SetOpacity(1.f);
		m_Opacity = true;
	}
		
}

void CFlameParticle::SetOpacity(float opacity)
{
	m_Sprite->GetMaterial(0)->SetOpacity(opacity);
}

void CFlameParticle::SetDepthDisable()
{
	m_Sprite->GetMaterial(0)->SetRenderState("DepthDisable");
}

void CFlameParticle::SetBoxSize(float x, float y)
{
	m_Body->SetRadius(x);
}

void CFlameParticle::SetImageSize(float x, float y)
{
	m_Sprite->SetWorldScale(x, y);
}

void CFlameParticle::Start()
{
	CGameObject::Start();
}

bool CFlameParticle::Init()
{
	SetLifeTime(0.5f);

	m_Body = CreateComponent<CColliderSphere2D>("FlameParticle");
	m_Sprite = CreateComponent<CSpriteComponent>("FlameSprite");

	SetRootComponent(m_Body);
	m_Body->AddChild(m_Sprite);

	m_Body->SetCollisionProfile("MonsterAttack");
	m_Body->SetRadius(50.f);
	m_Body->SetWorldPosition(100.f, 100.f);

	m_Sprite->SetPivot(0.5f, 0.5f);
	m_Sprite->SetTexture("FlameParticle", TEXT("HollowKnight/Boss/Event/pFlame.png"));
	m_Sprite->SetWorldScale(248.f, 247.f);

	m_Body->SetEnable(false);
	m_Speed = 1.f;

	m_Sprite->GetMaterial(0)->SetRenderState("DepthDisable");
	return true;
}

void CFlameParticle::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

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

	if(!m_MineFlame)
		AddWorldPosition(GetWorldAxis(AXIS_X) * 1500.f * m_Speed * DeltaTime);
}

void CFlameParticle::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CFlameParticle* CFlameParticle::Clone() const
{
	return new CFlameParticle(*this);
}

void CFlameParticle::CollisionBullet(const CollisionResult& result)
{
}
