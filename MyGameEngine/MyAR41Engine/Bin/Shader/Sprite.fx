#include "Share.fx"

/*
쉐이더들은 기본적으로 입력레지스터, 출력레지스터, 상수레지스터, 임시레지스터가 존재한다.

VertexShader 또한 마찬가지

● 레지스터는 이름 + 번호로 만들어지게 된다.
예를 들어 POSITION 레지스터라면 POSITION0 ~ 15 번까지 이용이 가능하다.
0번일 경우 번호 생략이 가능해서 POSITION 이라고 하면 0번 레지스터를 의미한다.

■ 입력레지스터 : 출력하는 메쉬의 정점정보가 들어가 있게 된다.
메쉬를 출력할때 정점이 어떤 구조로 만들어진 정점인지를 지정한 후에 출력을
하게 된다.

■ 출력레지스터 : Shader에서 연산을 마무리한 후에 결과값을 저장해두기 위한
레지스터이다. VertexShader의 경우 연산된 투영공간에서의 위치 정보를 넣어준다던지
아니면 다른 Shader에서 필요로 하는 추가적인 정보들도 출력레지스터 넣어두면
뒤의 Shader들이 가져가서 사용할 수 있다.

■ 상수레지스터 : C++코드가 가지고 있는 정보를 Shader에 넘겨줄때 사용한다.

■ 임시레지스터 : C++연산처럼 연산할때 필요한 레지스터이다.
*/


// float : 실수타입 float2 : x, y를 가지고 있는 Vector2, float3, float4 다 됨.
// int : 정수타입 int2 : x, y를 int타입으로 가지고 있는 Vector2 타입
// Semantic : 레지스터를 지정한다.

// 아래처럼 지정하면 입력레지스터의 POSITION0, COLOR0 레지스터에 들어있는
// 값을 가져와서 사용하겠다는 것이다.

struct VS_INPUT_COLOR //입력받기
{
	//* 이거 c++에서는 : 쓰면 비트필드라고 하는 고대문법인데 쓸 일 없다.
	float3 Pos : POSITION; //0번째 레지스터를 지정해서 pos를 담아두다.
	float4 Color : COLOR; //0번째 레지스터를 지정해서 COLOR를 담아둔다.
};

// SV : System Value로 사용되는 값으로 출력레지스터에서 사용할 수 있다.
// 출력레지스터에 아래처럼 SV_POSITION 을 넣으면 최종 투영공간에서의 위치를
// 지정하는것으로 이 값을 이용해서 화면의 어디에 출력할지를 결정한다.
// SV 값은 다른 Shader에서 절대로 건드리면 안된다.
struct VS_OUTPUT_COLOR
{
	float4 Pos : SV_POSITION; //시스템 밸류, 무분별한 사용 ㄴㄴ
	float4 Color : COLOR;
};

struct VS_INPUT_UV
{
	float3 Pos : POSITION;
	float2 UV : TEXCOORD;
};

struct VS_OUTPUT_UV
{
	float4 Pos : SV_POSITION;
	float2 UV : TEXCOORD;
};

// 인자로 VS_INPUT_COLOR를 쓰면 저 구조체에 지정된 입력 레지스터에서 값을
// 가져와서 사용하므로 인자를 따로 넣어줄 필요가 없다.

VS_OUTPUT_COLOR SpriteColorVS(VS_INPUT_COLOR input)
{
	VS_OUTPUT_COLOR output = (VS_OUTPUT_COLOR) 0; //0번째거 가져온다는 뜻인가..?

	float3 Pos = input.Pos - g_Pivot * g_MeshSize;

	// mul : 행렬 곱. g_matWVP 는 World * View * Proj 이므로 정점을 여기에 곱하게 되면
	// 투영 공간으로 변환된 정점의 위치가 나온다.
	output.Pos = mul(float4(Pos, 1.f), g_matWVP);
	output.Color = input.Color;

	return output;
}

//PS_OUTPUT_SINGLE :  백버퍼랑 연결되어있는 렌더타겟을 출력한다.
PS_OUTPUT_SINGLE SpriteColorPS(VS_OUTPUT_COLOR input)
{
	PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE) 0;

	output.Color = input.Color; //컬러만 가져온다. output Pos는 SV이므로 가져오면 ㅈ댐

	return output;
}

// 인자로 VS_INPUT_COLOR를 쓰면 저 구조체에 지정된 입력 레지스터에서 값을
// 가져와서 사용하므로 인자를 따로 넣어줄 필요가 없다.
VS_OUTPUT_UV SpriteVS(VS_INPUT_UV input)
{
	VS_OUTPUT_UV output = (VS_OUTPUT_UV) 0;

	//인풋: TEXCOORD, Pos로 구성(pos는 LB쪽으로 그리는 위치)
	float3 Pos = input.Pos - g_Pivot * g_MeshSize;

	// mul : 행렬 곱. g_matWVP 는 World * View * Proj 이므로 정점을 여기에 곱하게 되면
	// 투영 공간으로 변환된 정점의 위치가 나온다.
	output.Pos = mul(float4(Pos, 1.f), g_matWVP);
	
	output.UV = UpdateAnimation2D(input.UV);

	//이미지 회전 여부 내 코드
	//output.UV.x = 1 - input.UV.x;
    //if (g_SpriteReverse == 1)
    //{
    //    output.UV.x = 1.f - output.UV.x;
    //}
	
	//================
	return output;
}

PS_OUTPUT_SINGLE SpritePS(VS_OUTPUT_UV input)
{
	PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE) 0;
	

	float4 TextureColor = g_BaseTexture.Sample(g_PointSmp, input.UV);

	//레드(255)키 제외
    if (TextureColor.r == 1.f && TextureColor.g == 0.f && TextureColor.b == 0.f)
    {
        TextureColor.a = 0.f;
    }

	output.Color.rgb = TextureColor.rgb * g_MtrlBaseColor.rgb;

	output.Color.a = TextureColor.a * g_MtrlOpacity;

	return output;
}


//쉐이더 입력->연산->출력A
//이 출력A를 다른 쉐이더가 입력으로 받고 또 출력 B 하는 과정이 렌파라의 기본적인 과정임.