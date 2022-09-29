
#include "Monster.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Resource/Material/Material.h"

CMonster::CMonster()
{
	SetTypeID<CMonster>();

	m_ObjectTypeName = "Monster";
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

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Sprite = CreateComponent<CSpriteComponent>("Sprite");

	m_Body->AddChild(m_Sprite);

	m_Sprite->SetPivot(0.5f, 0.f);

	m_Sprite->SetRelativeScale(100.f, 100.f);
	m_Sprite->SetRelativePosition(0.f, -50.f);
	m_Body->SetWorldPosition(500.f, 600.f);

	//m_Sprite->SetWorldPositionZ(0.5f);

//m_Sprite->GetMaterial(0)->SetOpacity(0.5f);
//m_Sprite->GetMaterial(0)->SetRenderState("DepthDisable");

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
