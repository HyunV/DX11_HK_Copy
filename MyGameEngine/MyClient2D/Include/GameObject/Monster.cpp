
#include "Monster.h"
#include "Component/SpriteComponent.h"

CMonster::CMonster()
{
	SetTypeID<CMonster>();
}

CMonster::CMonster(const CMonster& Obj) :
	CGameObject(Obj)
{
}

CMonster::~CMonster()
{
}

void CMonster::Start()
{
	CGameObject::Start();
}

bool CMonster::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("Sprite");

	m_Sprite->SetRelativeScale(100.f, 100.f);
	m_Sprite->SetWorldPosition(500.f, 600.f);

	return true;
}

void CMonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CMonster::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CMonster* CMonster::Clone() const
{
	return new CMonster(*this);
}
