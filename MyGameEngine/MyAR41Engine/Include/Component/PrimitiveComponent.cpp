
#include "PrimitiveComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Render/RenderManager.h"

CPrimitiveComponent::CPrimitiveComponent()
{
	SetTypeID<CPrimitiveComponent>();
}

CPrimitiveComponent::CPrimitiveComponent(const CPrimitiveComponent& component) :
	CSceneComponent(component)
{
}

CPrimitiveComponent::~CPrimitiveComponent()
{
}

void CPrimitiveComponent::SetMesh(const std::string& Name)
{
	m_Mesh = m_Scene->GetResource()->FindMesh(Name);

	if (m_Mesh)
		SetMeshSize(m_Mesh->GetMeshSize());
}

void CPrimitiveComponent::SetMesh(CMesh* Mesh)
{
	m_Mesh = Mesh;

	if (m_Mesh)
		SetMeshSize(m_Mesh->GetMeshSize());
}

void CPrimitiveComponent::SetShader(const std::string& Name)
{
	m_Shader = m_Scene->GetResource()->FindShader(Name);
}

void CPrimitiveComponent::Start()
{
	CSceneComponent::Start();

	// Scene에 배치가 되고 Start가 호출되면 출력 목록으로 지정한다.
	CRenderManager::GetInst()->AddRenderList(this);
}

bool CPrimitiveComponent::Init()
{
	if (!CSceneComponent::Init())
		return false;

	return true;
}

void CPrimitiveComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CPrimitiveComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CPrimitiveComponent::Render()
{
	CSceneComponent::Render();

	m_Shader->SetShader();

	m_Mesh->Render();
}

CPrimitiveComponent* CPrimitiveComponent::Clone() const
{
	return new CPrimitiveComponent(*this);
}
