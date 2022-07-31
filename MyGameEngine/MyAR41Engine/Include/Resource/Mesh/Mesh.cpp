
#include "Mesh.h"
#include "../../Device.h"

CMesh::CMesh() :
	m_Min(FLT_MAX, FLT_MAX, FLT_MAX), //min에는 최대값 채워놓고
	m_Max(FLT_MIN, FLT_MIN, FLT_MIN) // max에는 최소값들 채워놨음
	//초기화를 반대로 해놔야 얘네 역할인 최대값 최대값 세팅할 수 있으니까
{
}

CMesh::~CMesh()
{
	//메시 지울때 벡터 컨테이너 , 메시슬롯 일일히 다 지워줌.
	size_t	Size = m_vecContainer.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecContainer[i]);
	}
	Size = m_vecMeshSlot.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecMeshSlot[i]);
	}
}

bool CMesh::CreateMesh(void* VtxData, int Size, int Count,
	D3D11_USAGE VtxUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
	void* IdxData, int IdxSize, int IdxCount, D3D11_USAGE IdxUsage,
	DXGI_FORMAT Fmt)
{
	MeshContainer* Container = new MeshContainer; //버텍스버퍼, 인덱스 버퍼 토폴로지 담는 메시 컨테이너 생성

	Container->VB.Size = Size;
	Container->VB.Count = Count;
	Container->Primitive = Primitive;
	Container->VB.Data = new char[Size * Count];
	memcpy(Container->VB.Data, VtxData, Size * Count);

	if (!CreateBuffer(BufferType::Vertex, VtxData, Size, Count,
		VtxUsage, &Container->VB.Buffer))
		return false;

	m_vecContainer.push_back(Container);

	MeshSlot* Slot = new MeshSlot;

	m_vecMeshSlot.push_back(Slot);

	Slot->VB = &Container->VB;
	Slot->Primitive = Container->Primitive;

	if (IdxData != nullptr)
	{
		IndexBuffer	IB;
		Container->vecIB.push_back(IB);
		int Index = (int)Container->vecIB.size() - 1;

		Slot->IB = &Container->vecIB[Index];

		Slot->IB->Size = IdxSize;
		Slot->IB->Count = IdxCount;
		Slot->IB->Fmt = Fmt;
		Slot->IB->Data = new char[IdxSize * IdxCount];
		memcpy(Slot->IB->Data, IdxData, IdxSize * IdxCount);

		if (!CreateBuffer(BufferType::Index, IdxData, IdxSize, IdxCount,
			IdxUsage, &Slot->IB->Buffer))
			return false;
	}

	return true;
}

void CMesh::Render() //모든 슬롯 렌더 하기
{
	size_t	Size = m_vecMeshSlot.size();

	for (size_t i = 0; i < Size; ++i)
	{
		unsigned int	Stride = (unsigned int)m_vecMeshSlot[i]->VB->Size;
		unsigned int	Offset = 0;

		CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(m_vecMeshSlot[i]->Primitive);
		CDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 1,
			&m_vecMeshSlot[i]->VB->Buffer, &Stride, &Offset);

		if (m_vecMeshSlot[i]->IB) //인덱스 버퍼일때
		{
			CDevice::GetInst()->GetContext()->IASetIndexBuffer(
				m_vecMeshSlot[i]->IB->Buffer, m_vecMeshSlot[i]->IB->Fmt,
				0);
			CDevice::GetInst()->GetContext()->DrawIndexed(
				m_vecMeshSlot[i]->IB->Count, 0, 0);
		}

		else
		{
			CDevice::GetInst()->GetContext()->IASetIndexBuffer(
				nullptr, DXGI_FORMAT_UNKNOWN, 0);
			CDevice::GetInst()->GetContext()->Draw(
				m_vecMeshSlot[i]->VB->Count, 0);
		}
	}
}

void CMesh::Render(int SlotNumber) //특정 슬롯만 렌더하기
{
	unsigned int	Stride = (unsigned int)m_vecMeshSlot[SlotNumber]->VB->Size;
	unsigned int	Offset = 0;

	CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(m_vecMeshSlot[SlotNumber]->Primitive);
	CDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 1,
		&m_vecMeshSlot[SlotNumber]->VB->Buffer, &Stride, &Offset);

	if (m_vecMeshSlot[SlotNumber]->IB)
	{
		CDevice::GetInst()->GetContext()->IASetIndexBuffer(
			m_vecMeshSlot[SlotNumber]->IB->Buffer, m_vecMeshSlot[SlotNumber]->IB->Fmt,
			0);
		CDevice::GetInst()->GetContext()->DrawIndexed(
			m_vecMeshSlot[SlotNumber]->IB->Count, 0, 0);
	}

	else
	{
		CDevice::GetInst()->GetContext()->IASetIndexBuffer(
			nullptr, DXGI_FORMAT_UNKNOWN, 0);
		CDevice::GetInst()->GetContext()->Draw(
			m_vecMeshSlot[SlotNumber]->VB->Count, 0);
	}
}

bool CMesh::CreateBuffer(BufferType Type, void* Data, int Size,
	int Count, D3D11_USAGE Usage, ID3D11Buffer** Buffer)
{
	D3D11_BUFFER_DESC	Desc = {}; //사용할 버퍼의 구조체 정의

	Desc.ByteWidth = Size * Count; //구조체의 크기 지정: 정점크기x정점개수가 크기
	Desc.Usage = Usage;

	//버퍼 타입일때 플래그 다르게 새워둠
	if (Type == BufferType::Vertex)
		Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	else
		Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// 다이나믹일때는 CPU는 쓰기를 허용한다. 느리다.
	if (Usage == D3D11_USAGE_DYNAMIC)
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//스탠딩일때는 CPU R/W 가 허용된다. 겁나느리다.
	else if (Usage == D3D11_USAGE_STAGING)
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;

	D3D11_SUBRESOURCE_DATA	BufferData = {}; //하위 리소스 데이터를 설명하는 구조체
	//리소스 내의 실제 데이터들을 정의 , 얘는 디바이스 정보도 필요하다.

	BufferData.pSysMem = Data; //리소스 데이터들을 직접 가리켜주는 pSysMem

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, &BufferData,
		Buffer)))
		return false; //버퍼 생성 실패시 빠꾸

	if (Type == BufferType::Vertex) //버텍스 버퍼 일시
	{
		//버텍스 버퍼를 만들면 [Pos(12바이트) | Color ] 이런식으로 들어있을 것이다.
		// 출력하면 위치가 항상 먼저 출력
		// 정점은 위치 12바이트가 항상 먼저 들어와 있을 것이다. 
		
		char* VertexData = (char*)Data; //따라서 1바이트 기준으로 for문 돌려서 포인터 연산을 수행한다.

		for (int i = 0; i < Count; ++i) //정점의 개수만큼
		{
			Vector3* Pos = (Vector3*)VertexData;
			VertexData += Size;
			
			//min, max 최대, 최소값 세팅을 해준다.

			if (m_Min.x > Pos->x)
				m_Min.x = Pos->x;

			if (m_Min.y > Pos->y)
				m_Min.y = Pos->y;

			if (m_Min.z > Pos->z)
				m_Min.z = Pos->z;

			if (m_Max.x < Pos->x)
				m_Max.x = Pos->x;

			if (m_Max.y < Pos->y)
				m_Max.y = Pos->y;

			if (m_Max.z < Pos->z)
				m_Max.z = Pos->z;
		}
	}

	return true;
}
