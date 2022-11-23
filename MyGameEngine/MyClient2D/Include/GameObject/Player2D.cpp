
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

#include "Scene\SceneManager.h"
#include "PathManager.h"

#include "Engine.h"


CPlayer2D::CPlayer2D()
{
	SetTypeID<CPlayer2D>();

	m_ObjectTypeName = "Player2D";
}

CPlayer2D::CPlayer2D(const CPlayer2D& Obj) :
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_Sprite = (CSpriteComponent*)FindComponent("sprite");
	m_SpriteChild = (CSpriteComponent*)FindComponent("spriteChild");
	
	m_GravityAgent = (CGravityAgent*)FindComponent("GravityAgent");
	m_Camera = (CCameraComponent*)FindComponent("Camera");
	m_Arm = (CTargetArm*)FindComponent("Arm");
	m_Anim = CResourceManager::GetInst()->FindAnimation2D("TheKnight");
	//m_RightChild = (CSceneComponent*)FindComponent("RightChild");
	//*애니메이션 지금은 그냥 가져다 쓰는데 몬스터 같은거 만들때는 복사해서 사용하기
	
}

CPlayer2D::~CPlayer2D()
{
}

void CPlayer2D::Start()
{
	CGameObject::Start();

	if (m_Scene)
		m_Scene->GetCameraManager()->SetCurrentCamera(m_Camera);


	SetInputKey();
	SetAnimation();
	//CInput::GetInst()->SetLockKey(true);
	m_Body->SetCollisionCallback(ECollision_Result::Collision, this, &CPlayer2D::CollisionBegin);


}

bool CPlayer2D::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("sprite");
	//m_RightChild = CreateComponent<CSceneComponent>("RightChild");
	m_SpriteChild = CreateComponent<CSpriteComponent>("spriteChild");
	m_Camera = CreateComponent<CCameraComponent>("Camera");
	m_Arm = CreateComponent<CTargetArm>("Arm");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_GravityAgent = CreateComponent<CGravityAgent>("GravityAgent");

	m_Sprite->SetAnimationFile("TheKnight");
	
	m_Anim = m_Sprite->GetAnimation();
	m_Anim->SetCurrentAnimation("Idle");
	
	SetRootComponent(m_Body);

	m_Body->SetWorldPosition(200.f, 500.f);

	m_Body->SetBoxSize(50.f, 98.f);
	m_Body->SetCollisionProfile("Player");

	m_Body->AddChild(m_Sprite);
	//m_Sprite->AddChild(m_RightChild);

	//m_Sprite->GetMaterial(0)->SetBaseColorUnsignedChar(255, 0, 0, 255); //컬러

	m_Sprite->AddChild(m_Arm);
	m_Arm->AddChild(m_Camera);

	Resolution RS = CDevice::GetInst()->GetResolution();

	float Width = (float)RS.Width / 2.f;
	float Height = (float)RS.Height / 2.f;

	m_Arm->SetTargetOffset(Vector3(-Width, -Height, 0.f));

	//m_RightChild->AddChild(m_SpriteChild);

	m_Sprite->SetPivot(0.5f, 0.4f);
	float x = 349.f * g_SCALE;
	float y = 186.f * g_SCALE;

	m_Sprite->SetWorldScale(x, y);



	//m_Sprite->SetInheritRotZ(true);

	//CMaterial* Material = m_Sprite->GetMaterial(0);
	//Material->SetOpacity(0.5f);
	//Material->SetRenderState("DepthDisable");

	//m_RightChild->SetRelativePosition(0.f, 0.f);
	//m_RightChild->SetInheritRotZ(true);

	m_SpriteChild->SetRelativeScale(50.f, 50.f);
	//m_SpriteChild->SetPivot(0.5f, 0.4f);
	m_SpriteChild->SetInheritRotZ(true);

	//m_SpriteChild->SetAnimationFile("MainSystemUI");
	//m_SpriteChild->GetMaterial(0)->SetBaseColorUnsignedChar(250, 250, 250, 255);
	//m_SpriteChild->SetRelativeScale(60.f, 60.f);
	// 
	//CAnimation2D* Anims = m_SpriteChild->GetAnimation();
	//Anims->SetCurrentAnimation("Flame");


	//
	//Anim->AddAnimation("Idle", "AtlasTest5");
	//Anim->AddAnimation("Run", "FrameGrimTest3");
	//
	/*Anim->SetLoop("Idle", true);
	Anim->SetLoop("Run", true);*/
	
	//Anim->SetCurrentAnimation("AtlasTest3");
	//Anim->SetLoop("AtlasTest3", true);
	m_Sprite->SetTextureReverse(true);

	//Anim->TextureReverse(true);
	//Anim->SetLoop("Flame", true);

	m_GravityAgent->SetPhysicsSimulate(false);
	m_GravityAgent->SetJumpVelocity(1.8f);
	m_GravityAgent->SetGravityAccel(1.f);
	//m_GravityAgent->SetGravityAccel(0.5f);
	m_GravityAgent->SetSideWallCheck(true);

	m_TimeTest = 0;
	return true;
}

void CPlayer2D::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	//스위치로 개선해보면 좋을듯
	//점프
	if (m_Jumping)
	{
		bool jump = m_GravityAgent->GetJump();
		//if (m_GravityAgent->GetFalling())
			//m_CurState = EPlayerStates::Fall;
		//if (m_GravityAgent->GetSideWallCheck())
		//{
		//	m_CurState = EPlayerStates::WallSlide;
		//}
		
		
		if (!jump) //점프가 끝나면
		{
			m_CurState = EPlayerStates::LandOn;
			m_Jumping = false;
		}			
	}
	//이동
	else 
	{ 
		if (!(m_CurState == EPlayerStates::LandOn))
		{
			Vector3 Pos = m_Body->GetWorldPos();
			float MoveX = Pos.x - m_PrevPos.x;

			if (MoveX == 0)
				m_CurState = EPlayerStates::Idle;
		}		
	}

	SetCurAnim(m_CurState);
}

void CPlayer2D::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
	m_PrevPos = m_Body->GetWorldPos();
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
	m_Sprite->SetAnimationFile("AnimationTest");
	CGameObject::Load(File);
}

void CPlayer2D::MoveUp()
{
	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_Y) * 300.f * g_DeltaTime);
	m_Sprite->SetTextureReverse(true);
	m_SpriteChild->SetTextureReverse(true);
	//m_Sprite->GetAnimation()->SetCurrentAnimation("KnightDashTest");
}

void CPlayer2D::MoveDown()
{
	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_Y) * -300.f * g_DeltaTime);
	m_Sprite->SetTextureReverse(false);
	m_SpriteChild->SetTextureReverse(false);
	//m_Sprite->GetAnimation()->SetCurrentAnimation("KnightDashTest");
}

void CPlayer2D::Rotation()
{
	//m_Body->AddWorldRotationZ(360.f * g_DeltaTime);
	//m_Sprite->GetAnimation()->SetCurrentAnimation("Loading");
	//m_Sprite->SetRelativeScale(269.f * 0.5f, 475 * 0.5f);
}

void CPlayer2D::RotationInv()
{
	//m_Body->AddWorldRotationZ(-360.f * g_DeltaTime);
}

void CPlayer2D::LeftMove()
{
	//m_Body->AddWorldRotationZ(360.f * g_DeltaTime);
	//Vector3 v = m_Body->GetWorldAxis(AXIS::AXIS_X);
	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * -500.f * g_DeltaTime);
	
	m_Sprite->SetTextureReverse(false);
	m_SpriteChild->SetTextureReverse(false);

	if (m_CurState != EPlayerStates::Jump &&
		m_CurState != EPlayerStates::Fall &&
		m_CurState != EPlayerStates::DoubleJump &&
		m_CurState != EPlayerStates::WallSlide)
		m_CurState = EPlayerStates::Walk;

}

void CPlayer2D::RightMove()
{
	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * +500.f * g_DeltaTime);	

	m_Sprite->SetTextureReverse(true);
	m_SpriteChild->SetTextureReverse(true);

	if (m_CurState != EPlayerStates::Jump &&
		m_CurState != EPlayerStates::Fall &&
		m_CurState != EPlayerStates::DoubleJump &&
		m_CurState != EPlayerStates::WallSlide)
		m_CurState = EPlayerStates::Walk;
}

void CPlayer2D::Jump()
{
	if (m_Jumping)
	{	
		m_GravityAgent->Jump();		
		//m_Anim->SetCurrentAnimation("006DoubleJump");
		m_CurState = EPlayerStates::DoubleJump;
	}
	else
	{
		//m_CurState = EPlayerStates::DoubleJump;
		m_GravityAgent->Jump();
		m_CurState = EPlayerStates::Jump;
		m_Jumping = true;
	}
	//CInput::GetInst()->SetLockKey(true);

}

void CPlayer2D::JumpEnd()
{
	OutputDebugStringA("추락중");
	m_CurState = EPlayerStates::Fall;
}

void CPlayer2D::LandOff()
{
	OutputDebugStringA("점프 끝");
	m_CurState = EPlayerStates::Idle;
}

void CPlayer2D::Fire()
{
	m_GravityAgent->SetPhysicsSimulate(true);
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
	
	//m_GravityAgent->SetJumpVelocity(200.f);
}

void CPlayer2D::Dash()
{
	m_GravityAgent->SetPhysicsSimulate(true);
}

void CPlayer2D::CollisionBegin(const CollisionResult& Result)
{
	//OutputDebugStringA(Result.Src->GetName().c_str());
	//OutputDebugStringA(Result.Dest->GetName().c_str());
	//
	//float a = Result.HitPoint.x;
	//float b = Result.HitPoint.y;
	//float c = Result.HitPoint.z;

	//CSceneManager::GetInst()->CreateNextScene();

	//char Name[256] = {};
	//const PathInfo* Path = CPathManager::GetInst()->FindPath(SCENE_PATH);
	//strcat_s(Name, Path->PathMultibyte);
	//strcat_s(Name, "HollowScene6.scn");
	//CScene* NextScene = CSceneManager::GetInst()->GetNextScene();
	//NextScene->Load(Name);

	//CSceneManager::GetInst()->CreateNextScene(true);
	//CSceneManager::GetInst()->ChangeNextScene();

	//Result.Dest.
	
	
	
	//m_GravityAgent->m_FallTime = 0.f;
	//m_GravityAgent->m_JumpCount = 0;
	//m_GravityAgent->m_Ground = true;
	//m_GravityAgent->m_Jump = false;
	//m_GravityAgent->SetPhysicsSimulate(false);

	//this->AddWorldPositionY(100.f);
}

void CPlayer2D::SetInputKey()
{
	//CInput::GetInst()->AddBindFunction<CPlayer2D>("Rotation", Input_Type::Push,
	//	this, &CPlayer2D::RotationInv, m_Scene);
	//CInput::GetInst()->AddBindFunction<CPlayer2D>("RotationInv", Input_Type::Push,
	//	this, &CPlayer2D::Rotation, m_Scene);

	//CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveUp", Input_Type::Push,
	//	this, &CPlayer2D::MoveUp, m_Scene);
	//CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveDown", Input_Type::Push,
	//	this, &CPlayer2D::MoveDown, m_Scene);


	CInput::GetInst()->AddBindFunction<CPlayer2D>("Up", Input_Type::Down, this,
		&CPlayer2D::Fire, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Left", Input_Type::Push, this,
		&CPlayer2D::LeftMove, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Right", Input_Type::Push, this,
		&CPlayer2D::RightMove, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Space", Input_Type::Down, this,
		&CPlayer2D::Jump, m_Scene);

	//추가
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Shift", Input_Type::Down, this,
		&CPlayer2D::Fire, m_Scene);
}

void CPlayer2D::SetAnimation()
{
	m_Anim->SetPlayScale("005-0Jump", 1.f);
	m_Anim->SetCurrentEndFunction("005-0Jump", this, &CPlayer2D::JumpEnd);

	m_Anim->SetPlayScale("005-1AirBone", 3.f);

	m_Anim->SetPlayScale("008LandOn", 5.f);
	m_Anim->SetCurrentEndFunction("008LandOn", this, &CPlayer2D::LandOff);

	m_Anim->SetPlayScale("006DoubleJump", 1.f);
	m_Anim->SetCurrentEndFunction("006DoubleJump", this, &CPlayer2D::JumpEnd);

}

void CPlayer2D::SetCurAnim(EPlayerStates State)
{
	if (m_PrevState == State)
		return;

	switch (State)
	{
	case CPlayer2D::EPlayerStates::Idle:
		m_Anim->SetCurrentAnimation("001Idle");
		break;
	case CPlayer2D::EPlayerStates::Walk:
		m_Anim->SetCurrentAnimation("002Walk");
		break;
	case CPlayer2D::EPlayerStates::Jump:
			m_Anim->SetCurrentAnimation("005-0Jump");
		break;
	case CPlayer2D::EPlayerStates::DoubleJump:
		m_Anim->SetCurrentAnimation("006DoubleJump");
		break;
	case CPlayer2D::EPlayerStates::Fall:
		m_Anim->SetCurrentAnimation("005-1AirBone");
		break;
	case CPlayer2D::EPlayerStates::LandOn:
		m_Anim->SetCurrentAnimation("008LandOn");
		break;
	case CPlayer2D::EPlayerStates::Dash:
		m_Anim->SetCurrentAnimation("003Dash");
		break;
	case CPlayer2D::EPlayerStates::Slash:
		break;
	case CPlayer2D::EPlayerStates::UpSlash:
		break;
	case CPlayer2D::EPlayerStates::DownSlash:
		break;
	case CPlayer2D::EPlayerStates::FireBall:
		break;
	case CPlayer2D::EPlayerStates::Charge:
		break;
	case CPlayer2D::EPlayerStates::Enter:
		break;
	case CPlayer2D::EPlayerStates::Stun:
		break;
	case CPlayer2D::EPlayerStates::Death:
		break;
	case CPlayer2D::EPlayerStates::Prostrate:
		break;
	case CPlayer2D::EPlayerStates::ProstrateRise:
		break;
	case CPlayer2D::EPlayerStates::WallSlide:
		m_Anim->SetCurrentAnimation("021WallSlide");
		break;
	default:
		m_Anim->SetCurrentAnimation("001Idle");
		break;		
	}

	m_PrevState = State;
}

void CPlayer2D::SetIdle()
{
	m_Anim->SetCurrentAnimation("001Idle");
}
