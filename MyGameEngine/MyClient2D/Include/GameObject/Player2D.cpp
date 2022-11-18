
#include "Player2D.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Device.h"
#include "MyBullet.h"
#include "Resource/Material/Material.h"
#include "Animation/Animation2D.h"

#include "Component/GravityAgent.h"

#include "Engine.h"


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
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_GravityAgent = (CGravityAgent*)FindComponent("GravityAgent");
}

CPlayer2D::~CPlayer2D()
{
}

void CPlayer2D::Start()
{
	CGameObject::Start();

	if (m_Scene)
		m_Scene->GetCameraManager()->SetCurrentCamera(m_Camera);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Rotation", Input_Type::Push,
		this, &CPlayer2D::RotationInv, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("RotationInv", Input_Type::Push,
		this, &CPlayer2D::Rotation, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveUp", Input_Type::Push,
		this, &CPlayer2D::MoveUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveDown", Input_Type::Push,
		this, &CPlayer2D::MoveDown, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Left", Input_Type::Push, this, 
		&CPlayer2D::LeftMove, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Right", Input_Type::Push, this,
		&CPlayer2D::RightMove, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Space", Input_Type::Push, this,
		&CPlayer2D::Jump, m_Scene);

	//추가
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Shift", Input_Type::Down, this,
		&CPlayer2D::Fire, m_Scene);
}

bool CPlayer2D::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("sprite");
	m_RightChild = CreateComponent<CSceneComponent>("RightChild");
	m_SpriteChild = CreateComponent<CSpriteComponent>("spriteChild");
	m_Camera = CreateComponent<CCameraComponent>("Camera");
	m_Arm = CreateComponent<CTargetArm>("Arm");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Body->SetBoxSize(100.f, 100.f);
	m_GravityAgent = CreateComponent<CGravityAgent>("GravityAgent");

	SetRootComponent(m_Body);

	m_Body->SetCollisionProfile("Player");

	m_Body->AddChild(m_Sprite);

	m_Sprite->AddChild(m_RightChild);

	//m_Sprite->GetMaterial(0)->SetBaseColorUnsignedChar(255, 0, 0, 255); //컬러

	m_Sprite->AddChild(m_Arm);
	m_Arm->AddChild(m_Camera);

	Resolution RS = CDevice::GetInst()->GetResolution();

	float Width = (float)RS.Width / 2.f;
	float Height = (float)RS.Height / 2.f;

	m_Arm->SetTargetOffset(Vector3(-Width, -Height, 0.f));

	m_RightChild->AddChild(m_SpriteChild);

	m_Body->SetWorldPosition(500.f, 500.f);
	m_Body->SetCollisionCallback(ECollision_Result::Collision, this, &CPlayer2D::CollisionBegin);

	m_Sprite->SetRelativeScale(100.f, 100.f);
	m_Sprite->SetPivot(0.5f, 0.5f);
	m_Sprite->SetInheritRotZ(true);
	m_Sprite->SetTexture("Grim", TEXT("Nightmare Grimm Anim/002.Idle/002-03-062.png"));
	//m_Sprite->SetRelativeScale(259.f*0.5, 436.f*0.5);
	m_Sprite->SetRelativeScale(102.f, 106.f);
	//m_Sprite->SetRelativeRotationZ(30.f);

	CMaterial* Material = m_Sprite->GetMaterial(0);

	//Material->SetOpacity(0.5f);
	
	//Material->SetRenderState("DepthDisable");

	m_RightChild->SetRelativePosition(0.f, 0.f);
	m_RightChild->SetInheritRotZ(true);

	m_SpriteChild->SetRelativeScale(50.f, 50.f);
	m_SpriteChild->SetRelativePosition(0.f, 0.f);
	m_SpriteChild->SetPivot(0.5f, 0.5f);
	m_SpriteChild->SetInheritRotZ(true);

	//m_SpriteChild->SetAnimationFile("MainSystemUI");
	//m_SpriteChild->GetMaterial(0)->SetBaseColorUnsignedChar(250, 250, 250, 255);
	//m_SpriteChild->SetRelativeScale(60.f, 60.f);
	// 
	//CAnimation2D* Anims = m_SpriteChild->GetAnimation();
	//Anims->SetCurrentAnimation("Flame");

	m_Sprite->SetAnimationFile("AnimationTest");
	CAnimation2D* Anim = m_Sprite->GetAnimation();
	//
	//Anim->AddAnimation("Idle", "AtlasTest5");
	//Anim->AddAnimation("Run", "FrameGrimTest3");
	//
	/*Anim->SetLoop("Idle", true);
	Anim->SetLoop("Run", true);*/
	
	Anim->SetCurrentAnimation("AtlasTest3");
	Anim->SetLoop("AtlasTest3", true);
	m_Sprite->SetTextureReverse(true);

	//Anim->TextureReverse(true);
	//Anim->SetLoop("Flame", true);

	m_GravityAgent->SetPhysicsSimulate(false);
	//m_GravityAgent->SetJumpVelocity(60.f);

	m_GravityAgent->SetPhysicsSimulate(true);
	m_GravityAgent->SetJumpVelocity(60.f);

	m_TimeTest = 0;
	return true;
}

void CPlayer2D::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	//m_TimeTest += DeltaTime;
	//if (m_TimeTest > 1.f)
	//{
	//	float Fps = CEngine::GetInst()->GetFPS();
	//	m_TimeTest = 0;
	//}

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

void CPlayer2D::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CPlayer2D::Load(FILE* File)
{
	CGameObject::Load(File);
}

void CPlayer2D::MoveUp()
{
	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_Y) * 300.f * g_DeltaTime);
	m_Sprite->SetTextureReverse(true);
	m_SpriteChild->SetTextureReverse(true);
	m_Sprite->GetAnimation()->SetCurrentAnimation("KnightDashTest");
}

void CPlayer2D::MoveDown()
{
	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_Y) * -300.f * g_DeltaTime);
	m_Sprite->SetTextureReverse(false);
	m_SpriteChild->SetTextureReverse(false);
	m_Sprite->GetAnimation()->SetCurrentAnimation("KnightDashTest");
}

void CPlayer2D::Rotation()
{
	m_Body->AddWorldRotationZ(360.f * g_DeltaTime);
	//m_Sprite->GetAnimation()->SetCurrentAnimation("Loading");
	m_Sprite->SetRelativeScale(269.f * 0.5f, 475 * 0.5f);
}

void CPlayer2D::RotationInv()
{
	m_Body->AddWorldRotationZ(-360.f * g_DeltaTime);
}

void CPlayer2D::LeftMove()
{
	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * -300.f * g_DeltaTime);
}

void CPlayer2D::RightMove()
{
	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * 300.f * g_DeltaTime);	
}

void CPlayer2D::Jump()
{
	m_GravityAgent->Jump();
}

void CPlayer2D::Fire()
{
	//CMyBullet* Bullet = m_Scene->CreateObject<CMyBullet>("MyBullet");
	//Bullet->SetWorldPosition(GetWorldPos());
	//Bullet->SetWorldRotation(GetWorldRot());

	//m_Sprite->GetAnimation()->SetCurrentAnimation("Idle");
	//m_Sprite->SetRelativeScale(259.f * 0.5f, 436 * 0.5f);

	//CMyBullet* Bullet2 = m_Scene->CreateObject<CMyBullet>("MyBullet2");
	//Bullet2->SetWorldPosition(m_Sprite->GetWorldPos());
	////Bullet2->AddWorldRotationZ(15.f * g_DeltaTime);
	//Bullet2->SetWorldRotationZ(m_Sprite->GetWorldRot().z+15.f);

	//CMyBullet* Bullet3 = m_Scene->CreateObject<CMyBullet>("MyBullet3");
	//Bullet3->SetWorldPosition(m_Sprite->GetWorldPos());
	//Bullet3->SetWorldRotationZ(m_Sprite->GetWorldRot().z - 15.f);
	
	//CMyBullet* Bullet = m_Scene->CreateObject<CMyBullet>("MyBullet");

	//Bullet->SetWorldPosition(GetWorldPos());
	//Bullet->SetWorldRotation(GetWorldRot());
	//Bullet->SetCollisionProfileName("PlayerAttack");

	//Bullet2->SetCollisionProfileName("PlayerAttack");
	//Bullet3->SetCollisionProfileName("PlayerAttack");
	m_GravityAgent->SetPhysicsSimulate(true);
	m_GravityAgent->SetJumpVelocity(60.f);
}

void CPlayer2D::CollisionBegin(const CollisionResult& Result)
{
	OutputDebugStringA(Result.Src->GetName().c_str());
	OutputDebugStringA(Result.Dest->GetName().c_str());
	
	float a = Result.HitPoint.x;
	float b = Result.HitPoint.y;
	float c = Result.HitPoint.z;

	//this->AddWorldPositionY(1.f);
	m_GravityAgent->SetPhysicsSimulate(false);
}
