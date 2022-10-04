#include "SectionComponent.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/SceneManager.h"
#include "CameraComponent.h"
#include "../Resource/Shader/ColliderConstantBuffer.h"
#include "../Scene/CollisionSection2D.h"
#include "../Render/RenderManager.h"

CSectionComponent::CSectionComponent()
{
}

CSectionComponent::~CSectionComponent()
{
}

bool CSectionComponent::Init()
{
	if (!CSceneComponent::Init())
		return false;

	m_Mesh = CResourceManager::GetInst()->FindMesh("Box2DLineMesh");
	m_Shader = CResourceManager::GetInst()->FindShader("ColliderShader");
	m_Color = Vector4(0.f, 0.f, 1.f, 1.f);
	m_Scene = CSceneManager::GetInst()->GetScene();
	m_vecSection = m_Scene->GetCollisionManager()->GetSection()->vecSection;
	
	return true;
}

void CSectionComponent::Start()
{
	CSceneComponent::Start();
	CRenderManager::GetInst()->AddRenderList(this);
}

void CSectionComponent::PostUpdate(float DeltaTime)
{
	//
}

void CSectionComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CSectionComponent::Render()
{
	CSceneComponent::Render();
	
	Matrix	matScale, matTranslate, matWorld;

	Matrix	matView = m_Scene->GetCameraManager()->GetCurrentCamera()->GetViewMatrix();
	Matrix	matProj = m_Scene->GetCameraManager()->GetCurrentCamera()->GetProjMatrix();
	


	for (int i = 0; i < m_vecSection.size(); i++)
	{
		Vector3	Scale = GetWorldScale();

		Vector2 vSectionSize = m_Scene->GetCollisionManager()->GetSection()->SectionSize;

		Vector2 vMin = m_vecSection[i]->GetMin();
		Vector2 vMax = m_vecSection[i]->GetMax();

		Vector2 Size = vSectionSize;
		Size.x *= GetWorldScale().x;
		Size.y *= GetWorldScale().y;

		vMin.x = GetWorldPos().x - Size.x * 0.5f;
		vMin.y = GetWorldPos().y - Size.y * 0.5f;

		vMax.x = vMin.x + Size.x;
		vMax.y = vMin.y + Size.y;

		Scale.x *= vSectionSize.x;
		Scale.y *= vSectionSize.y;

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


}
