
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
	m_Body = (CColliderBox2D*)FindComponent("Body"); //루트
	m_Sprite = (CSpriteComponent*)FindComponent("Sprite");

	m_GravityAgent = (CGravityAgent*)FindComponent("GravityAgent");
	m_Camera = (CCameraComponent*)FindComponent("Camera");
	m_Arm = (CTargetArm*)FindComponent("Arm");

	m_DashSprite = (CSpriteComponent*)FindComponent("DashSprite");
	m_DoubleJumpSprite = (CSpriteComponent*)FindComponent("DoubleJumpSprite");
	m_AttackSprite = (CSpriteComponent*)FindComponent("AttackSprite");
	m_FireSprite = (CSpriteComponent*)FindComponent("FireSprite");

	m_Anim = CResourceManager::GetInst()->FindAnimation2D("TheKnight");

	//추후 강화모션 작업
}

CPlayer2D::~CPlayer2D()
{
}

void CPlayer2D::Start()
{
	CGameObject::Start();

	if (m_Scene)
		m_Scene->GetCameraManager()->SetCurrentCamera(m_Camera);

	SetInputKey(); //키셋팅
	SetAnimation(); // 애니메이션 세팅
	m_Body->SetCollisionCallback(ECollision_Result::Collision, 
		this, &CPlayer2D::CollisionBegin); //콜라이더 세팅
}

bool CPlayer2D::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Sprite = CreateComponent<CSpriteComponent>("Sprite");

	m_Camera = CreateComponent<CCameraComponent>("Camera");
	m_Arm = CreateComponent<CTargetArm>("Arm");
	
	m_DashSprite = CreateComponent<CSpriteComponent>("DashSprite");
	m_DoubleJumpSprite = CreateComponent<CSpriteComponent>("DoubleJumpSprite");
	m_AttackSprite = CreateComponent<CSpriteComponent>("AttackSprite");
	m_FireSprite = CreateComponent<CSpriteComponent>("FireSprite");
	
	m_GravityAgent = CreateComponent<CGravityAgent>("GravityAgent");

	m_Sprite->SetAnimationFile("TheKnight");
	m_Anim = m_Sprite->GetAnimation();
	m_Anim->SetCurrentAnimation("Idle");

	//========================계층구조
	SetRootComponent(m_Body);
		m_Body->AddChild(m_Sprite);
			m_Sprite->AddChild(m_DashSprite);
			m_Sprite->AddChild(m_DoubleJumpSprite);
			m_Sprite->AddChild(m_AttackSprite);
			m_Sprite->AddChild(m_FireSprite);
			m_Sprite->AddChild(m_Arm);
				m_Arm->AddChild(m_Camera);
	

	//Body Collider
	m_Body->SetWorldPosition(200.f, 500.f);
	m_Body->SetBoxSize(50.f, 98.f);
	m_Body->SetCollisionProfile("Player");

	//플레이어 Sprite
	m_Sprite->SetRenderLayerName("Player");
	m_Sprite->SetPivot(0.5f, 0.4f);
	//m_Sprite->GetMaterial(0)->SetRenderState("DepthDisable");
	
	float x = 349.f * g_SCALE;
	float y = 186.f * g_SCALE;
	m_Sprite->SetWorldScale(x, y);
	
	m_Sprite->SetTextureReverse(true);


	//================이펙트 세팅
	m_DashSprite->SetPivot(0.5f, 0.4f);

	float DashX = 401.f * g_SCALE;
	float DashY = 217.f * g_SCALE;

	m_DashSprite->SetWorldScale(DashX, DashY);
	m_DashSprite->SetAnimationFile("TheKnight");
	m_DashSprite->SetRelativePosition(0, -20.f);
	m_DashSprite->GetMaterial(0)->SetRenderState("DepthDisable");
	m_DashSprite->SetTextureReverse(false);	
	m_DashSprite->SetRenderLayerName("BackEffect");
	m_DashSprite->SetEnable(false);
	

	m_DoubleJumpSprite->SetPivot(0.5f, 0.4f);

	float JumpX = 383.f * g_SCALE;
	float JumpY = 356.f * g_SCALE;

	m_DoubleJumpSprite->SetWorldScale(JumpX, JumpY);
	m_DoubleJumpSprite->SetAnimationFile("TheKnight");
	m_DoubleJumpSprite->GetMaterial(0)->SetRenderState("DepthDisable");
	m_DoubleJumpSprite->SetTextureReverse(true);
	m_DoubleJumpSprite->SetEnable(false);
	//m_EffectSprite->SetRenderLayerName("Effect");

	m_AttackSprite->SetPivot(0.5f, 0.4f);

	float AttackX = 349.f * g_SCALE;
	float AttackY = 186.f * g_SCALE;

	m_AttackSprite->SetWorldScale(AttackX, AttackY);
	m_AttackSprite->SetAnimationFile("TheKnight");
	m_AttackSprite->SetRenderLayerName("Effect");
	m_AttackSprite->SetTextureReverse(true);
	//m_AttackSprite->SetEnable(false);

	m_FireSprite->SetPivot(0.5f, 0.4f);

	float FireX = 306.f * g_SCALE;
	float FireY = 289.f * g_SCALE;

	m_FireSprite->SetWorldScale(FireX, FireY);
	m_FireSprite->SetAnimationFile("TheKnight");
	m_FireSprite->SetRelativePosition(0, 0.f);
	m_FireSprite->SetRenderLayerName("Effect");
	m_FireSprite->SetTextureReverse(false);
	//m_FireSprite->SetEnable(false);


	//Arm
	Resolution RS = CDevice::GetInst()->GetResolution();

	float Width = (float)RS.Width / 2.f;
	float Height = (float)RS.Height / 2.f;

	m_Arm->SetTargetOffset(Vector3(-Width, -Height, 0.f));


	//중력 에이전트
	m_GravityAgent->SetPhysicsSimulate(false);
	m_GravityAgent->SetJumpVelocity(1.8f);
	m_GravityAgent->SetGravityAccel(1.f);
	m_GravityAgent->SetSideWallCheck(true);



	//m_Sprite->SetInheritRotZ(true);
	//CMaterial* Material = m_Sprite->GetMaterial(0);
	//Material->SetOpacity(0.5f);
	//Material->SetRenderState("DepthDisable"); //깊이 무시?
	//m_SpriteChild->SetInheritRotZ(true);

	//============================스킬 쿨 세팅
	SkillCoolDownInfo Dash = {};
	Dash.CoolDown = 0.5f;
	m_vecCoolDown.push_back(Dash);

	SkillCoolDownInfo Attack = {};
	Attack.CoolDown = 0.3f;
	m_vecCoolDown.push_back(Attack);

	SkillCoolDownInfo DoubleAttack = {};
	Attack.CoolDown = 0.5f;
	m_vecCoolDown.push_back(DoubleAttack);

	SkillCoolDownInfo Fire = {};
	Fire.CoolDown = 0.5f;
	m_vecCoolDown.push_back(Fire);

	return true;
}

void CPlayer2D::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	CheckDir(); //방향
	//쿨타임 돌리기
	size_t	Size = m_vecCoolDown.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecCoolDown[i].CoolDownEnable)
		{
			m_vecCoolDown[i].CoolDown -= DeltaTime;

			if (m_vecCoolDown[i].CoolDown <= 0.f)
				m_vecCoolDown[i].CoolDownEnable = false;
		}
	}

	switch (m_CurState)
	{
	case CPlayer2D::EPlayerStates::Idle:
		m_DashCount = 0;
		break;
	case CPlayer2D::EPlayerStates::Walk:
	{
		m_DashCount = 0;
		Vector3 Pos = m_Body->GetWorldPos();
		float MoveX = Pos.x - m_PrevPos.x;

		if (MoveX == 0) //움직임이 없을 시
			m_CurState = EPlayerStates::Idle;
	}
	break;
	case CPlayer2D::EPlayerStates::Jump:
		break;
	case CPlayer2D::EPlayerStates::DoubleJump:
		break;
	case CPlayer2D::EPlayerStates::Fall:
	{
		bool jump = m_GravityAgent->GetJump();

		if (!jump) //점프가 끝나면(땅에 닿는 순간)
		{
			m_CurState = EPlayerStates::LandOn;
			m_Jumping = 0;
			m_DashCount = 0;
		}
	}
	break;
	case CPlayer2D::EPlayerStates::LandOn:
		break;

	case CPlayer2D::EPlayerStates::Dash:
		m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * m_Dir * 1500.f * g_DeltaTime);
		break;
	case CPlayer2D::EPlayerStates::Slash:
		break;
	case CPlayer2D::EPlayerStates::DoubleSlash:
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
		break;
	default:

		break;
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
	m_Sprite->SetAnimationFile("TheKnight");
	CGameObject::Load(File);
}

void CPlayer2D::MoveUp()
{
	//CInput::GetInst()->
}

void CPlayer2D::MoveDown()
{
}

void CPlayer2D::Move()
{
	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * (float)m_Dir * 500.f * g_DeltaTime);

	if (m_CurState != EPlayerStates::Jump &&
		m_CurState != EPlayerStates::Fall &&
		m_CurState != EPlayerStates::DoubleJump &&
		m_CurState != EPlayerStates::WallSlide &&
		m_CurState != EPlayerStates::Slash &&
		m_CurState != EPlayerStates::DoubleSlash)
		m_CurState = EPlayerStates::Walk;
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
	if (!m_KeyLock)
	{
		SetReverse(false);

		Move();
	}
}

void CPlayer2D::RightMove()
{
	if (!m_KeyLock)
	{
		SetReverse(true);

		Move();
	}
}

void CPlayer2D::Jump()
{
	OutputDebugStringA("점프");
	if (!m_KeyLock)
	{
		if (m_Jumping == 1)
		{
			m_GravityAgent->Jump();
			m_CurState = EPlayerStates::DoubleJump;
			m_Jumping++;

			//더블점프 이펙트
			m_DoubleJumpSprite->SetEnable(true);
			m_DoubleJumpSprite->GetAnimation()->SetCurrentAnimation("007DoubleJumpEffect");
			


			//m_EffectSprite->SetCurrentAnimation("006DoubleJump");
		}
		else if (m_Jumping == 0)
		{
			m_GravityAgent->Jump();
			m_CurState = EPlayerStates::Jump;
			m_Jumping++;
		}
	}

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
	m_CurState = EPlayerStates::FireBall;
	//CMyBullet* Bullet = m_Scene->CreateObject<CMyBullet>("MyBullet");
	//Bullet->SetWorldPosition(GetWorldPos());
	//Bullet->SetWorldRotation(GetWorldRot());

	//m_Sprite->GetAnimation()->SetCurrentAnimation("Idle");
	//m_Sprite->SetRelativeScale(259.f * 0.5f, 436 * 0.5f);

	CMyBullet* Bullet2 = m_Scene->CreateObject<CMyBullet>("MyBullet2");
	Bullet2->SetWorldPosition(m_Sprite->GetWorldPos());
	//Bullet2->AddWorldRotationZ(m_Angle * g_DeltaTime);
	Bullet2->SetWorldRotationZ(m_Angle);

	//CMyBullet* Bullet3 = m_Scene->CreateObject<CMyBullet>("MyBullet3");
	//Bullet3->SetWorldPosition(m_Sprite->GetWorldPos());
	//Bullet3->SetWorldRotationZ(m_Sprite->GetWorldRot().z - 15.f);

	//CMyBullet* Bullet = m_Scene->CreateObject<CMyBullet>("MyBullet");

	//Bullet->SetWorldPosition(GetWorldPos());
	//Bullet->SetWorldRotation(GetWorldRot());
	//Bullet->SetCollisionProfileName("PlayerAttack");

	Bullet2->SetCollisionProfileName("PlayerAttack");
	//Bullet3->SetCollisionProfileName("PlayerAttack");

	m_FireSprite->GetAnimation()->SetCurrentAnimation("029FireEffect");

}

void CPlayer2D::FireEnd()
{
	m_FireSprite->SetEnable(false);
}

void CPlayer2D::Dash()
{
	OutputDebugStringA("대시 시작");
	
	//대시상태가이거나 대시카운트를 이미 사용하였으면 무시
	if (!(m_CurState == EPlayerStates::Dash) && m_DashCount == 0)
	{
		if (m_vecCoolDown[0].CoolDownEnable)
			return;

		
		//쿨타임 0.5초
		m_vecCoolDown[0].CoolDownEnable = true;
		m_vecCoolDown[0].CoolDown = 0.5f;

		float x = m_Body->GetWorldPos().x;
		//m_DashEndPos = x + m_Dir * 500.f;
		m_CurState = EPlayerStates::Dash;
		m_GravityAgent->SetPhysicsSimulate(false);
		m_KeyLock = true;
		m_DashCount++;

		//대시 이펙트
		m_DashSprite->GetAnimation()->SetCurrentAnimation("004DashEffect");
		m_DashSprite->SetEnable(true);
	}
}

void CPlayer2D::DashEnd()
{
	OutputDebugStringA("대시 끝");

	m_KeyLock = false;
	m_GravityAgent->SetPhysicsSimulate(true);
	//현재 Y좌표를 중력 에이전트에 보냄
	//m_GravityAgent->SetJumpVelocity(-1.f);
	m_GravityAgent->SetFallTime(0.6f);

	if (bool jump = m_GravityAgent->GetJump())
	{
		m_CurState = EPlayerStates::Fall;
	}
	else
	{
		m_CurState = EPlayerStates::Idle;
	}
	m_DashEndPos = 0;
}

void CPlayer2D::Attack()
{
	if (m_vecCoolDown[1].CoolDownEnable || m_KeyLock)
		return;

	//쿨타임 0.2초
	m_vecCoolDown[1].CoolDownEnable = true;
	m_vecCoolDown[1].CoolDown = 0.3f;

	//bool jump = m_GravityAgent->GetJump();
	

	if (m_vecCoolDown[2].CoolDown > 0.f)
	{
		OutputDebugStringA("더블");
		m_CurState = EPlayerStates::DoubleSlash;
		m_AttackSprite->GetAnimation()->SetCurrentAnimation("011SlashEffect");
	}
	else
	{
		OutputDebugStringA("공격");
		m_CurState = EPlayerStates::Slash;
		m_vecCoolDown[2].CoolDown = 0.5f;
		m_vecCoolDown[2].CoolDownEnable = true;
		m_AttackSprite->GetAnimation()->SetCurrentAnimation("012SlashEffectAlt");
	}

	//이펙트
	m_AttackSprite->SetEnable(true);
}

void CPlayer2D::AttackEnd()
{
	if (m_Jumping)
		m_CurState = EPlayerStates::Fall;
	else
		m_CurState = EPlayerStates::Idle;
}

void CPlayer2D::Charge()
{

}

void CPlayer2D::DashEffectEnd()
{
	m_DashSprite->SetEnable(false);
}

void CPlayer2D::DoubleJumpEffectEnd()
{
	m_DoubleJumpSprite->SetEnable(false);
}

void CPlayer2D::AttackEffectEnd()
{
	m_AttackSprite->SetEnable(false);
}

void CPlayer2D::FireEffectEnd()
{
	m_FireSprite->SetEnable(false);
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


	//CInput::GetInst()->AddBindFunction<CPlayer2D>("Up", Input_Type::Down, this,
	//	&CPlayer2D::Fire, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Left", Input_Type::Push, this,
		&CPlayer2D::LeftMove, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Right", Input_Type::Push, this,
		&CPlayer2D::RightMove, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Z", Input_Type::Down, this,
		&CPlayer2D::Jump, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("X", Input_Type::Down, this,
		&CPlayer2D::Attack, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("C", Input_Type::Down, this,
		&CPlayer2D::Dash, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("V", Input_Type::Down, this,
		&CPlayer2D::Fire, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Space", Input_Type::Push, this,
		&CPlayer2D::Charge, m_Scene);


}

void CPlayer2D::SetAnimation()
{
	m_Anim->SetPlayScale("005-0Jump", 1.f);
	m_Anim->SetCurrentEndFunction("005-0Jump", this, &CPlayer2D::JumpEnd);

	m_Anim->SetPlayScale("005-1AirBone", 3.f);

	m_Anim->SetPlayScale("008LandOn", 5.f);
	m_Anim->SetCurrentEndFunction("008LandOn", this, &CPlayer2D::LandOff);

	m_Anim->SetPlayScale("006DoubleJump", 2.f);
	m_Anim->SetCurrentEndFunction("006DoubleJump", this, &CPlayer2D::JumpEnd);
	

	m_Anim->SetPlayScale("003Dash", 2.f);

	m_Anim->AddCurrentNotify("003Dash", "003Dash", 6, this, &CPlayer2D::DashEnd);

	m_Anim->AddCurrentNotify("009Slash", "009Slash", 6, this, &CPlayer2D::AttackEnd);
	m_Anim->AddCurrentNotify("010SlashAlt", "010SlashAlt", 6, this, &CPlayer2D::AttackEnd);
	//m_Anim->SetCurrentEndFunction("009Slash", this, &CPlayer2D::AttackEnd);

	m_Anim->SetPlayScale("017FireBall", 3.f);

	//이펙트

	
	//m_FireSprite; //앞
	

	m_DoubleJumpSprite->GetAnimation()->SetPlayScale("007DoubleJumpEffect", 2.f);
	m_DoubleJumpSprite->GetAnimation()->AddCurrentNotify("007DoubleJumpEffect", "007DoubleJumpEffect", 5, this, &CPlayer2D::DoubleJumpEffectEnd);

	m_DashSprite->GetAnimation()->SetPlayScale("004DashEffect", 4.f);
	m_DashSprite->GetAnimation()->SetCurrentEndFunction("004DashEffect", this, &CPlayer2D::DashEffectEnd);

	m_AttackSprite->GetAnimation()->AddCurrentNotify("011SlashEffect", "011SlashEffect", 6, this, &CPlayer2D::AttackEffectEnd);
	m_AttackSprite->GetAnimation()->AddCurrentNotify("012SlashEffectAlt", "012SlashEffectAlt", 6, this, &CPlayer2D::AttackEffectEnd);

	m_AttackSprite->GetAnimation()->SetPlayScale("011SlashEffect", 5.f);
	m_AttackSprite->GetAnimation()->SetPlayScale("012SlashEffectAlt", 5.f);

	m_FireSprite->GetAnimation()->SetCurrentEndFunction("029FireEffect", this, &CPlayer2D::FireEffectEnd);
	m_FireSprite->GetAnimation()->SetPlayScale("029FireEffect", 3.f);
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
		m_Anim->SetCurrentAnimation("010SlashAlt");
		break;
	case CPlayer2D::EPlayerStates::DoubleSlash:
		m_Anim->SetCurrentAnimation("009Slash");
		break;
	case CPlayer2D::EPlayerStates::UpSlash:
		m_Anim->SetCurrentAnimation("013UpSlash");
		break;
	case CPlayer2D::EPlayerStates::DownSlash:
		m_Anim->SetCurrentAnimation("015DownSlash");
		break;
	case CPlayer2D::EPlayerStates::FireBall:
		m_Anim->SetCurrentAnimation("017FireBall");
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

//방향 체크(Update)
void CPlayer2D::CheckDir()
{
	//true 오른쪽 false 왼쪽
	bool Check = m_Sprite->GetTextureReverse();
	
	m_Dir = Check ? 1.f : -1.f;
	m_Angle = Check ? 0.f : 180.f;

	m_DashSprite->SetRelativePositionX(-120.f * m_Dir);	
}

void CPlayer2D::SetReverse(bool Enable)
{
	m_Sprite->SetTextureReverse(Enable);
	m_DashSprite->SetTextureReverse(!Enable);
	m_DoubleJumpSprite->SetTextureReverse(Enable);
	m_AttackSprite->SetTextureReverse(Enable);
	m_FireSprite->SetTextureReverse(Enable);
}
