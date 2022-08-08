
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

//상수버퍼는 16바이트 단위로 맞춰야 한다.
cbuffer Transform : register(b0)
{
	matrix g_matWorld;
	matrix g_matView;
	matrix g_matProj;
	matrix g_matWVP;
	float3 g_Pivot;
	float3 g_MeshSize;
	float2 g_TransformEmpty;
};

cbuffer Material : register(b1)
{
	float4 g_MtrlBaseColor;
	float4 g_MtrlAmbientColor;
	float4 g_MtrlSpecularColor;
	float4 g_MtrEmissiveColor;
	float g_MtrlOpacity;
	float3 g_MtrlEmpty;
};

SamplerState g_PointSmp : register(s0);
SamplerState g_LinearSmp : register(s1);
SamplerState g_AnisotropicSmp : register(s2);

Texture2D g_BaseTexture : register(t0);