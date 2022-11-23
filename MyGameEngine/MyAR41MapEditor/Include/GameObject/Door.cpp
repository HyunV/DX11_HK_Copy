#include "Door.h"

#include "Component/ColliderBox2D.h"
#include "Scene/SceneManager.h"
#include "PathManager.h"

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

void CDoor::CollisionBegin(const CollisionResult& Result)
{
	OutputDebugStringA(Result.Src->GetName().c_str()); //door2
	OutputDebugStringA(Result.Dest->GetName().c_str());

	std::string SceneName = Result.Src->GetName();

	CSceneManager::GetInst()->CreateNextScene();

	char Name[256] = {};
	const PathInfo* Path = CPathManager::GetInst()->FindPath(SCENE_PATH);
	strcat_s(Name, Path->PathMultibyte);
	strcat_s(Name, SceneName.c_str());
	strcat_s(Name, ".scn");

	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();
	NextScene->Load(Name);

	CSceneManager::GetInst()->ChangeNextScene();

}
