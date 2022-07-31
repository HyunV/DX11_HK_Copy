
#include "ResourceManager.h"
#include "Mesh/MeshManager.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager()
{
	m_MeshManager = new CMeshManager; //�޽��Ŵ��� ����
	
	m_MeshManager->Init(); //�ʱ�ȭ

	m_ShaderManager = new CShaderManager;

	m_ShaderManager->Init();
}

CResourceManager::~CResourceManager()
{
	SAFE_DELETE(m_ShaderManager);
	SAFE_DELETE(m_MeshManager); //�޽��Ŵ��� ����
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
	//�� ���ҽ� ���ҽ��Ŵ����� �ִ� �޽øŴ������� �޽� ����
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
