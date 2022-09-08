
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
