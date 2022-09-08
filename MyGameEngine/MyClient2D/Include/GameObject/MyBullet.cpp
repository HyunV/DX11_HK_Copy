#include "MyBullet.h"
#include "Component/SpriteComponent.h"
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

void CMyBullet::Start()
{
	CGameObject::Start();
}

bool CMyBullet::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("spritebullet");

	m_Sprite->SetRelativeScale(20.f, 20.f);
	m_Sprite->SetWorldPosition(500.f, 500.f);
	return true;
}

void CMyBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	m_Sprite->AddWorldPosition(m_Sprite->GetWorldAxis(AXIS_X) * 500.f * g_DeltaTime);
}

void CMyBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}
