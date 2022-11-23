
#include "Monster.h"
#include "Component/SpriteComponent.h"
#include "Resource/Material/Material.h"

#include "Component/ColliderBox2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderPixel.h"

CMonster::CMonster()
{
	SetTypeID<CMonster>();

	m_ObjectTypeName = "Monster";
}

CMonster::CMonster(const CMonster& Obj) :
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_Sprite = (CSpriteComponent*)FindComponent("Sprite");
}

CMonster::~CMonster()
{
}

void CMonster::Start()
{
	CGameObject::Start();

	//�ȼ� �ݶ��̴� �϶�
	//m_Body->SetInfo("PixelCollision", TEXT("PixelCollision.png"));
	//m_Body->SetPixelColorCollisionType(EPixelCollision_Type::Color_Ignore);
	//m_Body->SetPixelColor(255, 0, 255);
	//m_Body->SetInfo("PixelCollision", TEXT("End.png"));
}

bool CMonster::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Sprite = CreateComponent<CSpriteComponent>("Sprite");
	SetRootComponent(m_Body);

	m_Body->SetWorldPosition(100.f, 100.f);
	m_Body->SetBoxSize(500.f, 500.f);
	m_Body->AddChild(m_Sprite);
	m_Sprite->SetTexture("tm", TEXT("teemo.png"));
	m_Sprite->SetWorldScale(200.f, 200.f);


	//m_Sprite->AddChild(m_Sprite);
	//m_Body->AddChild(m_Sprite);
	
	//m_Body->SetCollisionProfile("Monster");

	//m_Sprite->SetPivot(0.5f, 0.5f);
	//m_Sprite->SetRelativeScale(100.f, 100.f);
	
	//m_Sprite->SetRelativePosition(300.f, 300.f);
	//m_Sprite->SetWorldPosition(100.f, 100.f);
	//m_Body->SetWorldPosition(500.f, 600.f);

	//m_Sprite->SetWorldPositionZ(0.5f);

//m_Sprite->GetMaterial(0)->SetOpacity(0.5f);
//m_Sprite->GetMaterial(0)->SetRenderState("DepthDisable");

	//===========MyTest
	//m_Body = CreateComponent<CColliderBox2D>("Body");
	//m_Body->SetCollisionProfile("Monster");
	//m_Body->SetBoxSize(300.f, 300.f);
	//m_Body->SetPivot(0.f, 0.f);
	
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
