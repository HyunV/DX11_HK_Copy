#pragma once

#include "../EngineInfo.h"
#include "../Resource/Mesh/Mesh.h"
#include "../Resource/Shader/Shader.h"
#include "../Resource/Texture/Texture.h"
#include "../Resource/Material/Material.h"
#include "../Resource/Animation/AnimationSequence2D.h"
#include "../Resource/ResourceManager.h"

class CSceneResource
{
	friend class CScene;

private:
	CSceneResource();
	~CSceneResource();

private:
	class CScene* m_Owner;

private:
	std::unordered_map<std::string, CSharedPtr<CMesh>>		m_mapMesh;
	std::unordered_map<std::string, CSharedPtr<CShader>>	m_mapShader;
	std::unordered_map<std::string, CSharedPtr<CTexture>>	m_mapTexture;
	std::unordered_map<std::string, CSharedPtr<CMaterial>>	m_mapMaterial;
	std::unordered_map<std::string, CSharedPtr<CAnimationSequence2D>>	m_mapAnimationSequence2D;

public:
	bool Init();


public:	// ===================== Mesh =========================
	bool CreateMesh(MeshType Type, const std::string& Name,
		void* VtxData, int Size, int Count,
		D3D11_USAGE VtxUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
		void* IdxData = nullptr, int IdxSize = 0, int IdxCount = 0,
		D3D11_USAGE IdxUsage = D3D11_USAGE_DEFAULT,
		DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN);

	class CMesh* FindMesh(const std::string& Name);



public:	// ===================== Shader =========================
	class CShader* FindShader(const std::string& Name);

public:	// ===================== Texture =========================
	bool LoadTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	bool LoadTexture(const std::string& Name, const std::vector<const TCHAR*>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath);
	class CTexture* FindTexture(const std::string& Name);

public:	// ===================== Material =========================
	CMaterial* FindMaterial(const std::string& Name);

	template <typename T>
	bool CreateMaterial(const std::string& Name)
	{
		if (FindMaterial(Name))
			return true;

		if (!CResourceManager::GetInst()->CreateMaterial<T>(Name))
			return false;

		m_mapMaterial.insert(std::make_pair(Name, CResourceManager::GetInst()->FindMaterial(Name)));

		return true;
	}

public:	// ===================== Animation =========================
	bool CreateAnimationSequence2D(const std::string& Name, const std::string& TextureName,
		const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
	bool CreateAnimationSequence2D(const std::string& Name, class CTexture* Texture);
	bool CreateAnimationSequence2DFullPath(const std::string& Name, const std::string& TextureName, const TCHAR* FullPath);
	bool CreateAnimationSequence2D(const std::string& Name, const std::string& TextureName, const std::vector<const TCHAR*>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	bool CreateAnimationSequence2DFullPath(const std::string& Name, const std::string& TextureName, const std::vector<const TCHAR*>& vecFullPath);
	bool AddAnimationSequence2DFrame(const std::string& Name, const Vector2& Start, const Vector2& End);
	bool AddAnimationSequence2DFrame(const std::string& Name, float StartX, float StartY, float EndX,
		float EndY);
	bool AddAnimationSequence2DFrameAll(const std::string& Name, int Count, const Vector2& Start, const Vector2& End);
	bool AddAnimationSequence2DFrameAll(const std::string& Name, int Count, float StartX, float StartY, float EndX,
		float EndY);
	bool SaveSequence2D(const std::string& Name, const char* FullPath);
	bool LoadSequence2D(const std::string& Name, const char* FullPath);
	bool SaveSequence2D(const std::string& Name, const char* FileName, const std::string& PathName);
	bool LoadSequence2D(const std::string& Name, const char* FileName, const std::string& PathName);

	CAnimationSequence2D* FindAnimationSequence2D(const std::string& Name);
};

