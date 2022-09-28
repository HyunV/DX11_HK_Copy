#include "ColliderBox2D.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/CameraManager.h"
#include "../Render/RenderManager.h"
#include "../Resource/Material/Material.h"
#include "../Engine.h"
#include "../Resource/ResourceManager.h"
#include "CameraComponent.h"
#include "../Resource/Shader/ColliderConstantBuffer.h"

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

	if (CEngine::GetEditorMode())
	{
		m_Mesh = CResourceManager::GetInst()->FindMesh("Box2DLineMesh");
		m_Shader = CResourceManager::GetInst()->FindShader("ColliderShader");
	}

	return true;
}

void CColliderBox2D::Update(float DeltaTime)
{
	CCollider2D::Update(DeltaTime);
}

void CColliderBox2D::PostUpdate(float DeltaTime)
{
	CCollider2D::PostUpdate(DeltaTime);

	Vector2	Size = m_BoxSize;
	Size.x *= GetWorldScale().x;
	Size.y *= GetWorldScale().y;

	m_Min.x = GetWorldPos().x - Size.x * 0.5f;
	m_Min.y = GetWorldPos().y - Size.y * 0.5f;

	m_Max.x = m_Min.x + Size.x;
	m_Max.y = m_Min.y + Size.y;
}

void CColliderBox2D::Render()
{
	CCollider2D::Render();

	Matrix	matScale, matTranslate, matWorld;

	Matrix	matView = m_Scene->GetCameraManager()->GetCurrentCamera()->GetViewMatrix();
	Matrix	matProj = m_Scene->GetCameraManager()->GetCurrentCamera()->GetProjMatrix();

	Vector3	Scale = GetWorldScale();
	Scale.x *= m_BoxSize.x;
	Scale.y *= m_BoxSize.y;

	matScale.Scaling(Scale);
	matTranslate.Translation(GetWorldPos());

	matWorld = matScale * matTranslate;

	CColliderConstantBuffer* Buffer = CResourceManager::GetInst()->GetColliderCBuffer();

	Buffer->SetColor(m_Color);
	Buffer->SetWVP(matWorld * matView * matProj);

	Buffer->UpdateBuffer();

	m_Shader->SetShader();

	m_Mesh->Render();
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

bool CColliderBox2D::Collision(CCollider* Dest)
{
	return false;
}
