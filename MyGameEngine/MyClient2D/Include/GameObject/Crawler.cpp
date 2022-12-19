#include "Crawler.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Scene/Scene.h"
#include "Animation/Animation2D.h"
#include "Component/GravityAgent.h"
#include "Gio.h"
#include "PlayerAttack.h"
#include <time.h>

CCrawler::CCrawler()
{
	SetTypeID<CCrawler>();

	m_ObjectTypeName = "Crawler";
}

CCrawler::CCrawler(const CCrawler& Obj)	:
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("CrawlerBody"); //루트
	m_Sprite = (CSpriteComponent*)FindComponent("CrawlerSprite");

	m_GravityAgent = (CGravityAgent*)FindComponent("CrawlerGravityAgent");
	m_Anim = CResourceManager::GetInst()->FindAnimation2D("Crawler");
}

CCrawler::~CCrawler()
{
}

void CCrawler::SpriteAnimationSetting()
{
	m_Sprite->SetPivot(0.5f, 0.3f);

	float x = 301.f * g_SCALE;
	float y = 149.f * g_SCALE;
	m_Sprite->SetWorldScale(x, y);
	m_Sprite->SetRenderLayerName("Player");
	m_Sprite->GetMaterial(0)->SetRenderState("DepthDisable");
}

void CCrawler::SetAnimation()
{
	m_Anim->SetCurrentEndFunction("Crawler002TurnOn", this, &CCrawler::ChangeDir);
	m_Anim->SetPlayScale("Crawler002TurnOn", 5.f);

	m_Anim->SetPlayScale("Crawler003Fall", 5.f);

	m_Anim->SetPlayScale("Crawler001Walk", 2.f);
	m_Anim->SetLoop("Crawler001Walk", true);
}

void CCrawler::SetCurAnim(EMonsterState State)
{
	if (m_PrevState == State)
		return;

	switch (State)
	{
	case CCrawler::EMonsterState::Fall:
		m_Anim->SetCurrentAnimation("Crawler003Fall");
		break;
	case CCrawler::EMonsterState::Walk:
		CResourceManager::GetInst()->SoundPlay("CrawlerWalk");
		m_Anim->SetCurrentAnimation("Crawler001Walk");
		break;
	case CCrawler::EMonsterState::TurnOn:
		m_Anim->SetCurrentAnimation("Crawler002TurnOn");
		break;
	case CCrawler::EMonsterState::Death:
		m_Anim->SetCurrentAnimation("Crawler004Death");
		break;
	default:
		break;
	}

	m_PrevState = State;
}

void CCrawler::Start()
{
	CGameObject::Start();

	SpriteAnimationSetting();
	SetAnimation();

	m_Body->SetCollisionCallback(ECollision_Result::Collision, this, &CCrawler::CollisionBegin);

	m_GravityAgent->ObjectJump();

	int rands = rand() % 2;
	if (rands == 0)
		m_Sprite->SetTextureReverse(true);
	else
		m_Sprite->SetTextureReverse(false);

	CheckDir();
}

bool CCrawler::Init()
{
	CGameObject::Init();
	m_Body = CreateComponent<CColliderBox2D>("CrawlerBody");
	m_Sprite = CreateComponent<CSpriteComponent>("CrawlerSprite");
	m_GravityAgent = CreateComponent<CGravityAgent>("CrawlerGravityAgent");

	//애니메이션
	m_Sprite->SetAnimationFile("Crawler");
	m_Anim = m_Sprite->GetAnimation();
	m_Anim->SetCurrentAnimation("Crawler003Fall");

	SetRootComponent(m_Body);
	m_Body->AddChild(m_Sprite);

	m_Body->SetWorldPosition(860.f, 1000.f);
	m_Body->SetBoxSize(90.f, 50.f);
	m_Body->SetCollisionProfile("Monster");

	m_GravityAgent->SetJumpVelocity(30.f);
	m_GravityAgent->SetGravityAccel(7.f);
	m_GravityAgent->SetPhysicsSimulate(true);
	m_CurState = EMonsterState::Fall;

	m_HP = 2;
	return true;
}

void CCrawler::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (!m_Body->GetEnable() && m_CurState != EMonsterState::Death)
		Destroy();

	CheckDir();
	
	if (m_Accel <= 1000.f)
		m_Accel += DeltaTime;
	
	//히트 머테리얼
	if (m_MaterialChangeTime >= 1.f)
	{
		m_MaterialChangeTime += DeltaTime;

		if (m_MaterialChangeTime >= 1.1f)
		{
			m_Sprite->GetMaterial(0)->SetBaseColor(1.f, 1.f, 1.f, 1.f);
			m_Sprite->GetMaterial(0)->SetOpacity(1.f);
			m_MaterialChangeTime = 0.f;
		}
	}

	switch (m_CurState)
	{
	case CCrawler::EMonsterState::Fall:		
		if (!m_GravityAgent->GetJump())
			m_CurState = EMonsterState::Walk;
		break;
	case CCrawler::EMonsterState::Walk:
		if (m_GravityAgent->GetSideWallCheck())
			m_CurState = EMonsterState::TurnOn;
		else
			AddWorldPositionX(m_Dir * (500.f +m_Accel)* g_DeltaTime);
		
		break;
	case CCrawler::EMonsterState::TurnOn:
		break;
	case CCrawler::EMonsterState::Death:
		m_Time += DeltaTime;

		if (m_Time >= 3.f)
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

	SetCurAnim(m_CurState);
}

void CCrawler::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CCrawler* CCrawler::Clone() const
{
	return new CCrawler(*this);
}

void CCrawler::ChangeDir()
{
	bool check = m_Sprite->GetTextureReverse();
	m_Sprite->SetTextureReverse(!check);
	m_CurState = EMonsterState::Walk;
}

void CCrawler::CheckDir()
{
	//true 오른쪽 false 왼쪽
	bool Check = m_Sprite->GetTextureReverse();

	m_Dir = Check ? 1.f : -1.f;
	//m_Angle = Check ? 0.f : 180.f;
}

void CCrawler::CreateGio()
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

void CCrawler::CollisionBegin(const CollisionResult& Result)
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

		//색 변화 머테리얼
		m_Sprite->GetMaterial(0)->SetOpacity(0.7f);
		m_Sprite->GetMaterial(0)->SetBaseColor(255, 255, 255, 255);
		m_MaterialChangeTime = 1.f;

		//hp 감소
		m_HP -= Damage;
		if (m_HP <= 0) //사망
		{
			CreateGio();
			CResourceManager::GetInst()->SoundPlay("MonDeathHit");
			m_GravityAgent->SetGravityAccel(15.f);
			m_GravityAgent->ObjectJump();
			m_CurState = EMonsterState::Death;
			m_Body->SetEnable(false);
		}
	}
}
