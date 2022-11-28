#include "MyBullet.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderSphere2D.h"
#include "Player2D.h"


CMyBullet::CMyBullet()
{
	SetTypeID<CMyBullet>();

	m_ObjectTypeName = "MyBullet";
}

CMyBullet::CMyBullet(const CMyBullet& Obj)	:
	CGameObject(Obj)
{
}

CMyBullet::~CMyBullet()
{
}

void CMyBullet::SetCollisionProfileName(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
}

void CMyBullet::Start()
{
	CGameObject::Start();
}

bool CMyBullet::Init()
{
	CGameObject::Init();
	SetLifeTime(0.7f);
	m_Body = CreateComponent<CColliderSphere2D>("Body");
	m_Sprite = CreateComponent<CSpriteComponent>("spritebullet");

	m_Body->AddChild(m_Sprite);

	m_Body->SetCollisionCallback<CMyBullet>(ECollision_Result::Collision, this, &CMyBullet::CollisionBullet);

	m_Sprite->SetPivot(0.5f, 0.5f);

	m_Sprite->SetRelativeScale(20.f, 20.f);
	//m_Sprite->SetWorldPosition(500.f, 500.f);
	return true;
}

void CMyBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	AddWorldPosition(GetWorldAxis(AXIS_X) * 2500.f * DeltaTime);
}

void CMyBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CMyBullet* CMyBullet::Clone() const
{
	return new CMyBullet(*this);
}

void CMyBullet::CollisionBullet(const CollisionResult& result)
{
	Destroy();
}
