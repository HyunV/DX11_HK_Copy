#include "ColliderPixel.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/CameraManager.h"
#include "../Render/RenderManager.h"
#include "../Resource/Material/Material.h"
#include "../Engine.h"
#include "../Resource/ResourceManager.h"
#include "CameraComponent.h"
#include "../Resource/Shader/ColliderConstantBuffer.h"
#include "../CollisionManager.h"
#include "ColliderBox2D.h"
#include "ColliderOBB2D.h"
#include "ColliderSphere2D.h"

CColliderPixel::CColliderPixel()
{
	SetTypeID<CColliderPixel>();

	m_ComponentTypeName = "ColliderPixel";
	m_Collider2DType = ECollider2D_Type::Pixel;
}

CColliderPixel::CColliderPixel(const CColliderPixel& component) :
	CCollider2D(component)
{
}

CColliderPixel::~CColliderPixel()
{
}

void CColliderPixel::Start()
{
	CCollider2D::Start();
}

bool CColliderPixel::Init()
{
	if (!CCollider2D::Init())
		return false;

	return true;
}

void CColliderPixel::Update(float DeltaTime)
{
	CCollider2D::Update(DeltaTime);
}

void CColliderPixel::PostUpdate(float DeltaTime)
{
	CCollider2D::PostUpdate(DeltaTime);
}

void CColliderPixel::Render()
{
	CCollider2D::Render();
}

CColliderPixel* CColliderPixel::Clone() const
{
	return new CColliderPixel(*this);
}

void CColliderPixel::Save(FILE* File)
{
	CCollider2D::Save(File);
}

void CColliderPixel::Load(FILE* File)
{
	CCollider2D::Load(File);
}

bool CColliderPixel::Collision(CCollider* Dest)
{
	return false;
}
