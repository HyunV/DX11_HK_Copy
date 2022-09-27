#include "ColliderBox2D.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Render/RenderManager.h"
#include "../Resource/Material/Material.h"
#include "../Engine.h"

CColliderBox2D::CColliderBox2D()
{
	SetTypeID<CColliderBox2D>();

	m_ComponentTypeName = "ColliderBox2D";
	m_Collider2DType = ECollider2D_Type::Box2D;
	m_BoxSize.x = 100.f;
	m_BoxSize.y = 100.f;
}

CColliderBox2D::CColliderBox2D(const CColliderBox2D& component) :
	CCollider2D(component)
{
	m_BoxSize = component.m_BoxSize;
}

CColliderBox2D::~CColliderBox2D()
{
}

void CColliderBox2D::Start()
{
	CCollider2D::Start();
}

bool CColliderBox2D::Init()
{
	if (!CCollider2D::Init())
		return false;

	return true;
}

void CColliderBox2D::Update(float DeltaTime)
{
	CCollider2D::Update(DeltaTime);
}

void CColliderBox2D::PostUpdate(float DeltaTime)
{
	CCollider2D::PostUpdate(DeltaTime);
}

void CColliderBox2D::Render()
{
	CCollider2D::Render();
}

CColliderBox2D* CColliderBox2D::Clone() const
{
	return new CColliderBox2D(*this);
}

void CColliderBox2D::Save(FILE* File)
{
	CCollider2D::Save(File);
}

void CColliderBox2D::Load(FILE* File)
{
	CCollider2D::Load(File);
}
