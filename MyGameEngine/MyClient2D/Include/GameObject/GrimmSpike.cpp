#include "GrimmSpike.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Animation/Animation2D.h"
#include "Scene/Scene.h"

CGrimmSpike::CGrimmSpike()
{
	SetTypeID<CGrimmSpike>();

	m_ObjectTypeName = "GrimmSpike";
}

CGrimmSpike::CGrimmSpike(const CGrimmSpike& Obj)	:
	CGameObject(Obj)
{

}

CGrimmSpike::~CGrimmSpike()
{
}

void CGrimmSpike::Start()
{
	CGameObject::Start();
	CResourceManager::GetInst()->LoadSound("Effect", "SpikeStart", false, "Boss/grimm_spikes_pt_1_grounded.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "Spiking", false, "Boss/grimm_spikes_pt_2_shoot_up.wav");
	CResourceManager::GetInst()->LoadSound("Effect", "SpikeEnd", false, "Boss/grimm_spikes_pt_3_shrivel_back.wav");

	//CResourceManager::GetInst()->SoundPlay("SpikeStart");
}

bool CGrimmSpike::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderBox2D>("GrimmSpike");
	m_Sprite = CreateComponent<CSpriteComponent>("GrimmSpikeSprite");

	SetRootComponent(m_Body);
	m_Body->AddChild(m_Sprite);
	m_Body->SetEnable(false);

	m_Body->SetBoxSize(50.f, 2000.f);
	m_Body->SetCollisionProfile("MonsterAttack");

	m_Sprite->SetAnimationFile("GrimmBullet");
	m_Anim = m_Sprite->GetAnimation();
	m_Anim->SetCurrentAnimation("Grimm SpikeEffect");
	m_Anim->SetPlayScale("Grimm SpikeEffect", 3.f);
	m_Anim->SetPlayScale("Grimm SpikeUp", 3.f);
	m_Anim->SetLoop("Grimm SpikeUp", false);

	m_Anim->SetPlayScale("Grimm SpikeDown", 5.f);
	m_Anim->SetCurrentEndFunction<CGrimmSpike>("Grimm SpikeDown", this, &CGrimmSpike::SpikeEndFunc);

	
	m_Sprite->SetPivot(0.5f, 0.f);
	m_Sprite->SetWorldScale(148.f *g_SCALE, 569.f*g_SCALE);
	m_Sprite->SetWorldPosition(0.f, -30.f);

	m_Time = 0.f;
	SetLifeTime(3.f);
	return true;
}

void CGrimmSpike::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	m_Time += DeltaTime;

	if (m_Time >= 0.9f)
	{
		if (!m_SpikeStart)
		{
			m_Sprite->SetWorldScale(148.f * g_SCALE, 977.f * g_SCALE);
			m_Anim->SetCurrentAnimation("Grimm SpikeUp");
			m_Sprite->SetWorldPositionY(-900.f);
			m_SpikeStart = true;
			m_Body->SetEnable(true);
			
		}

		if (m_SpikeDown == false)
		{
			if (m_Sprite->GetWorldPos().y >= -150.f)
				m_Sprite->SetWorldPositionY(-150.f);
			else
				m_Sprite->AddWorldPositionY(20.f);
		}

		if (m_Time >= 1.5f)
		{
			if (!m_SpikeDown)
			{
				m_Anim->SetCurrentAnimation("Grimm SpikeDown");
			}
				

			m_SpikeDown = true;
			m_Body->SetEnable(false);		
		}
	}	
}

void CGrimmSpike::SpikeEndFunc()
{
	Destroy();
}
