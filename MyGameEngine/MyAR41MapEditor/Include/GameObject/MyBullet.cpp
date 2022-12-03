#include "MyBullet.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderSphere2D.h"
#include "Component/GravityAgent.h"
#include "Animation/Animation2D.h"
#include "Effect.h"
#include "Scene/Scene.h"


CMyBullet::CMyBullet()
{
	SetTypeID<CMyBullet>();

	m_ObjectTypeName = "MyBullet";
}

CMyBullet::CMyBullet(const CMyBullet& Obj) :
	CGameObject(Obj)
{
}

CMyBullet::~CMyBullet()
{
}

void CMyBullet::SetCollisionProfileName(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
}

void CMyBullet::SetDirection(float Dir)
{
	if (Dir < 0)
	{
		m_Sprite->SetTextureReverse(true);
		if (m_BallMod)
			m_Sprite->SetPivot(DarkBallPivot.y, 0.5f);
		else
			m_Sprite->SetPivot(NormalBallPivot.y, 0.5f);
	}
	else
	{
		if (m_BallMod)
			m_Sprite->SetPivot(DarkBallPivot.x, 0.5f);
		else
			m_Sprite->SetPivot(NormalBallPivot.x, 0.5f);
	}
}

void CMyBullet::Start()
{
	CGameObject::Start();
}

bool CMyBullet::Init()
{
	CGameObject::Init();
	SetLifeTime(0.7f);
	m_Body = CreateComponent<CColliderSphere2D>("PlayerBullet");
	m_Sprite = CreateComponent<CSpriteComponent>("spritebullet");

	m_Gravity = CreateComponent<CGravityAgent>("Gravity");
	m_Gravity->SetPhysicsSimulate(false);

	m_Body->AddChild(m_Sprite);

	m_Body->SetCollisionProfile("PlayerAttack");
	m_Body->SetCollisionCallback<CMyBullet>(ECollision_Result::Collision, 
		this, &CMyBullet::CollisionBullet);
	m_Body->SetRadius(40.f);

	//¾Ö´Ï¸ÞÀÌ¼Ç
	m_Sprite->SetAnimationFile("Effects");
	m_Anim = m_Sprite->GetAnimation();
	m_Anim->SetCurrentAnimation("FireBallShoot");

	DarkBallMod();
	NormalBallMod();

	m_Anim->SetPlayScale("FireBallShoot", 5.f);
	m_Anim->SetPlayScale("DarkBallShoot", 5.f);

	return true;
}

void CMyBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	AddWorldPosition(GetWorldAxis(AXIS_X) * 3000.f * DeltaTime);
	//AddWorldPosition(GetWorldAxis(AXIS_X) * 100.f * DeltaTime);

	if (m_Gravity->GetSideWallCheck())
	{
		HitBall();
		Destroy();
	}
		
}

void CMyBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CMyBullet* CMyBullet::Clone() const
{
	return new CMyBullet(*this);
}

void CMyBullet::DarkBallMod()
{
	m_BallMod = true;
	DarkBallPivot = Vector2(0.87f, 0.13f); //¿À¸¥ÂÊ ¼¦ ¿ÞÂÊ ¼¦ ÇÇº¿
	m_Anim->SetCurrentAnimation("DarkBallShoot");
	m_Sprite->SetWorldScale(504.f * g_SCALE, 157.f * g_SCALE);
}

void CMyBullet::NormalBallMod()
{
	m_BallMod = false;
	NormalBallPivot = Vector2(0.7f, 0.3f);
	m_Anim->SetCurrentAnimation("FireBallShoot");
	m_Sprite->SetWorldScale(317.f * g_SCALE, 143.f * g_SCALE);
}

void CMyBullet::HitBall()
{
	Vector3 v = m_Body->GetWorldPos();
	
	CEffect* Effect = m_Scene->CreateObject<CEffect>("FireEffect");
	Effect->SetWorldPosition(v);
	Effect->SetLifeTime(0.2f);
	Effect->SetWorldScale(349.f, 186.f);
	std::string s = "FireBallEffect";
	Effect->SetCurAnimation(s, 5.f);

	if (!m_BallMod)
		Destroy();
}

void CMyBullet::CollisionBullet(const CollisionResult& result)
{	//º®¿¡ ºÎ‹HÇû´Ù¸é
		HitBall();
}
