#include "Gio.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/GravityAgent.h"
#include "Animation/Animation2D.h"
#include "Effect.h"
#include "Scene/Scene.h"

CGio::CGio()
{
	SetTypeID<CGio>();

	m_ObjectTypeName = "Gio";
}

CGio::CGio(const CGio& Obj)
{

}

CGio::~CGio()
{
}

void CGio::Start()
{
	CGameObject::Start();
}

bool CGio::Init()
{
	CGameObject::Init();

	//CSharedPtr<class CSpriteComponent>	m_Sprite;
	//CSharedPtr<class CColliderSphere2D>	m_Body;
	//CSharedPtr<class CGravityAgent> m_Gravity;

	m_Body = CreateComponent<CColliderBox2D>("Gio");
	m_Sprite = CreateComponent<CSpriteComponent>("GioSprite");
	m_Gravity = CreateComponent<CGravityAgent>("Gravity");
	m_Gravity->SetPhysicsSimulate(true);
	m_Gravity->SetGravityAccel(1.f);
	m_Gravity->SetJumpVelocity(1.f);

	m_Body->SetCollisionProfile("MonsterSight");
	m_Body->SetCollisionCallback(ECollision_Result::Collision, this, &CGio::CollisionCoin);
	m_Body->SetBoxSize(30.f, 30.f);

	SetRootComponent(m_Body);
	m_Body->AddChild(m_Sprite);

	m_Sprite->SetAnimationFile("Effects");
	m_Sprite->GetAnimation()->SetCurrentAnimation("Gio");
	m_Sprite->GetAnimation()->SetPlayScale("Gio", 2.f);
	m_Sprite->SetPivot(0.5f, 0.5f);
	m_Sprite->SetWorldScale(30.f, 30.f);

	return true;
}

void CGio::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (!m_Jump)
	{
		m_Gravity->ObjectJump();
		m_Jump = true;
	}
	else
	{
		if (m_Gravity->GetJump())
			AddWorldPosition(GetWorldAxis(AXIS_X) * m_Dir * m_Range * g_DeltaTime);
		else
			m_Gravity->SetPhysicsSimulate(false);
	}
	m_Time += DeltaTime;
}


CGio* CGio::Clone() const
{
	return new CGio(*this);
}

void CGio::CollisionCoin(const CollisionResult& result)
{
	if (m_Time >= 0.7f)
	{
		OutputDebugStringA("µ· È¹µæ");
		Destroy();
	}
}
