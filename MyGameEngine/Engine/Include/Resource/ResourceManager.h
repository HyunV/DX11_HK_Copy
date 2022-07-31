#pragma once

#include "../EngineInfo.h"
#include "Shader/ShaderManager.h"

class CResourceManager
{
private:
	class CMeshManager* m_MeshManager; //�޽� �Ŵ���
	CShaderManager* m_ShaderManager;
	//�ؽ�ó �Ŵ���
	//���� �Ŵ���
	//��Ʈ �Ŵ��� ���..

public:
	bool Init();
	void Update();


public:	// ===================== Mesh ========================= //���ҽ� �Ŵ������� ��¥�� createMesh �Ҷ�
	bool CreateMesh(class CScene* Scene, MeshType Type, const std::string& Name,
		void* VtxData, int Size, int Count,
		D3D11_USAGE VtxUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
		void* IdxData = nullptr, int IdxSize = 0, int IdxCount = 0,
		D3D11_USAGE IdxUsage = D3D11_USAGE_DEFAULT,
		DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN);
	/*CreateMesh(�Ҽӵ� ��, �޽�Ÿ��, �˻��� �̸�,
	���ؽ����� ������, ver������, verũ��,
	���ؽ� ���뵵, ���ؽ�������, 
	�ε������� ������(��� ��������� ����Ʈ null), �ι� ������, �ι� ī��Ʈ,
	�ι� ���뵵,
	��������
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


	// ==========================�̱���==========================
	DECLARE_SINGLE(CResourceManager)
};

