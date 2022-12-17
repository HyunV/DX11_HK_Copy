#include "FlameBall.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderSphere2D.h"
#include "Animation/Animation2D.h"

CFlameBall::CFlameBall()
{
	SetTypeID<CFlameBall>();

	m_ObjectTypeName = "FlameBall";
}

CFlameBall::CFlameBall(const CFlameBall& Obj)	:
	CGameObject(Obj)
{
}

CFlameBall::~CFlameBall()
{
}

void CFlameBall::SetTextureReverse(bool Enable)
{
	m_Sprite->SetTextureReverse(Enable);
}

void CFlameBall::Start()
{
	CGameObject::Start();
}

bool CFlameBall::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderSphere2D>("FlameBall");
	m_Sprite = CreateComponent<CSpriteComponent>("FlameBallSprite");

	SetRootComponent(m_Body);
	m_Body->AddChild(m_Sprite);
	m_Body->SetRadius(30.f);
	m_Body->SetCollisionProfile("MonsterAttack");

	m_Sprite->SetAnimationFile("GrimmBullet");
	CAnimation2D* Anim = m_Sprite->GetAnimation();
	Anim->SetCurrentAnimation("Grimm FlameBall");
	Anim->SetPlayScale("Grimm FlameBall", 2.f);

	m_Sprite->SetPivot(0.5f, 0.5f);
	m_Sprite->SetWorldScale(106.f, 115.f);

	SetWorldPosition(0.f, 0.f);

	m_Dir = 1.f;
	m_Height = 0.f;
	m_BallDir = EFireBallDirection::None;

	SetLifeTime(5.f);
	m_Speed.x = 700.f;
	m_Speed.y = 500.f;

	return true;
}

void CFlameBall::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	float h = GetWorldPos().y;

	switch (m_BallDir)
	{
	case EFireBallDirection::None:
		AddWorldPositionX(m_Dir * m_Speed.x * DeltaTime);
		break;
	case EFireBallDirection::Up:
		if (h >= m_Height)
			m_Speed.y = 0.f;

		AddWorldPosition(m_Dir * m_Speed.x * DeltaTime, m_Speed.y * DeltaTime);
		break;
	case EFireBallDirection::Down:
		if (h <= m_Height)
			m_Speed.y = 0.f;

		AddWorldPosition(m_Dir * m_Speed.x * DeltaTime, -m_Speed.y * DeltaTime);
		break;

	case EFireBallDirection::OnlyDown:
		AddWorldPositionY(-m_Speed.y* DeltaTime);
		break;
	default:
		break;
	}		
}
