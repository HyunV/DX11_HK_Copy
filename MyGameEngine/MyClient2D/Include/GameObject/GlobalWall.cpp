#include "GlobalWall.h"
#include "Component/ColliderBox2D.h"

CGlobalWall::CGlobalWall()
{
	SetTypeID<CGlobalWall>();
	m_ObjectTypeName = "GlobalWall";
}

CGlobalWall::CGlobalWall(const CGlobalWall& Obj)	:
	CGameObject(Obj)
{
	m_Wall = (CColliderBox2D*)FindComponent("GlobalWall");
}

CGlobalWall::~CGlobalWall()
{
}

void CGlobalWall::Start()
{
	CGameObject::Start();
}

bool CGlobalWall::Init()
{
	m_Wall = CreateComponent<CColliderBox2D>("GlobalWall");	
	SetRootComponent(m_Wall);
	m_Wall->SetCollisionProfile("Wall");

	m_Wall->SetWorldPosition(640.f, 360.f);
	m_Wall->SetBoxSize(1280.f, 720.f);
	return true;
}

void CGlobalWall::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CGlobalWall::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGlobalWall* CGlobalWall::Clone() const
{
	return new CGlobalWall(*this);
}

void CGlobalWall::CollisionCallback(const CollisionResult& Result)
{
}
