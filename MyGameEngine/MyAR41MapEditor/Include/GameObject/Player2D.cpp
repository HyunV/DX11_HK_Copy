
#include "Player2D.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderSphere2D.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Device.h"
#include "MyBullet.h"
#include "PlayerAttack.h"
#include "Effect.h"
#include "Door.h"
#include "Resource/Material/Material.h"
#include "Animation/Animation2D.h"
#include "../UI/PlayerHUD.h"

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
	m_UpAttackSprite = (CSpriteComponent*)FindComponent("UpAttackSprite");
	m_DownAttackSprite = (CSpriteComponent*)FindComponent("DownAttackSprite");
	m_FireSprite = (CSpriteComponent*)FindComponent("FireSprite");
	m_ChargeSprite = (CSpriteComponent*)FindComponent("ChargeSprite");

	m_Anim = CResourceManager::GetInst()->FindAnimation2D("TheKnight");
}

CPlayer2D::~CPlayer2D()
{
	m_Anim->ClearAllNotify();
}

void CPlayer2D::SetProstrate()
{
	m_Prostrate = true;
	m_CurState = EPlayerStates::Prostrate;
}

void CPlayer2D::CheckProstrate()
{
	if (m_Prostrate)
	{
		m_KeyLock = true;
		m_CurState = EPlayerStates::ProstrateRise;
	}
	return;
}

void CPlayer2D::SetInputKey()
{
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Q", Input_Type::Down,
		this, &CPlayer2D::Q, m_Scene);


	CInput::GetInst()->AddBindFunction<CPlayer2D>("Up", Input_Type::Push, this,
		&CPlayer2D::UpKey, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Down", Input_Type::Push, this,
		&CPlayer2D::DownKey, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Up", Input_Type::Up, this,
		&CPlayer2D::UpKeyUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Down", Input_Type::Up, this,
		&CPlayer2D::DownKeyUp, m_Scene);


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

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Space", Input_Type::Down, this,
		&CPlayer2D::Fire, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("V", Input_Type::Push, this,
		&CPlayer2D::Charge, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("V", Input_Type::Up, this,
		&CPlayer2D::SetNextState, m_Scene);
}

void CPlayer2D::SetAnimation()
{
	m_Anim->SetPlayScale("005-0Jump", 2.f);
	m_Anim->SetCurrentEndFunction("005-0Jump", this, &CPlayer2D::SetNextState);

	m_Anim->SetPlayScale("005-1AirBone", 3.f);

	m_Anim->SetPlayScale("008LandOn", 5.f);
	m_Anim->SetCurrentEndFunction("008LandOn", this, &CPlayer2D::SetNextState);

	m_Anim->SetPlayScale("006DoubleJump", 2.f);
	m_Anim->SetCurrentEndFunction("006DoubleJump", this, &CPlayer2D::SetNextState);


	m_Anim->SetPlayScale("003Dash", 2.f);
	m_Anim->AddCurrentNotify("003Dash", "003Dash", 6, this, &CPlayer2D::DashEnd);

	m_Anim->SetPlayScale("026ShadowDash", 2.f);
	m_Anim->AddCurrentNotify("026ShadowDash", "026ShadowDash", 6, this, &CPlayer2D::DashEnd);


	m_Anim->SetPlayScale("009Slash", 2.f);
	m_Anim->AddCurrentNotify("009Slash", "009Slash", 6, this, &CPlayer2D::SetNextState);
	m_Anim->SetPlayScale("010SlashAlt", 2.f);
	m_Anim->AddCurrentNotify("010SlashAlt", "010SlashAlt", 6, this, &CPlayer2D::SetNextState);

	m_Anim->SetPlayScale("013UpSlash", 2.f);
	m_Anim->AddCurrentNotify("013UpSlash", "013UpSlash", 6, this, &CPlayer2D::SetNextState);
	m_Anim->SetPlayScale("015DownSlash", 2.f);
	m_Anim->AddCurrentNotify("015DownSlash", "015DownSlash", 6, this, &CPlayer2D::SetNextState);

	m_Anim->SetPlayScale("017FireBall", 3.f);
	m_Anim->SetCurrentEndFunction("017FireBall", this, &CPlayer2D::DashEnd); //대시랑 로직이 같음

	m_Anim->SetPlayScale("028FireBallShadow", 3.f);
	m_Anim->SetCurrentEndFunction("028FireBallShadow", this, &CPlayer2D::DashEnd);

	m_Anim->SetPlayScale("018ChargeOnKnight", 2.f);

	m_Anim->SetPlayScale("031DashEnd", 3.f);
	m_Anim->SetCurrentEndFunction("031DashEnd", this, &CPlayer2D::SetNextState);

	m_Anim->SetPlayScale("032ChargeStart", 2.f);
	m_Anim->SetCurrentEndFunction("032ChargeStart", this, &CPlayer2D::Charging);

	m_Anim->SetCurrentEndFunction("020EnterTheKnight", this, &CPlayer2D::EnterRoomEnd);

	m_Anim->SetCurrentEndFunction("023Death", this, &CPlayer2D::Death);

	m_Anim->SetCurrentEndFunction("037Death2", this, &CPlayer2D::DeathEnd);

	m_Anim->SetCurrentEndFunction("025ProstrateRise", this, &CPlayer2D::SetNextState);

	//=========================이펙트
	//더블점프

	m_DoubleJumpSprite->GetAnimation()->SetPlayScale("007DoubleJumpEffect", 2.f);
	m_DoubleJumpSprite->GetAnimation()->AddCurrentNotify("007DoubleJumpEffect", "007DoubleJumpEffect", 5, this, &CPlayer2D::DoubleJumpEffectEnd);

	//대시
	m_DashSprite->GetAnimation()->SetPlayScale("004DashEffect", 4.f);
	m_DashSprite->GetAnimation()->SetCurrentEndFunction("004DashEffect", this, &CPlayer2D::DashEffectEnd);

	m_DashSprite->GetAnimation()->SetPlayScale("027ShadowDashEffect", 4.f);
	m_DashSprite->GetAnimation()->SetCurrentEndFunction("027ShadowDashEffect", this, &CPlayer2D::DashEffectEnd);

	//강화대시

	//공격
	m_AttackSprite->GetAnimation()->SetPlayScale("011SlashEffect", 5.f);
	m_AttackSprite->GetAnimation()->AddCurrentNotify("011SlashEffect", "011SlashEffect", 6, this, &CPlayer2D::AttackEffectEnd);

	m_AttackSprite->GetAnimation()->SetPlayScale("012SlashEffectAlt", 5.f);
	m_AttackSprite->GetAnimation()->AddCurrentNotify("012SlashEffectAlt", "012SlashEffectAlt", 6, this, &CPlayer2D::AttackEffectEnd);

	m_UpAttackSprite->GetAnimation()->SetPlayScale("014UpSlashEffect", 5.f);
	m_UpAttackSprite->GetAnimation()->AddCurrentNotify("014UpSlashEffect", "014UpSlashEffect", 6, this, &CPlayer2D::AttackEffectEnd);

	m_DownAttackSprite->GetAnimation()->SetPlayScale("016DownSlashEffect", 5.f);
	m_DownAttackSprite->GetAnimation()->AddCurrentNotify("016DownSlashEffect", "016DownSlashEffect", 6, this, &CPlayer2D::AttackEffectEnd);

	//강화공격
	m_AttackSprite->GetAnimation()->SetPlayScale("033SlashFEffect", 5.f);
	m_AttackSprite->GetAnimation()->AddCurrentNotify("033SlashFEffect", "033SlashFEffect", 6, this, &CPlayer2D::AttackEffectEnd);

	m_AttackSprite->GetAnimation()->SetPlayScale("034SlashFEffectAlt", 5.f);
	m_AttackSprite->GetAnimation()->AddCurrentNotify("034SlashFEffectAlt", "034SlashFEffectAlt", 6, this, &CPlayer2D::AttackEffectEnd);

	m_UpAttackSprite->GetAnimation()->SetPlayScale("035UpSlashFEffect", 5.f);
	m_UpAttackSprite->GetAnimation()->AddCurrentNotify("035UpSlashFEffect", "035UpSlashFEffect", 6, this, &CPlayer2D::AttackEffectEnd);

	m_DownAttackSprite->GetAnimation()->SetPlayScale("036DownSlashFEffect", 5.f);
	m_DownAttackSprite->GetAnimation()->AddCurrentNotify("036DownSlashFEffect", "036DownSlashFEffect", 6, this, &CPlayer2D::AttackEffectEnd);


	m_FireSprite->GetAnimation()->SetCurrentEndFunction("029FireEffect", this, &CPlayer2D::FireEffectEnd);
	m_FireSprite->GetAnimation()->SetPlayScale("029FireEffect", 5.f);

	m_FireSprite->GetAnimation()->SetCurrentEndFunction("030FireShadow", this, &CPlayer2D::FireEffectEnd);
	m_FireSprite->GetAnimation()->SetPlayScale("030FireShadow", 5.f);
}

void CPlayer2D::SetSounds()
{
	CResourceManager::GetInst()->LoadSound("Effect", "HeroDamage", false, "TheKnight/hero_damage.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "HeroDash", false, "TheKnight/hero_dash.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "HeroDeath", false, "TheKnight/hero_death_extra_details.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "HeroFalling", false, "TheKnight/hero_falling.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "HeroFireball", false, "TheKnight/hero_fireball.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "HeroJump", false, "TheKnight/hero_jump.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "HeroCharge", true, "TheKnight/hero_nail_art_charge_initiate.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "HeroLandSoft", false, "TheKnight/hero_land_soft.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "HeroWalk", true, "TheKnight/hero_run_footsteps_stone.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "HeroWings", false, "TheKnight/hero_wings.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "Herosword1", false, "TheKnight/sword_4.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "Herosword2", false, "TheKnight/sword_5.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "HeroRefill", false, "Main/ui_button_confirm.wav");
	
}

void CPlayer2D::SpriteAnimationSetting()
{
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

	float AttackX = 349.f;
	float AttackY = 186.f;

	m_AttackSprite->SetWorldScale(AttackX, AttackY);
	m_AttackSprite->SetAnimationFile("TheKnight");
	m_AttackSprite->SetRenderLayerName("Effect");
	m_AttackSprite->SetTextureReverse(true);
	m_AttackSprite->SetEnable(false);


	//윗공
	m_UpAttackSprite->SetPivot(0.5f, 0.4f);

	float UpAtkX = 169.f;
	float UpAtkY = 192.f;

	m_UpAttackSprite->SetWorldScale(UpAtkX, UpAtkY);
	m_UpAttackSprite->SetAnimationFile("TheKnight");
	m_UpAttackSprite->SetRenderLayerName("Effect");
	m_UpAttackSprite->SetTextureReverse(true);
	m_UpAttackSprite->SetEnable(false);

	//아랫공
	m_DownAttackSprite->SetPivot(0.5f, 0.4f);

	float DownAtkX = 182.f;
	float DownAtkY = 209.f;

	m_DownAttackSprite->SetWorldScale(DownAtkX, DownAtkY);
	m_DownAttackSprite->SetRelativePosition(0, -50.f);
	m_DownAttackSprite->SetAnimationFile("TheKnight");
	m_DownAttackSprite->SetRenderLayerName("Effect");
	m_DownAttackSprite->SetTextureReverse(true);
	m_DownAttackSprite->SetEnable(false);

	m_FireSprite->SetPivot(0.5f, 0.4f);

	float FireX = 306.f * g_SCALE;
	float FireY = 289.f * g_SCALE;

	m_FireSprite->SetWorldScale(FireX, FireY);
	m_FireSprite->SetAnimationFile("TheKnight");
	m_FireSprite->SetRenderLayerName("Effect");
	//m_FireSprite->GetMaterial(0)->SetRenderState("DepthDisable");
	m_FireSprite->SetRelativePosition(50, -20.f);
	m_FireSprite->SetTextureReverse(false);
	m_FireSprite->SetEnable(false);

	//차지 이펙트

	m_ChargeSprite->SetPivot(0.5f, 0.4f);

	float ChargeX = 205.f * g_SCALE;
	float ChargeY = 155.f * g_SCALE;

	m_ChargeSprite->SetWorldScale(ChargeX, ChargeY);
	m_ChargeSprite->SetAnimationFile("TheKnight");
	m_ChargeSprite->SetRenderLayerName("Effect");
	//m_FireSprite->GetMaterial(0)->SetRenderState("DepthDisable");
	//m_ChargeSprite->SetRelativePosition(50, -20.f);
	m_ChargeSprite->SetTextureReverse(true);
	m_ChargeSprite->SetEnable(false);
}

void CPlayer2D::SetCurAnim(EPlayerStates State)
{
	//애니메이션 세팅할때 이전 상태랑 같은거면 리턴
	if (m_PrevState == State)
		return;

	//! 주의, 이펙트는 여기 포함되지 않음
	switch (State)
	{
	case CPlayer2D::EPlayerStates::Idle:
		m_Anim->SetCurrentAnimation("001Idle");
		CResourceManager::GetInst()->SoundStop("HeroFalling");
		break;
	case CPlayer2D::EPlayerStates::Walk:
		m_Anim->SetCurrentAnimation("002Walk");
		CResourceManager::GetInst()->SoundPlay("HeroWalk");

		break;
	case CPlayer2D::EPlayerStates::Jump:
		m_Anim->SetCurrentAnimation("005-0Jump");
		CResourceManager::GetInst()->SoundPlay("HeroJump");
		break;
	case CPlayer2D::EPlayerStates::DoubleJump:
		m_Anim->SetCurrentAnimation("006DoubleJump");
		CResourceManager::GetInst()->SoundPlay("HeroWings");
		break;
	case CPlayer2D::EPlayerStates::Fall:
		m_Anim->SetCurrentAnimation("005-1AirBone");
		CResourceManager::GetInst()->SoundPlay("HeroFalling");
		break;
	case CPlayer2D::EPlayerStates::LandOn:
		m_Anim->SetCurrentAnimation("008LandOn");
		CResourceManager::GetInst()->SoundPlay("HeroLandSoft");
		break;
	case CPlayer2D::EPlayerStates::Dash:
		if (m_Advance)
			m_Anim->SetCurrentAnimation("026ShadowDash");
		else
			m_Anim->SetCurrentAnimation("003Dash");

		CResourceManager::GetInst()->SoundPlay("HeroDash");

		break;
	case CPlayer2D::EPlayerStates::Slash:
		m_Anim->SetCurrentAnimation("010SlashAlt");
		CResourceManager::GetInst()->SoundPlay("Herosword2");
		break;
	case CPlayer2D::EPlayerStates::DoubleSlash:
		m_Anim->SetCurrentAnimation("009Slash");
		CResourceManager::GetInst()->SoundPlay("Herosword1");
		break;
	case CPlayer2D::EPlayerStates::UpSlash:
		m_Anim->SetCurrentAnimation("013UpSlash");
		CResourceManager::GetInst()->SoundPlay("Herosword1");
		break;
	case CPlayer2D::EPlayerStates::DownSlash:
		m_Anim->SetCurrentAnimation("015DownSlash");
		CResourceManager::GetInst()->SoundPlay("Herosword1");
		break;
	case CPlayer2D::EPlayerStates::FireBall:
		if (m_Advance)
			m_Anim->SetCurrentAnimation("028FireBallShadow");
		else
			m_Anim->SetCurrentAnimation("017FireBall");
		CResourceManager::GetInst()->SoundPlay("HeroFireball");
		break;
	case CPlayer2D::EPlayerStates::Charge:
		m_Anim->SetCurrentAnimation("032ChargeStart");
		break;
	case CPlayer2D::EPlayerStates::Enter:
		m_Anim->SetCurrentAnimation("020EnterTheKnight");
		break;
	case CPlayer2D::EPlayerStates::Stun:
		m_Anim->SetCurrentAnimation("022Stun");
		CResourceManager::GetInst()->SoundPlay("HeroDamage");
		break;
	case CPlayer2D::EPlayerStates::Death:
		m_Anim->SetCurrentAnimation("023Death");
		m_CurState = EPlayerStates::Death;
		m_GravityAgent->SetPhysicsSimulate(false);
		m_KeyLock = true;
		m_Body->SetEnable(false);
		//CResourceManager::GetInst()->SoundPlay("HeroDeath");
		break;
	case CPlayer2D::EPlayerStates::DeathEnd:
		m_Anim->SetCurrentAnimation("037Death2");
		CResourceManager::GetInst()->SoundPlay("HeroDeath");
		break;
	case CPlayer2D::EPlayerStates::Prostrate:
		m_Anim->SetCurrentAnimation("024Prostrate");
		break;
	case CPlayer2D::EPlayerStates::ProstrateRise:
		m_Anim->SetCurrentAnimation("025ProstrateRise");
		break;
	case CPlayer2D::EPlayerStates::WallSlide:
		m_Anim->SetCurrentAnimation("021WallSlide");
		break;
	case CPlayer2D::EPlayerStates::DashEndGround:
		m_Anim->SetCurrentAnimation("031DashEnd");
		break;
	default:
		m_Anim->SetCurrentAnimation("001Idle");
		break;
	}
	m_PrevState = State;
}

void CPlayer2D::Start()
{
	CGameObject::Start();

	if (m_Scene)
		m_Scene->GetCameraManager()->SetCurrentCamera(m_Camera);

	m_Body->SetCollisionCallback(ECollision_Result::Collision,
		this, &CPlayer2D::CollisionBegin); //콜라이더 세팅
	m_Body->SetCollisionCallback(ECollision_Result::Release, this, &CPlayer2D::CollisionEnd);

	SetSounds();
	SpriteAnimationSetting();
	SetAnimation(); // 애니메이션 세팅
	SetInputKey(); //키셋팅

	//============================스킬 쿨 세팅
	SkillCoolDownInfo Dash = {};
	Dash.CoolDown = 0.5f;
	m_vecCoolDown.push_back(Dash);

	SkillCoolDownInfo Attack = {};
	Attack.CoolDown = 0.2f;
	m_vecCoolDown.push_back(Attack);

	SkillCoolDownInfo DoubleAttack = {};
	Attack.CoolDown = 0.5f;
	m_vecCoolDown.push_back(DoubleAttack);

	SkillCoolDownInfo Fire = {};
	Fire.CoolDown = 3.f;
	m_vecCoolDown.push_back(Fire);


	//중력 에이전트
	m_GravityAgent->SetPhysicsSimulate(false);
	m_GravityAgent->SetJumpVelocity(80.f);
	m_GravityAgent->SetGravityAccel(18.f);
	m_GravityAgent->SetSideWallCheck(true);

	SetProstrate();

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
	m_UpAttackSprite = CreateComponent<CSpriteComponent>("UpAttackSprite");
	m_DownAttackSprite = CreateComponent<CSpriteComponent>("DownAttackSprite");
	m_FireSprite = CreateComponent<CSpriteComponent>("FireSprite");
	m_ChargeSprite = CreateComponent<CSpriteComponent>("ChargeSprite");

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
	m_Sprite->AddChild(m_UpAttackSprite);
	m_Sprite->AddChild(m_DownAttackSprite);
	m_Sprite->AddChild(m_FireSprite);
	m_Sprite->AddChild(m_ChargeSprite);
	m_Sprite->AddChild(m_Arm);
	m_Arm->AddChild(m_Camera);

	//Body Collider
	m_Body->SetWorldPosition(200.f, 1000.f);
	m_Body->SetBoxSize(50.f, 98.f);
	m_Body->SetCollisionProfile("Player");


	//Arm
	Resolution RS = CDevice::GetInst()->GetResolution();

	float Width = (float)RS.Width / 2.f; // 640
	float Height = (float)((RS.Height / 2.f)); //360B

	//m_Arm->SetTargetOffset(Vector3(-Width, -175.f, 0.f));
	m_Arm->SetTargetOffset(Vector3(-Width, -Height, 0.f));

	//m_Sprite->SetInheritRotZ(true);
	//CMaterial* Material = m_Sprite->GetMaterial(0);
	//Material->SetOpacity(0.5f);
	//Material->SetRenderState("DepthDisable"); //깊이 무시?
	//m_SpriteChild->SetInheritRotZ(true);

	m_MaxHP = 5;
	m_HP = m_MaxHP;
	m_Gio = 0;

	return true;
}
void CPlayer2D::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	
	CheckDir(); //방향

	//카메라 세팅
	Vector3 BodyPos = m_Body->GetWorldPos();

	if (BodyPos.y < 300.f)
		m_Camera->SetWorldPositionY(-175.f);



	//무적 여부
	if (m_InfiniteMod)
	{
		m_InfiniteTime -= DeltaTime;

		if (m_flick)
		{
			if (m_Opacity)
			{
				m_Sprite->GetMaterial(0)->SetOpacity(0.5f);
				m_Opacity = false;
			}
			else
			{
				m_Sprite->GetMaterial(0)->SetOpacity(1.f);
				m_Opacity = true;
			}
		}

		if (m_InfiniteTime <= 0.f)
		{
			m_InfiniteMod = false;
			m_Sprite->GetMaterial(0)->SetOpacity(1.f);
			SetNextState();
			m_Body->SetEnable(true);
		}
	}

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

	//차지 애니메이션 관련
	if (m_ChargeStart)
	{
		std::string AnimName = m_Anim->GetCurrentAnimationName("TheKnight");

		if (AnimName != "018ChargeOnKnight")
		{
			ChargeOff();
			OutputDebugStringA("차징캔슬");			
		}		
	}

	switch (m_CurState)
	{
	case CPlayer2D::EPlayerStates::Idle:
		m_DashCount = 0;
		m_KeyLock = false;
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
		m_DashCount = 0;
		break;

	case CPlayer2D::EPlayerStates::Dash:
	{
		m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * m_Dir * 1500.f * g_DeltaTime);
	}
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
		//공격 시 살짝 뒤로감
		m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * m_Dir * (-100.f) * g_DeltaTime);
		break;
	case CPlayer2D::EPlayerStates::Charge:
		{
		if (m_ChargeStart)
			m_ChargingTime += g_DeltaTime;

		if (m_ChargingTime >= 1.f)
		{
			CPlayerHUD* HUD = (CPlayerHUD*)(m_Scene->GetViewport()->FindUIWindow<CPlayerHUD>("PlayerHUD"));
			HUD->CreateRefillHeart();
			m_ChargingTime = 0.f;
			CreateChargeEffect();
		}
		}
		break;
	case CPlayer2D::EPlayerStates::Enter:
		break;
	case CPlayer2D::EPlayerStates::Stun:
		{
			bool jump = m_GravityAgent->GetJump();
				if (!jump)
					m_CurState = EPlayerStates::Idle;
		}
		break;
	case CPlayer2D::EPlayerStates::Death:
		m_GravityAgent->SetPhysicsSimulate(false);
		break;
	case CPlayer2D::EPlayerStates::DeathEnd:
	{
		if(!(m_Gio == 0))
		--m_Gio;

		float Opa = m_Sprite->GetMaterial(0)->GetOpacity();
		Opa -= DeltaTime;
		m_Sprite->GetMaterial(0)->SetOpacity(Opa);
		if (Opa <= 0.f)
		{
			////마을 귀환














			/////
		}
		break;
	}
	case CPlayer2D::EPlayerStates::Prostrate:
		break;
	case CPlayer2D::EPlayerStates::ProstrateRise:
		break;
	case CPlayer2D::EPlayerStates::WallSlide:
		break;
	case CPlayer2D::EPlayerStates::DashEndGround:
		m_DashCount = 0;
		break;
	default:

		break;
	}

	if (m_CurState != EPlayerStates::Walk)
		CResourceManager::GetInst()->SoundStop("HeroWalk");

	if (m_CurState != EPlayerStates::Fall)
		CResourceManager::GetInst()->SoundStop("HeroFalling");

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

	m_GravityAgent;
	int a = 0;
}

void CPlayer2D::UpKey()
{
	CheckProstrate();

	if (m_CollisionDoor)
		EnterRoomStart();

	m_UpKey = true;
}

void CPlayer2D::DownKey()
{
	CheckProstrate();

	m_DownKey = true;
}

void CPlayer2D::UpKeyUp()
{
	m_UpKey = false;
}

void CPlayer2D::DownKeyUp()
{
	m_DownKey = false;
}

void CPlayer2D::Move()
{
	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * (float)m_Dir * 500.f * g_DeltaTime);

	if(m_CurState == EPlayerStates::Idle || m_CurState == EPlayerStates::Charge)
		//|| m_CurState == EPlayerStates::DashEndGround
		m_CurState = EPlayerStates::Walk;
}

void CPlayer2D::LeftMove()
{
	CheckProstrate();

	if (!m_KeyLock)
	{
		SetReverse(false);

		Move();
	}
}

void CPlayer2D::RightMove()
{
	CheckProstrate();

	if (!m_KeyLock)
	{
		SetReverse(true);

		Move();
	}
}

void CPlayer2D::Jump()
{
	CheckProstrate();

	OutputDebugStringA("점프");

	if (m_CurState == EPlayerStates::Stun)
		return;

	if (!m_KeyLock)
	{
		if (m_Jumping == 1)
		{
			//더블 점프
			m_GravityAgent->Jump();
			m_CurState = EPlayerStates::DoubleJump;
			m_Jumping++;

			//더블점프 이펙트
			m_DoubleJumpSprite->SetEnable(true);
			m_DoubleJumpSprite->GetAnimation()->SetCurrentAnimation("007DoubleJumpEffect");

		}
		else if (m_Jumping == 0)
		{
			//일반 점프
			m_GravityAgent->Jump();
			m_CurState = EPlayerStates::Jump;
			m_Jumping++;
		}
	}

}

void CPlayer2D::Fire()
{
	CheckProstrate();

	OutputDebugStringA("마관광살포");

	if (m_KeyLock || m_vecCoolDown[3].CoolDownEnable)
		return;

	//쿨타임 0.5초
	m_vecCoolDown[3].CoolDownEnable = true;
	m_vecCoolDown[3].CoolDown = 3.f;

	m_CurState = EPlayerStates::FireBall;
	m_KeyLock = true;

	m_GravityAgent->SetPhysicsSimulate(false);

	//탄 생성
	CMyBullet* Bullet = m_Scene->CreateObject<CMyBullet>("MyBullet");
	Bullet->SetWorldPosition(m_Sprite->GetWorldPos());
	//Bullet2->AddWorldRotationZ(m_Angle * g_DeltaTime);
	Bullet->SetWorldRotationZ(m_Angle);
	Bullet->SetDirection(m_Dir);
		
	Bullet->SetCollisionProfileName("PlayerAttack");

	if (m_Advance)
		Bullet->DarkBallMod();

	//이펙트
	SetAttackMotion(m_CurState);
	m_FireSprite->SetEnable(true);
}

void CPlayer2D::Dash()
{
	CheckProstrate();

	OutputDebugStringA("대시 시작");

	if (m_KeyLock)
		return;
	//////////////////////////////////////////////////////////////
	//m_GravityAgent->SetPhysicsSimulate(true);

	//////////////////////////////////////////////////////////////

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
		SetAttackMotion(m_CurState);
		m_DashSprite->SetEnable(true);
	}
}

void CPlayer2D::DashEnd()
{
	OutputDebugStringA("대시 끝");
	
	m_Scene;
	int ace = 0;
	
	CScene* Scene = CSceneManager::GetInst()->GetScene();
	CPlayer2D* Player = (CPlayer2D*)Scene->FindObject("Player2D");
	this;
	int a = 0;

	m_KeyLock = false;
	m_GravityAgent->SetPhysicsSimulate(true);
	
	//현재 Y좌표를 중력 에이전트에 보냄
	m_GravityAgent->SetFallTime(0.f);
	float fallY = (m_Body->GetWorldPos().y);
	m_GravityAgent->FallingStartOn(fallY);

	//다음 모션
	if (!m_Jumping)
		m_CurState = EPlayerStates::DashEndGround;
	else
		SetNextState();
	
	m_DashEndPos = 0;
}

void CPlayer2D::Attack()
{
	CheckProstrate();

	if (m_vecCoolDown[1].CoolDownEnable || m_KeyLock)
		return;

	//쿨타임 0.2초
	m_vecCoolDown[1].CoolDownEnable = true;
	m_vecCoolDown[1].CoolDown = 0.2f;

	//공중공격여부
	if (m_UpKey && !m_DownKey)
	{
		OutputDebugStringA("위");
		m_CurState = EPlayerStates::UpSlash;
		m_UpKey = false;
		SetAttackMotion(m_CurState);
		m_UpAttackSprite->SetEnable(true);
	}
	else if (m_Jumping && m_DownKey && !m_UpKey)
	{
		OutputDebugStringA("아래");
		m_CurState = EPlayerStates::DownSlash;
		m_DownKey = false;
		SetAttackMotion(m_CurState);
		m_DownAttackSprite->SetEnable(true);
	}
	else //일반공격
	{
		if (m_vecCoolDown[2].CoolDown > 0.f)
		{
			OutputDebugStringA("더블");
			m_CurState = EPlayerStates::DoubleSlash;
			SetAttackMotion(m_CurState);		
		}
		else
		{
			OutputDebugStringA("일반");
			m_CurState = EPlayerStates::Slash;
			
			//더블어택 내부쿨
			m_vecCoolDown[2].CoolDown = 0.5f;
			m_vecCoolDown[2].CoolDownEnable = true;

			SetAttackMotion(m_CurState);
		}
		m_AttackSprite->SetEnable(true);	
	}
	//콜라이더
	CreateHitCollider(m_CurState);
}

void CPlayer2D::Charge()
{
	CheckProstrate();

	if (m_Jumping == 0 && !m_KeyLock && m_CurState == EPlayerStates::Idle)
	{	
		OutputDebugStringA("차징 시작");
		m_CurState = EPlayerStates::Charge;
	}	
}

void CPlayer2D::Charging()
{
	if (m_CurState == EPlayerStates::Charge)
	{
		m_ChargeStart = true;
		m_Anim->SetCurrentAnimation("018ChargeOnKnight");
		m_Anim->GetCurrentAnimationName("TheKnight");
		m_ChargeSprite->SetEnable(true);
		m_ChargeSprite->GetAnimation()->SetCurrentAnimation("019ChargeEffect");	
		//사운드
		CResourceManager::GetInst()->SoundPlay("HeroCharge");
	}	
}

void CPlayer2D::ChargeOff()
{
	m_ChargeStart = false;
	m_ChargingTime = 0;
	m_ChargeSprite->SetEnable(false);
	CResourceManager::GetInst()->SoundStop("HeroCharge");	
}

void CPlayer2D::Death()
{
	m_CurState = EPlayerStates::DeathEnd;
	m_Anim->SetCurrentAnimation("037Death2");
}

void CPlayer2D::DeathEnd()
{
	
}

void CPlayer2D::EnterRoomStart()
{
	if (m_DoorName == "")
		return;

	m_Body->SetEnable(false);	
	m_CurState = EPlayerStates::Enter;
	m_KeyLock = true;
	InfiniteMod(3.f, false);

}

void CPlayer2D::EnterRoomEnd()
{
	m_CurState = EPlayerStates::Idle;
	m_Doorptr->ChangeScene(m_DoorName);
}

void CPlayer2D::Q()
{
	if (m_Advance)
	{
		//OutputDebugStringA("강화모드 해제");
		m_Advance = false;
		InfiniteMod(0.1f);
		
	}
		
	else
	{
		//OutputDebugStringA("강화모드 활성화");
		InfiniteMod(999999.f);
		m_Advance = true;

		m_GravityAgent->SetPhysicsSimulate(true);
		CPlayerHUD* HUD = (CPlayerHUD*)(m_Scene->GetViewport()->FindUIWindow<CPlayerHUD>("PlayerHUD"));
		//HUD->CreateBreakHeart();
		//HUD->UpgradeMaxHeart();
		
	}
		
}

void CPlayer2D::InfiniteMod(float Time, bool flick)
{
	m_flick = flick;
	m_InfiniteMod = true;
	m_InfiniteTime = Time;
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
	m_UpAttackSprite->SetEnable(false);
	m_DownAttackSprite->SetEnable(false);
}

void CPlayer2D::FireEffectEnd()
{
	m_FireSprite->SetEnable(false);
}



void CPlayer2D::CollisionBegin(const CollisionResult& Result)
{
	std::string dest = Result.Dest->GetCollisionProfile()->Name;

	if (dest == "Monster" || dest == "MonsterAttack")
	{
		OutputDebugStringA("플레이어 데미지!");
		if (m_InfiniteMod)
			return;
		//=======================================================================
		m_HP--;
		
		CPlayerHUD* HUD = (CPlayerHUD*)(m_Scene->GetViewport()->FindUIWindow<CPlayerHUD>("PlayerHUD"));
		HUD->CreateBreakHeart();
		HUD->DeleteHeart();
		

		CEffect* Effect = m_Scene->CreateObject<CEffect>("HitEffect");
		Effect->SetLifeTime(0.5f);
		Effect->SetWorldPosition(this->GetWorldPos());
		Effect->SetWorldScale(699.f, 140.f);

		std::string s = "PlayerHitEffect";
		Effect->SetCurAnimation(s, 5.f);

		m_GravityAgent->SetPhysicsSimulate(true);
		m_GravityAgent->SetJumpVelocity(40.f);
		m_GravityAgent->ObjectJump();

		m_KeyLock = false;
		m_CurState = EPlayerStates::Stun;

		InfiniteMod();
		m_Body->SetEnable(false);

		//사망
		if (m_HP <= 0)
		{
			m_CurState = EPlayerStates::Death;
			m_GravityAgent->SetPhysicsSimulate(false);
			m_KeyLock = true;
			m_Body->SetEnable(false);
			InfiniteMod(999.f, false);
		}
	}
	else if (dest == "Gio")
	{
		CEffect* Effect = m_Scene->CreateObject<CEffect>("GetGioEffect");
		Effect->SetLifeTime(0.2f);
		Effect->SetWorldPosition(this->GetWorldPos());
		Effect->SetPivot(0.5f, 0.5f);
		Effect->SetWorldScale(43.f * 2.f, 104.f *2.f);

		std::string s = "GetGioEffect";
		Effect->SetCurAnimation(s, 3.f);

		//지오 ++;
	}
	else if (dest == "Door")
	{
		m_CollisionDoor = true;
		m_Doorptr = (CDoor*)(Result.Dest->GetOwner());
		m_DoorName = Result.Dest->GetName();
	}
}

void CPlayer2D::CollisionEnd(const CollisionResult& Result)
{
	std::string dest = Result.Dest->GetCollisionProfile()->Name;

	if(dest == "Door")
		m_CollisionDoor = false;
}



//방향 체크(Update)
void CPlayer2D::CheckDir()
{
	//true 오른쪽 false 왼쪽
	bool Check = m_Sprite->GetTextureReverse();

	m_Dir = Check ? 1.f : -1.f;
	m_Angle = Check ? 0.f : 180.f;

	m_DashSprite->SetRelativePositionX(-120.f * m_Dir);
	m_FireSprite->SetRelativePositionX(80.f * m_Dir);

}

void CPlayer2D::SetReverse(bool Enable)
{
	m_Sprite->SetTextureReverse(Enable);
	m_DashSprite->SetTextureReverse(!Enable);
	m_DoubleJumpSprite->SetTextureReverse(Enable);
	m_UpAttackSprite->SetTextureReverse(Enable);
	m_DownAttackSprite->SetTextureReverse(Enable);
	m_AttackSprite->SetTextureReverse(Enable);
	m_FireSprite->SetTextureReverse(!Enable);
	m_ChargeSprite->SetTextureReverse(Enable);
	
}

void CPlayer2D::SetNextState()
{
	m_Prostrate = false;

	if (m_Jumping)
		m_CurState = EPlayerStates::Fall;	
	else
		if (m_CurState == EPlayerStates::Dash)
			m_CurState = EPlayerStates::DashEndGround;
		else
			m_CurState = EPlayerStates::Idle;
}

void CPlayer2D::SetAttackMotion(EPlayerStates State)
{
	switch (State)
	{
	case CPlayer2D::EPlayerStates::Slash:
		if(m_Advance)
			m_AttackSprite->GetAnimation()->SetCurrentAnimation("034SlashFEffectAlt");
		else
			m_AttackSprite->GetAnimation()->SetCurrentAnimation("012SlashEffectAlt");

		break;
	case CPlayer2D::EPlayerStates::DoubleSlash:
		if (m_Advance)
			m_AttackSprite->GetAnimation()->SetCurrentAnimation("033SlashFEffect");
		else
			m_AttackSprite->GetAnimation()->SetCurrentAnimation("011SlashEffect");

		break;
	case CPlayer2D::EPlayerStates::UpSlash:
		if(m_Advance)
			m_UpAttackSprite->GetAnimation()->SetCurrentAnimation("035UpSlashFEffect");
		else
			m_UpAttackSprite->GetAnimation()->SetCurrentAnimation("014UpSlashEffect");
		
		break;
	case CPlayer2D::EPlayerStates::DownSlash:
		if(m_Advance)
			m_DownAttackSprite->GetAnimation()->SetCurrentAnimation("036DownSlashFEffect");
		else
			m_DownAttackSprite->GetAnimation()->SetCurrentAnimation("016DownSlashEffect");

		break;
	case CPlayer2D::EPlayerStates::FireBall:
		if (m_Advance)
			m_FireSprite->GetAnimation()->SetCurrentAnimation("030FireShadow");
		else
			m_FireSprite->GetAnimation()->SetCurrentAnimation("029FireEffect");

		break;
	case CPlayer2D::EPlayerStates::Dash:
		if (m_Advance)
			m_DashSprite->GetAnimation()->SetCurrentAnimation("027ShadowDashEffect");
		else
			m_DashSprite->GetAnimation()->SetCurrentAnimation("004DashEffect");
		break;	
	}

}

void CPlayer2D::CreateHitCollider(EPlayerStates State)
{
	CPlayerAttack* AttackCollider = m_Scene->CreateObject<CPlayerAttack>("PlayerAttack");

	Vector3 v;

	switch (m_CurState)
	{
	case CPlayer2D::EPlayerStates::Slash:
		v = m_AttackSprite->GetWorldPos();
		v.x += 100 * m_Dir;
		m_DownAttack = false;
		break;
	case CPlayer2D::EPlayerStates::DoubleSlash:
		v = m_AttackSprite->GetWorldPos();
		v.x += 100 * m_Dir;
		m_DownAttack = false;
		break;
	case CPlayer2D::EPlayerStates::UpSlash:
		v = m_UpAttackSprite->GetWorldPos();
		v.y += 50.f;
		m_DownAttack = false;
		break;

	case CPlayer2D::EPlayerStates::DownSlash:
		v = m_DownAttackSprite->GetWorldPos();
		v.y -= 50.f;
		m_DownAttack = true;
		break;
	default:
		return;
		break;
	}
	AttackCollider->SetWorldPosition(v);
}

void CPlayer2D::CreateChargeEffect()
{
	CEffect* Effect = m_Scene->CreateObject<CEffect>("ChargeEffect");
	Effect->SetLifeTime(0.5f);
	Effect->SetWorldPosition(this->GetWorldPos());
	Effect->AddWorldPositionY(-25.f);
	Effect->SetWorldScale(314.f, 315.f);

	std::string s = "RefillEffect";
	Effect->SetCurAnimation(s, 5.f);

	CResourceManager::GetInst()->SoundPlay("HeroRefill");
}
