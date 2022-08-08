#pragma once

#include "../EngineInfo.h"
#include "../Resource/Mesh/Mesh.h"
#include "../Resource/Shader/Shader.h"
#include "../Resource/Texture/Texture.h"
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
};

