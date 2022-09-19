
#include "SpriteComponent.h"
#include "../Resource/Material/Material.h"

CSpriteComponent::CSpriteComponent()
{
	SetTypeID<CSpriteComponent>();

	m_ComponentTypeName = "SpriteComponent";
}

CSpriteComponent::CSpriteComponent(const CSpriteComponent& component) :
	CPrimitiveComponent(component)
{
}

CSpriteComponent::~CSpriteComponent()
{
}

bool CSpriteComponent::SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTexture(0, 0, (int)EShaderBufferType::Pixel, Name, FileName, PathName);

	return true;
}

bool CSpriteComponent::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTextureFullPath(0, 0, (int)EShaderBufferType::Pixel, Name, FullPath);

	return true;
}

bool CSpriteComponent::SetTexture(const std::string& Name, const std::vector<const TCHAR*>& vecFileName, const std::string& PathName)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTexture(0, 0, (int)EShaderBufferType::Pixel, Name, vecFileName, PathName);

	return true;
}

bool CSpriteComponent::SetTexture(const std::string& Name)
{
	return false;
}

bool CSpriteComponent::SetTextureFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTextureFullPath(0, 0, (int)EShaderBufferType::Pixel, Name, vecFullPath);

	return true;
}

CTexture* CSpriteComponent::GetTexture(int Index) const
{
	if (m_vecMaterial.empty())
		return nullptr;

	return m_vecMaterial[0]->GetTexture(Index);
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

void CSpriteComponent::Save(FILE* File)
{
	CPrimitiveComponent::Save(File);
}

void CSpriteComponent::Load(FILE* File)
{
	CPrimitiveComponent::Load(File);
}
