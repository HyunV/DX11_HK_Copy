#include "ColliderOBB2D.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Render/RenderManager.h"
#include "../Resource/Material/Material.h"
#include "../Engine.h"

CColliderOBB2D::CColliderOBB2D()
{
	SetTypeID<CColliderOBB2D>();

	m_ComponentTypeName = "ColliderOBB2D";
	m_Collider2DType = ECollider2D_Type::OBB2D;
}

CColliderOBB2D::CColliderOBB2D(const CColliderOBB2D& component) :
	CCollider2D(component)
{
}

CColliderOBB2D::~CColliderOBB2D()
{
}

void CColliderOBB2D::Start()
{
	CCollider2D::Start();
}

bool CColliderOBB2D::Init()
{
	if (!CCollider2D::Init())
		return false;

	return true;
}

void CColliderOBB2D::Update(float DeltaTime)
{
	CCollider2D::Update(DeltaTime);
}

void CColliderOBB2D::PostUpdate(float DeltaTime)
{
	CCollider2D::PostUpdate(DeltaTime);
}

void CColliderOBB2D::Render()
{
	CCollider2D::Render();
}

CColliderOBB2D* CColliderOBB2D::Clone() const
{
	return new CColliderOBB2D(*this);
}

void CColliderOBB2D::Save(FILE* File)
{
	CCollider2D::Save(File);
}

void CColliderOBB2D::Load(FILE* File)
{
	CCollider2D::Load(File);
}

bool CColliderOBB2D::Collision(CCollider* Dest)
{
	return false;
}
