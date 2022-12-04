#include "Door.h"

#include "Component/ColliderBox2D.h"
#include "Scene/SceneManager.h"
#include "PathManager.h"
#include "Player2D.h"
#include "MonGenerator.h"
#include "MyGameManager.h"
#include "../UI/PlayerHUD.h"

CDoor::CDoor()
{
	SetTypeID<CDoor>();

	m_ObjectTypeName = "Door";
}

CDoor::CDoor(const CDoor& Obj)	:
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Body");
}

CDoor::~CDoor()
{

}

void CDoor::Start()
{
	CGameObject::Start();
	m_Body->SetCollisionCallback(ECollision_Result::Collision, this, &CDoor::CollisionBegin);
}

bool CDoor::Init()
{
	CGameObject::Init();
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Body->SetBoxSize(50.f, 100.f);
	m_Body->SetCollisionProfile("Door");
	SetRootComponent(m_Body);

	return true;
}

void CDoor::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CDoor::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDoor* CDoor::Clone() const
{
	return new CDoor(*this);
}

void CDoor::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CDoor::Load(FILE* File)
{
	CGameObject::Load(File);
}

void CDoor::ChangeScene(std::string& SceneName)
{
	/*
		01.TOWN
		02.ARENA
		03.SHOP
		04.BOSS
	*/
	CSceneManager::GetInst()->CreateNextScene();

	std::string Map = "";

	if (SceneName == "TownToArena")
	{
		m_DoorName = EDoorName::TownToArena;
		Map = "02.ARENA";
	}
	else if (SceneName == "TownToShop")
	{
		m_DoorName = EDoorName::TownToShop;
		Map = "03.SHOP";
	}
	else if (SceneName == "TownToBoss")
	{
		m_DoorName = EDoorName::TownToBoss;
		Map = "04.BOSS";
	}
	else if (SceneName == "ArenaToTown")
	{
		m_DoorName = EDoorName::ArenaToTown;
		Map = "01.TOWN";
	}
	else if (SceneName == "ShopToTown")
	{
		m_DoorName = EDoorName::ShopToTown;
		Map = "01.TOWN";
	}
	else if (SceneName == "BossToTown")
	{
		m_DoorName = EDoorName::BossToTown;
		Map = "01.TOWN";
	}
	else
		return;

	char Name[256] = {};
	const PathInfo* Path = CPathManager::GetInst()->FindPath(SCENE_PATH);
	strcat_s(Name, Path->PathMultibyte);
	strcat_s(Name, Map.c_str());
	strcat_s(Name, ".scn");


	//씬로드
	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();
	NextScene->Load(Name);

	CSceneManager::GetInst()->ChangeNextScene();

	SetPlayer(m_DoorName);
}

void CDoor::SetPlayer(EDoorName DoorName)
{
	CScene* Scene = CSceneManager::GetInst()->GetNextScene();
	CPlayer2D* Player = (CPlayer2D*)(Scene->FindObject("Player2D"));

	PlayerInfo Info = CMyGameManager::GetInst()->GetPlayerInfo();
	
	Player->m_MaxHP = Info.MaxHP;
	Player->m_HP = Info.HP;
	Player->m_Gio = Info.Gio;

	//CPlayerHUD* HUD = Scene->GetViewport()->FindUIWindow<CPlayerHUD>("PlayerHUD");
	//HUD->CreateEmptyHeart();
	//HUD->CreateHeart(Player->m_HP);

	switch (DoorName)
	{
	case CDoor::EDoorName::None:
		break;
	case CDoor::EDoorName::TownToArena:
	{
		CMonGenerator* Gen = (CMonGenerator*)(Scene->FindObject("MonGenerator"));
		Gen->StartGenerate(true);
	}
		
		break;
	case CDoor::EDoorName::TownToShop:
		break;
	case CDoor::EDoorName::TownToBoss:
		//Player->SetWorldPositionX(1500.f);
		break;
	case CDoor::EDoorName::ArenaToTown:
		Player->SetProstrate();
		break;
	case CDoor::EDoorName::ShopToTown:
		break;
	case CDoor::EDoorName::BossToTown:
		break;
	default:
		break;
	}
}

void CDoor::CollisionBegin(const CollisionResult& Result)
{
	//Src 이름 받아와서 그 씬으로 체인지
	//Dest는 플레이어
	OutputDebugStringA(Result.Src->GetName().c_str()); //door2
	OutputDebugStringA(Result.Dest->GetName().c_str());

	std::string s = Result.Dest->GetOwner()->GetName();

	if (s == "Player2D")
	{
		//CPlayer2D* Player = (CPlayer2D*)(Result.Dest->GetOwner());
		//std::string SceneName = Result.Src->GetName();
		//ChangeScene(SceneName);
	}
}
