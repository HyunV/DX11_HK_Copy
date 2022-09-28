#include "ColliderSphere2D.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Render/RenderManager.h"
#include "../Resource/Material/Material.h"
#include "../Engine.h"

CColliderSphere2D::CColliderSphere2D()
{
	SetTypeID<CColliderSphere2D>();

	m_ComponentTypeName = "ColliderSphere2D";
	m_Collider2DType = ECollider2D_Type::Sphere2D;
}

CColliderSphere2D::CColliderSphere2D(const CColliderSphere2D& component) :
	CCollider2D(component)
{
}

CColliderSphere2D::~CColliderSphere2D()
{
}

void CColliderSphere2D::Start()
{
	CCollider2D::Start();
}

bool CColliderSphere2D::Init()
{
	if (!CCollider2D::Init())
		return false;

	return true;
}

void CColliderSphere2D::Update(float DeltaTime)
{
	CCollider2D::Update(DeltaTime);
}

void CColliderSphere2D::PostUpdate(float DeltaTime)
{
	CCollider2D::PostUpdate(DeltaTime);
}

void CColliderSphere2D::Render()
{
	CCollider2D::Render();
}

CColliderSphere2D* CColliderSphere2D::Clone() const
{
	return new CColliderSphere2D(*this);
}

void CColliderSphere2D::Save(FILE* File)
{
	CCollider2D::Save(File);
}

void CColliderSphere2D::Load(FILE* File)
{
	CCollider2D::Load(File);
}

bool CColliderSphere2D::Collision(CCollider* Dest)
{
	return false;
}
