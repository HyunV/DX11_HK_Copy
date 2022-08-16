
#include "PrimitiveComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Render/RenderManager.h"
#include "../Resource/Material/Material.h"

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

	m_vecMaterial.clear();

	int SlotCount = m_Mesh->GetSlotCount();

	for (int i = 0; i < SlotCount; ++i)
	{
		CMaterial* Material = m_Mesh->GetMaterial(i);

		m_vecMaterial.push_back(Material->Clone());
	}
}

void CPrimitiveComponent::SetMesh(CMesh* Mesh)
{
	m_Mesh = Mesh;

	if (m_Mesh)
		SetMeshSize(m_Mesh->GetMeshSize());

	int SlotCount = m_Mesh->GetSlotCount();

	for (int i = 0; i < SlotCount; ++i)
	{
		CMaterial* Material = m_Mesh->GetMaterial(i);

		m_vecMaterial.push_back(Material->Clone());
	}
}

void CPrimitiveComponent::SetMaterial(int Slot, const std::string& Name)
{
	CMaterial* Material = m_Scene->GetResource()->FindMaterial(Name);

	m_vecMaterial[Slot] = Material;
}

void CPrimitiveComponent::SetMaterial(int Slot, CMaterial* Material)
{
	m_vecMaterial[Slot] = Material;
}

void CPrimitiveComponent::AddMaterial(const std::string& Name)
{
	CMaterial* Material = m_Scene->GetResource()->FindMaterial(Name);

	m_vecMaterial.push_back(Material);
}

void CPrimitiveComponent::AddMaterial(CMaterial* Material)
{
	m_vecMaterial.push_back(Material);
}

void CPrimitiveComponent::ClearMaterial()
{
	m_vecMaterial.clear();
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

	int	Size = (int)m_vecMaterial.size();

	for (int i = 0; i < Size; ++i)
	{
		m_vecMaterial[i]->SetMaterial();

		m_Mesh->Render(i);

		m_vecMaterial[i]->ResetMaterial();
	}
}

CPrimitiveComponent* CPrimitiveComponent::Clone() const
{
	return new CPrimitiveComponent(*this);
}
