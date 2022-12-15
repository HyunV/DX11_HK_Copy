#include "Gio.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/GravityAgent.h"
#include "Animation/Animation2D.h"
#include "Effect.h"
#include "Scene/Scene.h"
#include <time.h>

#include "Scene/SceneViewPort.h"
#include "UI/UIWindow.h"
#include "Player2D.h"

CGio::CGio()
{
	SetTypeID<CGio>();

	m_ObjectTypeName = "Gio";
}

CGio::CGio(const CGio& Obj)
{

}

CGio::~CGio()
{
}

void CGio::JumpGio()
{
		m_Gravity->ObjectJump();
}

void CGio::SetGravityPosGio(float Y)
{
	m_Gravity->SetPosY(Y);
}

void CGio::Start()
{
	CGameObject::Start();
}

bool CGio::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderBox2D>("Gio");
	m_Sprite = CreateComponent<CSpriteComponent>("GioSprite");
	m_Gravity = CreateComponent<CGravityAgent>("Gravity");
	m_Gravity->SetPhysicsSimulate(true);
	m_Gravity->SetGravityAccel(20.f);
	m_Gravity->SetJumpVelocity(50.f);

	m_Body->SetCollisionProfile("MonsterSight");
	m_Body->SetCollisionCallback(ECollision_Result::Collision, this, &CGio::CollisionCoin);
	m_Body->SetBoxSize(30.f, 30.f);

	SetRootComponent(m_Body);
	m_Body->AddChild(m_Sprite);

	m_Sprite->SetAnimationFile("Effects");
	m_Sprite->GetAnimation()->SetCurrentAnimation("Gio");
	m_Sprite->GetAnimation()->SetPlayScale("Gio", 2.f);
	m_Sprite->SetPivot(0.5f, 0.5f);
	m_Sprite->SetWorldScale(30.f, 30.f);

	CResourceManager::GetInst()->LoadSound("Effect", "GetGio", false, "geo_small_collect_1.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "GetGio2", false, "geo_small_collect_2.wav");

	return true;
}

void CGio::Update(float DeltaTime)
{
	Vector3 v = this->GetWorldPos();
	CGameObject::Update(DeltaTime);

		if (m_Gravity->GetJump())
			AddWorldPosition(GetWorldAxis(AXIS_X) * m_Dir * m_Range * g_DeltaTime);

	m_Time += DeltaTime;
}


CGio* CGio::Clone() const
{
	return new CGio(*this);
}

void CGio::CollisionCoin(const CollisionResult& result)
{
	if (m_Time >= 0.7f)
	{
		OutputDebugStringA("µ· È¹µæ");

		int shuffle = rand() % 2;
		if (shuffle == 1)
			CResourceManager::GetInst()->SoundPlay("GetGio");
		else
			CResourceManager::GetInst()->SoundPlay("GetGio2");
		
		CPlayer2D* Player = (CPlayer2D*)(result.Dest->GetOwner());
		Player->AddGio((rand()+100)%1000);
		//Player->AddGio(1);
		Destroy();
	}
}
