#pragma once

#include "../EngineInfo.h"
#include "Shader/ShaderManager.h"
#include "Material/MaterialManager.h"

class CResourceManager
{
private:
	class CMeshManager* m_MeshManager; //메쉬 매니저
	CShaderManager* m_ShaderManager;
	class CTextureManager* m_TextureManager;
	class CMaterialManager* m_MaterialManager;
	//텍스처 매니저
	//사운드 매니저
	//폰트 매니저 등등..

public:
	bool Init();
	void Update();


public:	// ===================== Mesh ========================= //리소스 매니저에서 통짜로 createMesh 할때
	bool CreateMesh(class CScene* Scene, MeshType Type, const std::string& Name,
		void* VtxData, int Size, int Count,
		D3D11_USAGE VtxUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
		void* IdxData = nullptr, int IdxSize = 0, int IdxCount = 0,
		D3D11_USAGE IdxUsage = D3D11_USAGE_DEFAULT,
		DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN);
	/*CreateMesh(소속된 씬, 메쉬타입, 검색할 이름,
	버텍스버퍼 데이터, ver사이즈, ver크기,
	버텍스 사용용도, 버텍스위상구조, 
	인덱스버퍼 데이터(없어도 상관없으니 디폴트 null), 인버 사이즈, 인버 카운트,
	인버 사용용도,
	포맷형식
	*/

	class CMesh* FindMesh(const std::string& Name);
	void ReleaseMesh(const std::string& Name);


public:	// ===================== Shader =========================
	template <typename T>
	bool CreateShader(const std::string& Name)
	{
		return m_ShaderManager->CreateShader<T>(Name);
	}

	class CShader* FindShader(const std::string& Name);
	void ReleaseShader(const std::string& Name);

	bool CreateConstantBuffer(const std::string& Name, int Size, int Register,
		int ShaderBufferType = (int)EShaderBufferType::All);
	class CConstantBuffer* FindConstantBuffer(const std::string& Name);



public:	// ===================== Texture =========================
	bool LoadTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	bool LoadTexture(const std::string& Name, const std::vector<const TCHAR*>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath);
	class CTexture* FindTexture(const std::string& Name);
	void ReleaseTexture(const std::string& Name);

public:	// ===================== Material =========================
	CMaterial* FindMaterial(const std::string& Name);
	void ReleaseMaterial(const std::string& Name);

	template <typename T>
	T* CreateMaterial(const std::string& Name)
	{
		return m_MaterialManager->CreateMaterial<T>(Name);
	}

	// ==========================싱글톤==========================
	DECLARE_SINGLE(CResourceManager)
};

