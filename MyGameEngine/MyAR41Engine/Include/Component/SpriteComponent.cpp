
#include "SpriteComponent.h"

CSpriteComponent::CSpriteComponent()
{
	SetTypeID<CSpriteComponent>();
}

CSpriteComponent::CSpriteComponent(const CSpriteComponent& component) :
	CPrimitiveComponent(component)
{
}

CSpriteComponent::~CSpriteComponent()
{
}

void CSpriteComponent::Start()
{
	CPrimitiveComponent::Start();
}

bool CSpriteComponent::Init()
{
	if (!CPrimitiveComponent::Init())
		return false;

	SetMesh("LBUVRect");

	m_Transform->Set2D(true);

	return true;
}

void CSpriteComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);
}

void CSpriteComponent::PostUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostUpdate(DeltaTime);
}

void CSpriteComponent::Render()
{
	CPrimitiveComponent::Render();
}

CSpriteComponent* CSpriteComponent::Clone() const
{
	return new CSpriteComponent(*this);
}
