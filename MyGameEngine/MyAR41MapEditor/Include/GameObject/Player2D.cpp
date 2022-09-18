
#include "Player2D.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Device.h"
#include "MyBullet.h"
#include "Resource/Material/Material.h"


CPlayer2D::CPlayer2D()
{
	SetTypeID<CPlayer2D>();

	m_ObjectTypeName = "Player2D";
}

CPlayer2D::CPlayer2D(const CPlayer2D& Obj) :
	CGameObject(Obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("sprite");
	m_RightChild = (CSceneComponent*)FindComponent("RightChild");
	m_SpriteChild = (CSpriteComponent*)FindComponent("spriteChild");
	m_Camera = (CCameraComponent*)FindComponent("Camera");
	m_Arm = (CTargetArm*)FindComponent("Arm");
}

CPlayer2D::~CPlayer2D()
{
}

void CPlayer2D::Start()
{
	CGameObject::Start();

	if (m_Scene)
		m_Scene->GetCameraManager()->SetCurrentCamera(m_Camera);
}

bool CPlayer2D::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("sprite");
	m_RightChild = CreateComponent<CSceneComponent>("RightChild");
	m_SpriteChild = CreateComponent<CSpriteComponent>("spriteChild");
	m_Camera = CreateComponent<CCameraComponent>("Camera");
	m_Arm = CreateComponent<CTargetArm>("Arm");

	m_Sprite->AddChild(m_RightChild);

	m_Sprite->GetMaterial(0)->SetBaseColorUnsignedChar(255, 255, 0, 255);

	m_Sprite->AddChild(m_Arm);
	m_Arm->AddChild(m_Camera);

	Resolution RS = CDevice::GetInst()->GetResolution();

	float Width = (float)RS.Width / 2.f;
	float Height = (float)RS.Height / 2.f;

	m_Arm->SetTargetOffset(Vector3(-Width, -Height, 0.f));

	m_RightChild->AddChild(m_SpriteChild);

	m_Sprite->SetRelativeScale(100.f, 100.f);
	m_Sprite->SetWorldPosition(500.f, 500.f);
	m_Sprite->SetPivot(0.5f, 0.5f);

	CMaterial* Material = m_Sprite->GetMaterial(0);

	Material->SetOpacity(0.5f);
	//Material->SetRenderState("DepthDisable");

	m_RightChild->SetRelativePosition(150.f, 0.f);
	m_RightChild->SetInheritRotZ(true);

	m_SpriteChild->SetRelativeScale(50.f, 50.f);
	m_SpriteChild->SetRelativePosition(100.f, 0.f);
	m_SpriteChild->SetInheritRotZ(true);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Rotation", Input_Type::Push,
		this, &CPlayer2D::RotationInv, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("RotationInv", Input_Type::Push,
		this, &CPlayer2D::Rotation, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveUp", Input_Type::Push,
		this, &CPlayer2D::MoveUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveDown", Input_Type::Push,
		this, &CPlayer2D::MoveDown, m_Scene);

	//Ãß°¡
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Fire", Input_Type::Down, this,
		&CPlayer2D::Fire, m_Scene);

	return true;
}

void CPlayer2D::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	//m_Sprite->AddRelativeRotationZ(180.f * DeltaTime);

	//m_RightChild->AddRelativeRotationZ(360.f * DeltaTime);
}

void CPlayer2D::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CPlayer2D* CPlayer2D::Clone() const
{
	return new CPlayer2D(*this);
}

void CPlayer2D::MoveUp()
{
	m_Sprite->AddWorldPosition(m_Sprite->GetWorldAxis(AXIS_Y) * 300.f * g_DeltaTime);
}

void CPlayer2D::MoveDown()
{
	m_Sprite->AddWorldPosition(m_Sprite->GetWorldAxis(AXIS_Y) * -300.f * g_DeltaTime);
}

void CPlayer2D::Rotation()
{
	m_Sprite->AddWorldRotationZ(360.f * g_DeltaTime);
}

void CPlayer2D::RotationInv()
{
	m_Sprite->AddWorldRotationZ(-360.f * g_DeltaTime);
}

void CPlayer2D::Fire()
{
	CMyBullet* Bullet = m_Scene->CreateObject<CMyBullet>("MyBullet");
	Bullet->SetWorldPosition(m_Sprite->GetWorldPos());
	Vector3 v3 = m_Sprite->GetWorldRot();
	Bullet->SetWorldRotationZ(v3.z);

	CMyBullet* Bullet2 = m_Scene->CreateObject<CMyBullet>("MyBullet2");
	Bullet2->SetWorldPosition(m_Sprite->GetWorldPos());
	//Bullet2->AddWorldRotationZ(15.f * g_DeltaTime);
	Bullet2->SetWorldRotationZ(m_Sprite->GetWorldRot().z+15.f);

	CMyBullet* Bullet3 = m_Scene->CreateObject<CMyBullet>("MyBullet3");
	Bullet3->SetWorldPosition(m_Sprite->GetWorldPos());
	Bullet3->SetWorldRotationZ(m_Sprite->GetWorldRot().z - 15.f);
}
