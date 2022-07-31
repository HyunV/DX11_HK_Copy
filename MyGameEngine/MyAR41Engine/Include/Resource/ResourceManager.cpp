
#include "ResourceManager.h"
#include "Mesh/MeshManager.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager()
{
	m_MeshManager = new CMeshManager; //메쉬매니저 생성
	
	m_MeshManager->Init(); //초기화

	m_ShaderManager = new CShaderManager;

	m_ShaderManager->Init();
}

CResourceManager::~CResourceManager()
{
	SAFE_DELETE(m_ShaderManager);
	SAFE_DELETE(m_MeshManager); //메쉬매니저 삭제
}

bool CResourceManager::Init()
{


	return true;
}

void CResourceManager::Update()
{
}

bool CResourceManager::CreateMesh(CScene* Scene, MeshType Type,
	const std::string& Name, void* VtxData, int Size,
	int Count, D3D11_USAGE VtxUsage,
	D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IdxData, int IdxSize,
	int IdxCount, D3D11_USAGE IdxUsage, DXGI_FORMAT Fmt)
{
	//이 리소스 리소스매니저에 있는 메시매니저에서 메시 생성
	return m_MeshManager->CreateMesh(Scene, Type, Name, VtxData, Size,
		Count, VtxUsage, Primitive, IdxData, IdxSize, IdxCount, IdxUsage,
		Fmt);
}

CMesh* CResourceManager::FindMesh(const std::string& Name)
{
	return m_MeshManager->FindMesh(Name);
}

void CResourceManager::ReleaseMesh(const std::string& Name)
{
	m_MeshManager->ReleaseMesh(Name);
}

CShader* CResourceManager::FindShader(const std::string& Name)
{
	return nullptr;
}

void CResourceManager::ReleaseShader(const std::string& Name)
{
}
