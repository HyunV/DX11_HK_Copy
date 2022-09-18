
#include "Component.h"

CComponent::CComponent()	:
	m_Scene(nullptr),
	m_Owner(nullptr)
{
	SetTypeID<CComponent>();

	m_ComponentTypeName = "Component";
}

CComponent::CComponent(const CComponent& Obj)	:
	CRef(Obj)
{
	m_ComponentType = Obj.m_ComponentType;
	m_ComponentTypeName = Obj.m_ComponentTypeName;
}

CComponent::~CComponent()
{
}

void CComponent::Destroy()
{
	CRef::Destroy();
}

void CComponent::Start()
{
}

bool CComponent::Init()
{
	return true;
}

void CComponent::Update(float DeltaTime)
{
}

void CComponent::PostUpdate(float DeltaTime)
{
}

void CComponent::Render()
{
}

CComponent* CComponent::Clone() const
{
	return nullptr;
}

void CComponent::Save(FILE* File)
{
	CRef::Save(File);

	fwrite(&m_ComponentType, sizeof(ComponentType), 1, File);

	int Length = (int)m_ComponentTypeName.length();

	fwrite(&Length, 4, 1, File);
	fwrite(m_ComponentTypeName.c_str(), 1, Length, File);
}

void CComponent::Load(FILE* File)
{
	CRef::Load(File);
}
