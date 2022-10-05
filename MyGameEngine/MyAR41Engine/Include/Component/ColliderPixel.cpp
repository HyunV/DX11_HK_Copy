#include "ColliderPixel.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/CameraManager.h"
#include "../Scene/SceneCollision.h"
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
#include "../Device.h"

CColliderPixel::CColliderPixel() :
	m_Info(nullptr)
{
	SetTypeID<CColliderPixel>();

	m_ComponentTypeName = "ColliderPixel";
	m_Collider2DType = ECollider2D_Type::Pixel;
}

CColliderPixel::CColliderPixel(const CColliderPixel& component) :
	CCollider2D(component)
{
	m_Info = component.m_Info;

	++m_Info->RefCount;

	m_PixelMesh = component.m_PixelMesh;
	m_PixelShader = component.m_PixelShader;
}

CColliderPixel::~CColliderPixel()
{
	if (m_Info)
	{
		--m_Info->RefCount;

		if (m_Info->RefCount == 0)
		{
			SAFE_RELEASE(m_Info->SRV);
			SAFE_DELETE_ARRAY(m_Info->Pixel);
			SAFE_DELETE(m_Info);
		}
	}
}

void CColliderPixel::Start()
{
	CCollider2D::Start();
}

bool CColliderPixel::Init()
{
	if (!CCollider2D::Init())
		return false;


	if (CEngine::GetEditorMode())
	{
		m_Mesh = CResourceManager::GetInst()->FindMesh("Box2DLineMesh");
		m_PixelMesh = CResourceManager::GetInst()->FindMesh("CenterUVRect");
		m_PixelShader = CResourceManager::GetInst()->FindShader("ColliderImageShader");
	}

	return true;
}

void CColliderPixel::Update(float DeltaTime)
{
	CCollider2D::Update(DeltaTime);
}

void CColliderPixel::PostUpdate(float DeltaTime)
{
	CCollider2D::PostUpdate(DeltaTime);

	Vector2	Size = Vector2((float)m_Info->Width, (float)m_Info->Height);
	Size.x *= GetWorldScale().x;
	Size.y *= GetWorldScale().y;

	m_Min.x = GetWorldPos().x - Size.x * 0.5f;
	m_Min.y = GetWorldPos().y - Size.y * 0.5f;

	m_Max.x = m_Min.x + Size.x;
	m_Max.y = m_Min.y + Size.y;

	m_Info->Box2D.Left = m_Min.x;
	m_Info->Box2D.Bottom = m_Min.y;
	m_Info->Box2D.Right = m_Max.x;
	m_Info->Box2D.Top = m_Max.y;
}

void CColliderPixel::Render()
{
	CCollider2D::Render();

	Matrix	matScale, matTranslate, matWorld;

	Matrix	matView = m_Scene->GetCameraManager()->GetCurrentCamera()->GetViewMatrix();
	Matrix	matProj = m_Scene->GetCameraManager()->GetCurrentCamera()->GetProjMatrix();

	Vector3	Scale = Vector3((float)m_Info->Width, (float)m_Info->Height, 1.f);
	Scale.x *= GetWorldScale().x;
	Scale.y *= GetWorldScale().y;
	Scale.z = GetWorldScale().z;

	matScale.Scaling(Scale);
	matTranslate.Translation(GetWorldPos());

	matWorld = matScale * matTranslate;

	CColliderConstantBuffer* Buffer = CResourceManager::GetInst()->GetColliderCBuffer();

	Buffer->SetColor(m_Color);
	Buffer->SetWVP(matWorld * matView * matProj);

	Buffer->UpdateBuffer();

	CDevice::GetInst()->GetContext()->PSSetShaderResources(0, 1, &m_Info->SRV);

	m_PixelShader->SetShader();

	m_PixelMesh->Render();



	m_Shader->SetShader();

	m_Mesh->Render();
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
	Vector2	HitPoint;
	bool	Result = false;

	switch (((CCollider2D*)Dest)->GetCollider2DType())
	{
	case ECollider2D_Type::Box2D:
		Result = CCollisionManager::GetInst()->CollisionBox2DToPixel(HitPoint, (CColliderBox2D*)Dest, this);
		break;
	case ECollider2D_Type::OBB2D:
		Result = CCollisionManager::GetInst()->CollisionOBB2DToPixel(HitPoint, (CColliderOBB2D*)Dest, this);
		break;
	case ECollider2D_Type::Sphere2D:
		Result = CCollisionManager::GetInst()->CollisionSphere2DToPixel(HitPoint, (CColliderSphere2D*)Dest, this);
		break;
	case ECollider2D_Type::Pixel:
		Result = CCollisionManager::GetInst()->CollisionPixelToPixel(HitPoint, this, (CColliderPixel*)Dest);
		break;
	}

	m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);

	return Result;
}

bool CColliderPixel::CollisionMouse(const Vector2& MouseWorldPos)
{
	Vector2	HitPoint;

	m_MouseCollision = CCollisionManager::GetInst()->CollisionPointToPixel(HitPoint, MouseWorldPos,
		*m_Info);

	m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);

	return m_MouseCollision;
}

void CColliderPixel::SetInfo(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	if (!m_Scene->GetCollisionManager()->CreatePixelCollision(Name, FileName, PathName))
		return;

	m_Info = m_Scene->GetCollisionManager()->FindPixelCollision(Name);
	++m_Info->RefCount;
}

void CColliderPixel::SetInfoFullPath(const std::string& Name, const TCHAR* FullPath)
{
	if (!m_Scene->GetCollisionManager()->CreatePixelCollisionFullPath(Name, FullPath))
		return;

	m_Info = m_Scene->GetCollisionManager()->FindPixelCollision(Name);
	++m_Info->RefCount;
}

void CColliderPixel::SetInfoMultibyte(const std::string& Name, const char* FileName, const std::string& PathName)
{
	if (!m_Scene->GetCollisionManager()->CreatePixelCollisionMultibyte(Name, FileName, PathName))
		return;

	m_Info = m_Scene->GetCollisionManager()->FindPixelCollision(Name);
	++m_Info->RefCount;
}

void CColliderPixel::SetInfoMultibyteFullPath(const std::string& Name, const char* FullPath)
{
	if (!m_Scene->GetCollisionManager()->CreatePixelCollisionMultibyteFullPath(Name, FullPath))
		return;

	m_Info = m_Scene->GetCollisionManager()->FindPixelCollision(Name);
	++m_Info->RefCount;
}

void CColliderPixel::SetPixelColorCollisionType(EPixelCollision_Type Type)
{
	if (!m_Info)
		return;

	m_Info->PixelColorCollisionType = Type;
}

void CColliderPixel::SetPixelAlphaCollisionType(EPixelCollision_Type Type)
{
	if (!m_Info)
		return;

	m_Info->PixelAlphaCollisionType = Type;
}

void CColliderPixel::SetPixelColor(unsigned char r, unsigned char g, unsigned char b)
{
	if (!m_Info)
		return;

	m_Info->TypeColor[0] = r;
	m_Info->TypeColor[1] = g;
	m_Info->TypeColor[2] = b;
}

void CColliderPixel::SetPixelAlpha(unsigned char a)
{
	if (!m_Info)
		return;

	m_Info->TypeColor[3] = a;
}
