#pragma once

#include <Windows.h>
#include <vector>
#include <list>
#include <unordered_map>
#include <crtdbg.h>
#include <typeinfo>
#include <string>
#include <functional>
#include <algorithm>
#include <stack>
#include <d3d11.h> //다렉 헤더파일
#include <d3dcompiler.h> //쉐이더를 만들어서 코드만들어야됨 , 얘네는 빌드에 포함이 안됨.. 별도로 로딩해서 써야됨
						//쉐이더를 컴파일하기 위해 필요하다.

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "SharedPtr.h"

//경로 관련 매크로
#define ROOT_PATH		"Root"
#define	SHADER_PATH		"Shader"
#define	TEXTURE_PATH	"Texture"
#define	SOUND_PATH		"Sound"
#define	FONT_PATH		"Font"

//싱글톤 생성, 파괴 매크로
#pragma once
#define DECLARE_SINGLE(Type)	\
private:\
	static Type* m_Inst;\
public:\
	static Type* GetInst()\
	{\
		if (!m_Inst)\
			m_Inst = new Type;\
		return m_Inst;\
	}\
	static void DestroyInst()\
	{\
		if(m_Inst)\
		{\
		delete m_Inst;\
		m_Inst = nullptr;\
		}\
	}\
private:\
	Type(); \
	~Type();

#define DEFINITION_SINGLE(Type) Type* Type::m_Inst = nullptr;


#define SAFE_DELETE(p)  if(p) {delete p; p = nullptr;}
#define SAFE_DELETE_ARRAY(p) if(p) {delete[] p; p = nullptr;}
#define	SAFE_RELEASE(p)	if(p)	{ p->Release(); p = nullptr;}

struct Resolution //해상도
{
	int Width;
	int Height;
};

//위치, 색상정보를 가지고 있는 버텍스(정점)
struct VertexColor
{
	Vector3 Pos; // 12바이트
	Vector4 Color; // 16바이트

	VertexColor()
	{
	}
	//복사생성자
	VertexColor(const Vector3& _Pos, const Vector4& _Color) :
		Pos(_Pos),
		Color(_Color)
	{
	}
};

struct VertexBuffer //VB
{
	ID3D11Buffer* Buffer;
	int	Size; //정점 1개의 크기
	int Count; // 정점의 개수
	void* Data; // 정점의 정보

	VertexBuffer() :
		Buffer(nullptr),
		Size(0),
		Count(0),
		Data(nullptr)
	{

	}

	~VertexBuffer()
	{
		SAFE_DELETE_ARRAY(Data);
		SAFE_RELEASE(Buffer);
	}
};

struct IndexBuffer
{
	ID3D11Buffer* Buffer;
	int	Size;
	int Count;
	DXGI_FORMAT Fmt; //인덱스 버퍼는 버텍스버퍼와 달리 포맷형식 추가
	void* Data;

	IndexBuffer() :
		Buffer(nullptr),
		Size(0),
		Count(0),
		Fmt(DXGI_FORMAT_UNKNOWN),
		Data(nullptr)
	{
	}

	~IndexBuffer()
	{
		SAFE_DELETE_ARRAY(Data);
		SAFE_RELEASE(Buffer);
	}
};

struct MeshContainer //버퍼로 도형의 모양을 결정하는 container
{
	VertexBuffer VB;
	std::vector<IndexBuffer> vecIB; //인덱스 버퍼는 늘어날 수 있으니 vecter로 담는다.

	D3D11_PRIMITIVE_TOPOLOGY	Primitive;
};

struct MeshSlot //버텍스, 인덱스 버퍼의 포인터를 가지고?
{
	VertexBuffer* VB;
	IndexBuffer* IB;
	D3D11_PRIMITIVE_TOPOLOGY	Primitive;

	MeshSlot() :
		VB(nullptr),
		IB(nullptr)
	{

	}
};