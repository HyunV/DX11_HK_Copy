#pragma once

#define DIRECTINPUT_VERSION 0x0800

#define GRAVITY 9.8f

#define g_SCALE 0.7f

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

//폰트출력용 디라이트
#include <dwrite_3.h> 
#include <d2d1.h>

#include <process.h> //쓰레드

#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d2d1.lib")

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "SharedPtr.h"
#include "Resource/Texture/DirectXTex.h"
#include "fmod.hpp"

#pragma comment(lib, "../Bin/fmod64_vc.lib")

extern float g_DeltaTime; //전역변수 해놓은거 가져오는 extern
extern float g_Scale;

//경로 관련 매크로
#define ROOT_PATH		"Root"
#define	SHADER_PATH		"Shader"
#define	TEXTURE_PATH	"Texture"
#define	SOUND_PATH		"Sound"
#define	FONT_PATH		"Font"
#define SEQUENCE2D_PATH "Sequence"
#define	ANIMATION2D_PATH		"Animation2D"
#define	SCENE_PATH		"Scene"

//싱글톤 생성, 파괴 매크로
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
	int	TextureType;
	float TextureWidth;
	float TextureHeight;
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

struct HierarchyObjectName
{
	std::string Name;
	std::string ParentName;
	std::string ClassName;
	std::string ParentClassName;
	class CGameObject* Obj;
	class CGameObject* Parent;
};

struct Animation2DFrameData
{
	Vector2 Start;
	Vector2 End;
};

struct Animation2DCBuffer
{
	float Anim2DImageWidth;
	float Anim2DImageHeight;
	Vector2 Anim2DFrameStart;

	Vector2 Anim2DFrameEnd;
	int Anim2DType;
	int Anim2DEnable;

	int Anim2DFrame;
	////내 코드===
	int SpriteReverse;
	int Anim2DReverse; 
	int Anim2DEmpty;
	//===========
	//Vector3 Anim2DEmpty;

};

struct CollisionChannel
{
	std::string			Name;
	ECollision_Channel	Channel;
	ECollision_Interaction	Interaction;
};

struct CollisionProfile
{
	std::string			Name;
	CollisionChannel* Channel;
	bool				Enable;
	std::vector<ECollision_Interaction>	vecCollisionInteraction;

	CollisionProfile() :
		Enable(true)
	{
	}
};

struct CollisionResult
{
	class CCollider* Src;
	class CCollider* Dest;
	Vector3			HitPoint;

	CollisionResult() :
		Src(nullptr),
		Dest(nullptr)
	{
	}
};

struct ColliderCBuffer
{
	Vector4	Color;
	Matrix	matWVP;
};

struct Box2DInfo
{
	float Left;
	float Bottom;
	float Right;
	float Top;
};

struct Sphere2DInfo
{
	Vector2	Center;
	float	Radius;
};

struct OBB2DInfo
{
	Vector2	Center;
	Vector2	Axis[AXIS2D_MAX];
	float	Length[AXIS2D_MAX];

};

struct PixelInfo
{
	Box2DInfo	Box2D;
	unsigned char* Pixel;
	unsigned int	Width;
	unsigned int	Height;
	EPixelCollision_Type	PixelColorCollisionType;
	EPixelCollision_Type	PixelAlphaCollisionType;
	unsigned char	TypeColor[4];
	ID3D11ShaderResourceView* SRV;
	std::string	Name;
	TCHAR		FileName[MAX_PATH];
	char		PathName[MAX_PATH];
	int			RefCount;

	PixelInfo() :
		FileName{},
		PathName{},
		RefCount(0),
		Pixel(nullptr),
		Box2D{},
		Width(0),
		Height(0),
		PixelColorCollisionType(EPixelCollision_Type::Alpha_Confirm),
		PixelAlphaCollisionType(EPixelCollision_Type::None),
		TypeColor{}
	{
	}
};

struct UICBuffer
{
	Vector4 UITint;
	Matrix	UIWVP;
	Vector2 UIMeshSize;
	Vector2 UIPivot;
	int		UITextureEnable;
	float	UIOpacity;
	Vector2	UIEmpty;
};

struct UIProgressBarCBuffer
{
	int		BarDir;
	float	Percent;
	Vector2	Empty;
};

struct ThreadSyncData
{
	int	Header;
	int	Size;
	unsigned char Data[1024];
};

struct TileMapCBuffer
{
	Vector2	ImageSize;
	Vector2	Start;
	Vector2	End;
	Vector2	TileSize;
	Matrix	matWVP;
	int		Frame;
	Vector3	Empty;
};

struct TileInfo
{
	Matrix	matWVP;
	Vector2	Start;
	Vector2	End;
	Vector4	TypeColor;
	float	Opacity;
	int		AnimationType;
	int		Frame;
	float	Empty;
};

struct PlayerInfo
{
	int MaxHP;
	int HP;
	int Gio;
	bool AdvHP;
	bool AdvAttack;
	bool AdvDash;
	bool AdvFire;

	PlayerInfo() :
		MaxHP(5),
		HP(5),
		Gio(0),
		AdvHP(false),
		AdvAttack(false),
		AdvDash(false),
		AdvFire(false)
	{
	}
};

enum class ENPC
{
	ElderBug,
	Honnet,
	Brum,
	Sly
};

enum class EFireBallDirection
{
	None,
	Up,
	Down,
	OnlyDown
};