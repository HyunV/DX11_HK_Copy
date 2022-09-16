#pragma once

#define DIRECTINPUT_VERSION 0x0800

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
#include <dinput.h> //다렉용 input 헤더
#include <filesystem> //C++17 에디터 classwindow의 directory_iterator 사용하기 위함

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "SharedPtr.h"
#include "Resource/Texture/DirectXTex.h"

extern float g_DeltaTime; //전역변수 해놓은거 가져오는 extern

//경로 관련 매크로
#define ROOT_PATH		"Root"
#define	SHADER_PATH		"Shader"
#define	TEXTURE_PATH	"Texture"
#define	SOUND_PATH		"Sound"
#define	FONT_PATH		"Font"

//싱글톤 생성, 파괴 매크로
#define DECLARE_SINGLE(Type)	\
private:\
	static Type*	m_Inst;\
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
	unsigned int Width;
	unsigned int Height;
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

struct TransformCBuffer
{
	Matrix  matWorld;
	Matrix  matView;
	Matrix  matProj;
	Matrix  matWVP;
	Vector3 Pivot;
	float	Empty1;
	Vector3 MeshSize;
	float	Empty2;
};

struct VertexUV
{
	Vector3 Pos;
	Vector2 UV;

	VertexUV()
	{

	}
	VertexUV(const Vector3& _Pos, const Vector2& _UV) :
		Pos(_Pos),
		UV(_UV)
	{

	}
};

struct MaterialCBuffer
{
	Vector4 BaseColor;
	Vector4 AmbientColor;
	Vector4 SpecularColor;
	Vector4 EmissiveColor;
	float Opacity;
	Vector3 Empty;
};

struct HierarchyName
{
	std::string Name;
	std::string ParentName;
	std::string	ClassName;
	std::string	ParentClassName;
	class CComponent* Component;
	class CComponent* Parent;
};

