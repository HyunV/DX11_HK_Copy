
#include "MeshManager.h"
#include "SpriteMesh.h"

CMeshManager::CMeshManager()
{
}

CMeshManager::~CMeshManager()
{
}

bool CMeshManager::Init()
{
	// 기본 메쉬 생성 센터 중심, 좌하단 중심

	//센터 중심인 사각형
	VertexColor CenterColorMesh[4] =
	{
		VertexColor(Vector3(-0.5f, 0.5f, 0.f), Vector4::Red),
		VertexColor(Vector3(0.5f, 0.5f, 0.f), Vector4::Green),
		VertexColor(Vector3(-0.5f, -0.5f, 0.f), Vector4::Blue),
		VertexColor(Vector3(0.5f, -0.5f, 0.f), Vector4(1.f, 0.f, 1.f, 1.f)) //마젠타
	};

	unsigned int RectIndex[6] = { 0, 1, 3, 0, 3, 2 }; //사각형 1개를 위한 삼각형 2개
	//시계방향으로 0, 1, 3 삼각형, 0, 3, 2 삼각형

	CreateMesh(nullptr, MeshType::Sprite, "CenterColorRect",
		CenterColorMesh, sizeof(VertexColor), 4, D3D11_USAGE_IMMUTABLE,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, RectIndex,
		4, 6, D3D11_USAGE_IMMUTABLE, DXGI_FORMAT_R32_UINT);

	//0,0 이 기준점인 사각형
	VertexColor	LBColorMesh[4] =
	{
		VertexColor(Vector3(0.f, 1.f, 0.f), Vector4::Red),
		VertexColor(Vector3(1.f, 1.f, 0.f), Vector4::Green),
		VertexColor(Vector3(0.f, 0.f, 0.f), Vector4::Blue),
		VertexColor(Vector3(1.f, 0.f, 0.f), Vector4(1.f, 0.f, 1.f, 1.f))
	};

	CreateMesh(nullptr, MeshType::Sprite, "LBColorRect",
		LBColorMesh, sizeof(VertexColor), 4, D3D11_USAGE_IMMUTABLE,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, RectIndex,
		4, 6, D3D11_USAGE_IMMUTABLE, DXGI_FORMAT_R32_UINT);

	return true;
}

bool CMeshManager::CreateMesh(CScene* Scene, MeshType Type, const std::string& Name,
	void* VtxData, int Size, int Count, D3D11_USAGE VtxUsage,
	D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IdxData, int IdxSize,
	int IdxCount, D3D11_USAGE IdxUsage, DXGI_FORMAT Fmt)
{
	if (FindMesh(Name)) //이미 같은 이름의 메시가 있으면 종료
		return true;

	CMesh* Mesh = nullptr; //메시 생성

	switch (Type)
	{
	case MeshType::Sprite: //타입에 따른 메시 생성
		Mesh = new CSpriteMesh;
		break;
	case MeshType::UI:
		break;
	case MeshType::Static:
		break;
	case MeshType::Animation:
		break;
	}

	Mesh->SetScene(Scene); //사용될 씬 부여
	Mesh->SetName(Name); //메시의 이름 지어줌

	if (!Mesh->CreateMesh(VtxData, Size, Count, VtxUsage, Primitive,
		IdxData, IdxSize, IdxCount, IdxUsage, Fmt))
	{
		SAFE_RELEASE(Mesh); //메시 생성 실패시
		return false;
	}

	m_mapMesh.insert(std::make_pair(Name, Mesh)); //만들어진 메시를 이름을 기반으로 저장

	return true;
}

CMesh* CMeshManager::FindMesh(const std::string& Name)
{
	auto	iter = m_mapMesh.find(Name);

	if (iter == m_mapMesh.end())
		return nullptr;

	return iter->second;
}

void CMeshManager::ReleaseMesh(const std::string& Name)
{
	auto	iter = m_mapMesh.find(Name);

	if (iter != m_mapMesh.end())
	{
		//이터레이터 2번째 레퍼런스카운터가 1이면 이전 애를 제거한다?
		if (iter->second->GetRefCount() == 1)
			m_mapMesh.erase(iter);
	}
}
