#include "BossEventObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Scene/Scene.h"
#include <time.h>
#include "../UI/NightMareKingUI.h"
#include "Zombie.h"
#include "NightMareKingGrimm.h"
#include "Player2D.h"
#include "FlameParticle.h"

#include "Scene/SceneManager.h"
#include "PathManager.h"

CBossEventObject::CBossEventObject()
{
	SetTypeID<CBossEventObject>();

	m_ObjectTypeName = "BossEventObject";
}

CBossEventObject::CBossEventObject(const CBossEventObject& Obj)	:
	CGameObject(Obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("GrimmHeartSprite");
	m_GrimmSprite = (CSpriteComponent*)FindComponent("GrimmSprite");
	m_Body = (CColliderBox2D*)FindComponent("EventBody"); //루트
}

CBossEventObject::~CBossEventObject()
{
	CResourceManager::GetInst()->SoundStop("Grimm");
}

void CBossEventObject::Start()
{
	CGameObject::Start();
	CResourceManager::GetInst()->LoadSound("BGM", "Grimm", true, "Nightmare King Grimm - S87-168 Nightmare Grimm.wav");
	CResourceManager::GetInst()->LoadSound("BGM", "GrimmEnding", false, "Nightmare King Grimm ending - S87-168 Nightmare Grimm Optional Ending.wav");
	CResourceManager::GetInst()->LoadSound("BGM", "GrimmHeart", true, "menu_heartbeat.wav");


	CResourceManager::GetInst()->LoadSound("BGM", "Event1", false, "Boss/Nightmare King Grimm/nightmare_bg_eye_break_1.wav");
	CResourceManager::GetInst()->LoadSound("BGM", "Event2", false, "Boss/Nightmare King Grimm/nightmare_bg_eye_break_2.wav");
	CResourceManager::GetInst()->LoadSound("BGM", "Event3", false, "Boss/Nightmare King Grimm/nightmare_bg_eye_break_3.wav");
	

	m_Body->SetCollisionCallback(ECollision_Result::Collision, this, &CBossEventObject::CollisionBegin);

	CResourceManager::GetInst()->SoundPlay("GrimmHeart");
}

bool CBossEventObject::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("GrimmHeartSprite");
	m_GrimmSprite = CreateComponent<CSpriteComponent>("GrimmSprite");
	m_Body = CreateComponent<CColliderBox2D>("EventBody");
	m_Body->SetName("EventBody");

	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_GrimmSprite);
	m_Sprite->AddChild(m_Body);

	m_Sprite->SetPivot(0.5f, 0.5f);
	m_Sprite->SetTexture("GrimmHeart1", TEXT("HollowKnight/Boss/Event/core1.png"));
	m_Sprite->SetWorldScale(147.f, 649.f);
	m_Sprite->SetWorldPosition(630.f, 380.f);
	m_Sprite->SetEnable(false);

	//m_Sprite->SetPivot(0.5f, 0.5f);
	//m_Sprite->SetTexture("GrimmHeart2", TEXT("HollowKnight/Boss/Event/core2.png"));
	//m_Sprite->SetWorldScale(300.f, 500.f);
	//m_Sprite->SetWorldPosition(640.f, 450.f);

	m_GrimmSprite->SetPivot(0.5f, 0.5f);
	m_GrimmSprite->SetTexture("GrimmAppear", TEXT("HollowKnight/Boss/Event/GrimmAppear.png"));
	m_GrimmSprite->SetWorldScale(81.f, 146.f);
	m_GrimmSprite->SetWorldPosition(640.f, 380.f);
	m_GrimmSprite->GetMaterial(0)->SetOpacity(0.f);
	m_GrimmSprite->SetRenderLayerName("Effect");

	m_Body->SetWorldPosition(400.f, 360.f);
	m_Body->SetBoxSize(1.f, 720.f);
	m_Body->SetCollisionProfile("NPC");

	m_CurEvent = EEventState::None;

	return true;
}

void CBossEventObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_Ending)
	{
		m_Time += DeltaTime;

		if (m_Time >= 5.f)
		{
			m_Ending = false;
			m_Time = 0.f;
			EndingScene();
		}
			
	}

	if (m_CreateGrimm)
	{
		if (m_Grim->GetDeath())
		{
			CResourceManager::GetInst()->SoundPlay("GrimmEnding");
			m_CreateGrimm = false;
			m_Ending = true;
		}
	}


	if (m_EventStart)
	{
		m_Time += DeltaTime;

		if (m_Time >= 1.f && m_CurEvent == EEventState::Event1)
		{
			m_Sprite->SetTexture("GrimmHeart2", TEXT("HollowKnight/Boss/Event/core2.png"));
			m_Sprite->SetWorldScale(300.f, 500.f);
			m_Sprite->SetWorldPosition(640.f, 430.f);
			CResourceManager::GetInst()->SoundPlay("Event2");
			m_CurEvent = EEventState::Event2;
		}


		if (m_Time >= 2.f && m_CurEvent == EEventState::Event2)
		{
			m_Sprite->SetEnable(false);
			CResourceManager::GetInst()->SoundPlay("Event3");
			m_CurEvent = EEventState::Event3;

			m_GrimmSprite->SetWorldScale(81.f, 146.f);
			m_GrimmSprite->SetWorldPosition(640.f, 380.f);
			
		}

		if (m_Time >= 2.f && m_Time < 4.f && m_CurEvent == EEventState::Event3)
		{
			CreateFireEffect(0.f);

			if (m_Time >= 3.f && m_Time < 4.f)
				m_GrimmSprite->GetMaterial(0)->AddOpacity(DeltaTime);
		}

		if (m_Time >= 4.f && m_CurEvent == EEventState::Event3)
		{
			CResourceManager::GetInst()->SoundPlay("Grimm");
			m_Scene->GetViewport()->CreateUIWindow<CNightMareKingUI>("NightMareKing");
			m_CurEvent = EEventState::Finish;
			m_GrimmSprite->SetEnable(false);
		}

		if (m_Time > 8.f && m_CurEvent == EEventState::Finish)
		{			
			m_Grim = m_Scene->CreateObject<CNightMareKingGrimm>("NightMareKingGrimm");
			m_EventStart = false;
			CPlayer2D* player = (CPlayer2D*)(m_Scene->FindObject("Player2D"));
			player->m_KeyLock = false;
			player->SetNextState();
			player->ResetCamera();

			m_CreateGrimm = true;
			m_Time = 0.f;
		}
	}
}

void CBossEventObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBossEventObject* CBossEventObject::Clone() const
{
	return new CBossEventObject(*this);
}

void CBossEventObject::CollisionBegin(const CollisionResult& Result)
{
	std::string dest = Result.Dest->GetCollisionProfile()->Name;
	if (dest == "Player")
	{
		m_Body->SetEnable(false);
		m_Sprite->SetEnable(true);
		CResourceManager::GetInst()->SoundStop("GrimmHeart");
		CResourceManager::GetInst()->SoundPlay("Event1");
		m_CurEvent = EEventState::Event1;
		m_EventStart = true;
	}
		
}

void CBossEventObject::CreateFireEffect(float z)
{
	CFlameParticle* Particle = m_Scene->CreateObject<CFlameParticle>("particle");
	Particle->SetWorldPosition(GetWorldPos());

	int angle = rand() % 360;
	Particle->AddWorldRotationZ((float)angle);
	
}

void CBossEventObject::EndingScene()
{
	OutputDebugStringA("엔딩");

	//메인타이틀 이동
	CSceneManager::GetInst()->CreateNextScene();

	char Name[256] = {};
	const PathInfo* Path = CPathManager::GetInst()->FindPath(SCENE_PATH);
	strcat_s(Name, Path->PathMultibyte);
	strcat_s(Name, "HollowEnding");
	strcat_s(Name, ".scn");

	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();
	NextScene->Load(Name);

	CSceneManager::GetInst()->ChangeNextScene();

}
