
//HLSL 언어
//메모장으로 작성되나 인클루드가 가능
// 이 파일은 공용헤더용도로 사용

//새 항목 -> 유틸리티 -> 텍스트파일 -> .fx로 만들어서 쓴다. 경로지정도 해둔다.

/*★##############이 셰이더 파일을 새로 만들게 되면 
● 빌드에서 제외 - 예
● 스프라이트 fx 우클릭 - 속성
	○ HLSL 컴파일러 항목
	- 진입점 이름을 써줘야 컴파일 오류가 안난다. SpriteColorVS 로 짓자
	- 셰이더 형식 (효과로 준다)
	- 셰이더 모델 (5.0버전을 사용할 것)
*/

//Dx11은 렌더타겟을 최대 8개까지 한번에 사용할 수 있다.
//SV_TARGET0 은 0번 렌더타겟에 출력한다. 이때 0은 생략이 가능하다.

struct PS_OUTPUT_SINGLE
{
	float4 Color : SV_TARGET; //렌더타겟은 백버퍼도 들고 있다.
};

//★★ 상수버퍼는 16바이트 단위로 맞춰야 한다.
cbuffer Transform : register(b0)
{
	matrix g_matWorld;
	matrix g_matView;
	matrix g_matProj;
	matrix g_matWVP;
	float3 g_Pivot;
	float  g_TransformEmpty1;
	float3 g_MeshSize;
	float g_TransformEmpty2;
};

cbuffer Material : register(b1)
{
	float4 g_MtrlBaseColor;
	float4 g_MtrlAmbientColor;
	float4 g_MtrlSpecularColor;
	float4 g_MtrlEmissiveColor;
	float g_MtrlOpacity;
    int g_MtrlTextureType;
    float g_MtrlTextureWidth;
    float g_MtrlTextureHeight;

};

SamplerState g_PointSmp : register(s0);
SamplerState g_LinearSmp : register(s1);
SamplerState g_AnisotropicSmp : register(s2);

Texture2D g_BaseTexture : register(t0);

cbuffer Animation2D : register(b2)
{
    float g_Anim2DImageWidth;
    float g_Anim2DImageHeight;
    float2 g_Anim2DFrameStart;
    float2 g_Anim2DFrameEnd;
    int g_Anim2DType;
    int g_Anim2DEnable;
    int g_Anim2DFrame;
    float3 g_Anim2DEmpty;
    //===========================================================
    //int g_Rotation; //반전 여부 테스트
};

#define Anim2D None -1
#define Anim2D_Atlas 0
#define Anim2D_Frame 1
#define Anim2D_Array 2

#define Image_Atlas 0
#define Image_Frame 1
#define Image_Array 2

float2 UpdateAnimation2D(float2 UV)
{
    if (g_Anim2DEnable == 0)
        return UV;
    
    float2 Result = (float2) 0;
    
    if (g_Anim2DType == Anim2D_Atlas)
    {
        if (UV.x == 0.f)
            Result.x = g_Anim2DFrameStart.x / g_Anim2DImageWidth;
        else
            Result.x = g_Anim2DFrameEnd.x / g_Anim2DImageWidth;
    
        if (UV.y == 0.f)
            Result.y = g_Anim2DFrameStart.y / g_Anim2DImageHeight;
        else
            Result.y = g_Anim2DFrameEnd.y / g_Anim2DImageHeight;
    }
    
    else
        Result = UV;
        
    return Result;
}