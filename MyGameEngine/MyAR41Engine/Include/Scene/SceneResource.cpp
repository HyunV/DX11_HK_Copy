#include "SceneResource.h"

CSceneResource::CSceneResource()
{
}

CSceneResource::~CSceneResource()
{
	{
		auto	iter = m_mapMesh.begin();
		auto	iterEnd = m_mapMesh.end();

		for (; iter != iterEnd;)
		{
			std::string	Name = iter->first;

			iter = m_mapMesh.erase(iter);
			iterEnd = m_mapMesh.end();

			CResourceManager::GetInst()->ReleaseMesh(Name);
		}
	}
	{
		auto	iter = m_mapShader.begin();
		auto	iterEnd = m_mapShader.end();

		for (; iter != iterEnd;)
		{
			std::string	Name = iter->first;

			iter = m_mapShader.erase(iter);
			iterEnd = m_mapShader.end();

			CResourceManager::GetInst()->ReleaseShader(Name);
		}
	}

	{
		auto	iter = m_mapTexture.begin();
		auto	iterEnd = m_mapTexture.end();

		for (; iter != iterEnd;)
		{
			std::string	Name = iter->first;

			iter = m_mapTexture.erase(iter);
			iterEnd = m_mapTexture.end();

			CResourceManager::GetInst()->ReleaseTexture(Name);
		}
	}
}

bool CSceneResource::Init()
{
	return true;
}

bool CSceneResource::CreateMesh(MeshType Type, const std::string& Name, void* VtxData, 
	int Size, int Count, D3D11_USAGE VtxUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
	void* IdxData, int IdxSize, int IdxCount, D3D11_USAGE IdxUsage, DXGI_FORMAT Fmt)
{
	if (FindMesh(Name))
		return true;

	if (!CResourceManager::GetInst()->CreateMesh(m_Owner, Type, Name, VtxData, Size, Count,
		VtxUsage, Primitive, IdxData, IdxSize,
		IdxCount, IdxUsage, Fmt))
		return false;

	m_mapMesh.insert(std::make_pair(Name, CResourceManager::GetInst()->FindMesh(Name)));

	return true;
}

CMesh* CSceneResource::FindMesh(const std::string& Name)
{
	auto	iter = m_mapMesh.find(Name);

	if (iter == m_mapMesh.end())
	{
		CMesh* Mesh = CResourceManager::GetInst()->FindMesh(Name);

		if (!Mesh)
			return nullptr;

		m_mapMesh.insert(std::make_pair(Name, Mesh));

		return Mesh;
	}

	return iter->second;
}

CShader* CSceneResource::FindShader(const std::string& Name)
{
	auto	iter = m_mapShader.find(Name);

	if (iter == m_mapShader.end())
	{
		CShader* Shader = CResourceManager::GetInst()->FindShader(Name);

		if (!Shader)
			return nullptr;

		m_mapShader.insert(std::make_pair(Name, Shader));

		return Shader;
	}

	return iter->second;
}

bool CSceneResource::LoadTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	if (FindTexture(Name))
		return true;

	if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		return false;

	m_mapTexture.insert(std::make_pair(Name, CResourceManager::GetInst()->FindTexture(Name)));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	if (FindTexture(Name))
		return true;

	if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath))
		return false;

	m_mapTexture.insert(std::make_pair(Name, CResourceManager::GetInst()->FindTexture(Name)));

	return true;
}

bool CSceneResource::LoadTexture(const std::string& Name, 
	const std::vector<const TCHAR*>& vecFileName, const std::string& PathName)
{
	if (FindTexture(Name))
		return true;

	if (!CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName))
		return false;

	m_mapTexture.insert(std::make_pair(Name, CResourceManager::GetInst()->FindTexture(Name)));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& Name,
	const std::vector<const TCHAR*>& vecFullPath)
{
	if (FindTexture(Name))
		return true;

	if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, vecFullPath))
		return false;

	m_mapTexture.insert(std::make_pair(Name, CResourceManager::GetInst()->FindTexture(Name)));

	return true;
}

CTexture* CSceneResource::FindTexture(const std::string& Name)
{
	auto	iter = m_mapTexture.find(Name);

	if (iter == m_mapTexture.end())
	{
		CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

		if (!Texture)
			return nullptr;

		m_mapTexture.insert(std::make_pair(Name, Texture));

		return Texture;
	}

	return iter->second;
}

CMaterial* CSceneResource::FindMaterial(const std::string& Name)
{
	auto	iter = m_mapMaterial.find(Name);

	if (iter == m_mapMaterial.end())
	{
		CMaterial* Material = CResourceManager::GetInst()->FindMaterial(Name);

		if (!Material)
			return nullptr;

		m_mapMaterial.insert(std::make_pair(Name, Material));

		return Material;
	}

	return iter->second;
}
