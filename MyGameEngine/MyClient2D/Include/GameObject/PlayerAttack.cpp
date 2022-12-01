#include "PlayerAttack.h"
#include "Player2D.h"
#include "Scene/Scene.h"
#include "Component/ColliderSphere2D.h" 
#include "Scene/SceneManager.h"
#include "Effect.h"

CPlayerAttack::CPlayerAttack()
{
	SetTypeID<CPlayerAttack>();

	m_ObjectTypeName = "CPlayerAttack";
}

CPlayerAttack::CPlayerAttack(const CPlayerAttack& Obj)	:
	CGameObject(Obj)
{
	
}

CPlayerAttack::~CPlayerAttack()
{
}

void CPlayerAttack::Start()
{
	CGameObject::Start();
}

bool CPlayerAttack::Init()
{
	CGameObject::Init();
	m_Body = CreateComponent<CColliderSphere2D>("PlayerAttack");
	m_Body->SetCollisionProfile("PlayerAttack");
	m_Body->SetCollisionCallback(ECollision_Result::Collision, 
		this, &CPlayerAttack::CollisionBegin);
	m_LifeTime = 0.2f;

	CResourceManager::GetInst()->LoadSound("Effect", "HitAttack", false, "Enemy/enemy_damage.wav");
	return true;
}

void CPlayerAttack::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

CPlayerAttack* CPlayerAttack::Clone() const
{
	return new CPlayerAttack(*this);
}

void CPlayerAttack::CollisionBegin(const CollisionResult& Result)
{
	//평타 공격이 맞았다는 의미
	//CScene* Scene = CSceneManager::GetInst()->GetScene();
	//CPlayer2D* Player = (CPlayer2D*)(Scene->GetPlayer());

	//if (Player->GetDownAttackEnable())
	//{
	//	OutputDebugStringA("하단공격");
	//	Player->GetGravityAgent()->MiniJump();
	//	Player->ResetDoubleJumping();
	//	Player->m_DashCount = 0;
	//}

	//CEffect* Effect = Scene->CreateObject<CEffect>("SwordEffect");
	//Effect->SetLifeTime(0.1f);
	//Effect->SetWorldPosition(this->GetWorldPos());
	//Effect->SetWorldScale(219.f*2.f, 106.f*2.f);
	//
	//std::string s = "SwordEffect";
	//Effect->SetCurAnimation(s, 5.f);

	//CResourceManager::GetInst()->SoundPlay("HitAttack");

	Destroy();
}
