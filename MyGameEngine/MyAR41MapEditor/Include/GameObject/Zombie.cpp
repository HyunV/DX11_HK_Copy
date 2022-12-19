#include "Zombie.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Scene/Scene.h"
#include "Animation/Animation2D.h"
#include "Component/GravityAgent.h"
#include "Gio.h"
#include "PlayerAttack.h"
#include <time.h>

CZombie::CZombie()
{
	SetTypeID<CZombie>();

	m_ObjectTypeName = "Zombie";
}

CZombie::CZombie(const CZombie& Obj)	: 
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("ZombieBody"); //루트
	m_Sight = (CColliderBox2D*)FindComponent("ZombieSight");
	m_Sprite = (CSpriteComponent*)FindComponent("ZombieSprite");

	m_GravityAgent = (CGravityAgent*)FindComponent("ZombieGravityAgent");
	m_Anim = CResourceManager::GetInst()->FindAnimation2D("Zombie");
}

CZombie::~CZombie()
{
	CResourceManager::GetInst()->SoundStop("MonWalk");
}

void CZombie::SetSounds()
{
	CResourceManager::GetInst()->LoadSound("Effect", "MonWalk", true, "Enemy/zombie_five_footstep.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "MonAttack", false, "Enemy/zombie_shield_sword_1.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "MonDeath", false, "Enemy/zombie_death.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "MonDeathHit", false, "Enemy/enemy_death_sword.wav");
}

void CZombie::SpriteAnimationSetting()
{
	m_Sprite->SetPivot(0.45f, 0.35f);

	float x = 239.f * g_SCALE;
	float y = 219.f * g_SCALE;
	m_Sprite->SetWorldScale(x, y);
	m_Sprite->SetRenderLayerName("Player");
	m_Sprite->GetMaterial(0)->SetRenderState("DepthDisable");
	//m_Sprite->SetTextureReverse(true);
}

void CZombie::SetAnimation()
{
	m_Anim->SetCurrentEndFunction("Zombie_003_TurnOn", this, &CZombie::ChangeDir);
	m_Anim->SetPlayScale("Zombie_003_TurnOn", 5.f);

	m_Anim->SetCurrentEndFunction("Zombie_004_Attack", this, &CZombie::Attack);
	m_Anim->SetPlayScale("Zombie_004_Attack", 5.f);
}

void CZombie::Start()
{
	CGameObject::Start();
	//충돌세팅

	SetSounds();
	SpriteAnimationSetting();
	SetAnimation(); // 애니메이션 세팅
	srand((unsigned int)time(0));

	m_Sight->SetCollisionCallback(ECollision_Result::Collision, this, &CZombie::SightCollisionBegin);

	m_Body->SetCollisionCallback(ECollision_Result::Collision, this, &CZombie::CollisionBegin);

	SkillCoolDownInfo Attack = {};
	Attack.CoolDown = 1.f;
	m_vecCoolDown.push_back(Attack);
}

bool CZombie::Init()
{
	CGameObject::Init();
	//컴포넌트
	m_Body = CreateComponent<CColliderBox2D>("ZombieBody");
	m_Sight = CreateComponent<CColliderBox2D>("ZombieSight");
	m_Sprite = CreateComponent<CSpriteComponent>("ZombieSprite");
	// m_Body->SetName("Body");
	m_GravityAgent = CreateComponent<CGravityAgent>("ZombieGravityAgent");
	//애니메이션
	m_Sprite->SetAnimationFile("Zombie");
	m_Anim = m_Sprite->GetAnimation();
	m_Anim->SetCurrentAnimation("Zombie_001_Idle");

	//계층구조
	SetRootComponent(m_Body);
	m_Body->AddChild(m_Sprite);
	m_Body->AddChild(m_Sight);

	m_Body->SetWorldPosition(450.f, 1000.f);
	m_Body->SetBoxSize(80.f, 90.f);
	m_Body->SetCollisionProfile("Monster");

	m_Sight->SetRelativePosition(-90.f, 0.f);
	m_Sight->SetBoxSize(90.f, 90.f);
	m_Sight->SetCollisionProfile("MonsterSight");

	m_GravityAgent->SetJumpVelocity(30.f);
	m_GravityAgent->SetGravityAccel(20.f);
	m_GravityAgent->SetPhysicsSimulate(true);
	m_CurState = EMonsterState::Idle;

	m_HP = 3;
	return true;
}

void CZombie::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	CheckDir();

	if (!m_Body->GetEnable() && m_CurState != EMonsterState::Death)
		Destroy();

	//히트 머테리얼
	if (MaterialChangeTime >= 1.f)
	{
		MaterialChangeTime += DeltaTime;

		if (MaterialChangeTime >= 1.1f)
		{
			m_Sprite->GetMaterial(0)->SetBaseColor(1.f, 1.f, 1.f, 1.f);
			m_Sprite->GetMaterial(0)->SetOpacity(1.f);
			MaterialChangeTime = 0.f;
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

	if (m_Time <= 0.f)
	{
		int State = rand() % 3;
		m_CurState = (EMonsterState)State;
		m_Time = 2.f;
	}

	switch (m_CurState)
	{
	case CZombie::EMonsterState::Idle:
		break;
	case CZombie::EMonsterState::Walk:
		m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * m_Dir * 100.f * g_DeltaTime);
		break;
	case CZombie::EMonsterState::TurnOn:
		break;
	case CZombie::EMonsterState::Attack:
		break;
	case CZombie::EMonsterState::Attacking:
		m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * m_Dir * 1000.f * g_DeltaTime);
		break;
	case CZombie::EMonsterState::Death:
		if (m_GravityAgent->GetJump())
			m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * m_Dir * 80.f * g_DeltaTime);

		m_Time += DeltaTime;
		//죽으면 시간을 200초로 돌려놓고 멈춤. 그리고 3초 뒤
		if (m_Time >= 203.f)
		{
			float Opa = m_Sprite->GetMaterial(0)->GetOpacity();
			Opa -= DeltaTime;
			m_Sprite->GetMaterial(0)->SetOpacity(Opa);

			if (Opa <= 0.f)
				Destroy();
		}
		break;
	default:
		break;
	}

	if (m_CurState != EMonsterState::Death)
		m_Time -= DeltaTime;

	SetCurAnim(m_CurState);
}

void CZombie::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CZombie* CZombie::Clone() const
{
	return new CZombie(*this);
}

void CZombie::Attack()
{
	m_CurState = EMonsterState::Attacking;
	m_Time = 0.2f;

	m_vecCoolDown[0].CoolDownEnable = true;
	m_vecCoolDown[0].CoolDown = 1.f;
}

void CZombie::CheckDir()
{
	//true 오른쪽 false 왼쪽
	bool Check = m_Sprite->GetTextureReverse();

	m_Dir = Check ? 1.f : -1.f;
	m_Angle = Check ? 0.f : 180.f;
}

void CZombie::SetCurAnim(EMonsterState State)
{
	if (m_PrevState == State)
		return;

	switch (State)
	{
	case CZombie::EMonsterState::Idle:
		m_Anim->SetCurrentAnimation("Zombie_001_Idle");
		m_Time = 2.f;
		break;
	case CZombie::EMonsterState::Walk:
		m_Anim->SetCurrentAnimation("Zombie_002_Walk");
		//CResourceManager::GetInst()->SoundPlay("MonWalk");
		m_Time = 2.f;
		break;
	case CZombie::EMonsterState::TurnOn:
		m_Anim->SetCurrentAnimation("Zombie_003_TurnOn");
		break;
	case CZombie::EMonsterState::Attack:
		m_Anim->SetCurrentAnimation("Zombie_004_Attack");
		break;
	case CZombie::EMonsterState::Attacking:
		m_Anim->SetCurrentAnimation("Zombie_005_Attacking");
		CResourceManager::GetInst()->SoundPlay("MonAttack");
		break;
	case CZombie::EMonsterState::Death:
		m_Anim->SetCurrentAnimation("Zombie_006_Death");
		CResourceManager::GetInst()->SoundPlay("MonDeath");
		CResourceManager::GetInst()->SoundStop("MonWalk");
		break;
	default:
		break;
	}
	m_PrevState = State;
}

void CZombie::ChangeDir()
{
	bool check = m_Sprite->GetTextureReverse();
	m_Sprite->SetTextureReverse(!check);
	//m_CurState = EMonsterState::Idle();
	m_Time = 0.f;
	m_Sight->SetRelativePosition(-90.f * m_Dir, 0.f);
}

void CZombie::CreateGio()
{
	CScene* Scene = this->GetScene();

	int Count = (rand() % 5) + 1;

	for (int i = 0; i < Count; i++)
	{
		OutputDebugStringA("코인생성");
		CGio* Gio = Scene->CreateObject<CGio>("Gio");

		Vector3 v = this->GetWorldPos();
		Gio->SetWorldPosition(v);
		Gio->SetGravityPosGio(v.y);
		Gio->JumpGio();
		int Dir = rand() % 2;
		float x = 1.f;
		if (Dir == 0)
			x = -1.f;

		Gio->SetDir(x);

		int Range = (rand() + 300) % 300;
		Gio->SetRange((float)Range);
	}
}

void CZombie::CollisionBegin(const CollisionResult& Result)
{
	std::string dest = Result.Dest->GetName();

	//공격 당하는 충돌일 시
	if (dest == "PlayerAttack" || dest == "PlayerBullet")
	{
		int Damage = 0;
		if (dest == "PlayerAttack")
		{
			CPlayerAttack* Attack = (CPlayerAttack*)(Result.Dest->GetOwner());
			Damage = Attack->GetDamage();
		}		
		else if (dest == "PlayerBullet")
			Damage = 3;

		OutputDebugStringA("좀비 맞음!");

		//색 변화 머테리얼
		m_Sprite->GetMaterial(0)->SetOpacity(0.7f);
		m_Sprite->GetMaterial(0)->SetBaseColor(255, 255, 255, 255);
		MaterialChangeTime = 1.f;

		//hp 감소
		m_HP -= Damage;
		if (m_HP <= 0) //사망
		{
			CreateGio();
			OutputDebugStringA("좀비 사망");
			CResourceManager::GetInst()->SoundPlay("MonDeathHit");
			m_GravityAgent->ObjectJump();
			m_CurState = EMonsterState::Death;
			m_Body->SetEnable(false);
			m_Sight->SetEnable(false);
			m_Time = 200.f;
		}
	}
}

void CZombie::SightCollisionBegin(const CollisionResult& Result)
{
	if (m_vecCoolDown[0].CoolDownEnable)
		return;
	OutputDebugStringA("시야들옴");
	m_CurState = EMonsterState::Attack;
	m_Time = 100.f;
}
