#include "ObjectComponent.h"

CObjectComponent::CObjectComponent()
{
	m_ComponentType = ComponentType::Object;

	SetTypeID<CObjectComponent>();
}

CObjectComponent::CObjectComponent(const CObjectComponent& Obj) :
	CComponent(Obj)
{
}

CObjectComponent::~CObjectComponent()
{
}

void CObjectComponent::Destroy()
{
}

void CObjectComponent::Start()
{
}

bool CObjectComponent::Init()
{
	return true;
}

void CObjectComponent::Update(float DeltaTime)
{
}

void CObjectComponent::PostUpdate(float DeltaTime)
{
}

void CObjectComponent::Render()
{
}

CObjectComponent* CObjectComponent::Clone() const
{
	return nullptr;
}
