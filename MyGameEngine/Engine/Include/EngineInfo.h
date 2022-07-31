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
#include <d3d11.h> //�ٷ� �������
#include <d3dcompiler.h> //���̴��� ���� �ڵ常���ߵ� , ��״� ���忡 ������ �ȵ�.. ������ �ε��ؼ� ��ߵ�
						//���̴��� �������ϱ� ���� �ʿ��ϴ�.

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "SharedPtr.h"

//��� ���� ��ũ��
#define ROOT_PATH		"Root"
#define	SHADER_PATH		"Shader"
#define	TEXTURE_PATH	"Texture"
#define	SOUND_PATH		"Sound"
#define	FONT_PATH		"Font"

//�̱��� ����, �ı� ��ũ��
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

struct Resolution //�ػ�
{
	int Width;
	int Height;
};

//��ġ, ���������� ������ �ִ� ���ؽ�(����)
struct VertexColor
{
	Vector3 Pos; // 12����Ʈ
	Vector4 Color; // 16����Ʈ

	VertexColor()
	{
	}
	//���������
	VertexColor(const Vector3& _Pos, const Vector4& _Color) :
		Pos(_Pos),
		Color(_Color)
	{
	}
};

struct VertexBuffer //VB
{
	ID3D11Buffer* Buffer;
	int	Size; //���� 1���� ũ��
	int Count; // ������ ����
	void* Data; // ������ ����

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
	DXGI_FORMAT Fmt; //�ε��� ���۴� ���ؽ����ۿ� �޸� �������� �߰�
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

struct MeshContainer //���۷� ������ ����� �����ϴ� container
{
	VertexBuffer VB;
	std::vector<IndexBuffer> vecIB; //�ε��� ���۴� �þ �� ������ vecter�� ��´�.

	D3D11_PRIMITIVE_TOPOLOGY	Primitive;
};

struct MeshSlot //���ؽ�, �ε��� ������ �����͸� ������?
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