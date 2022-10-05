
#include "Share.fx"

cbuffer UICBuffer : register(b10)
{
    float4 g_UITint;
    matrix g_UIWVP;
    float2 g_UIMeshSize;
    float2 g_UIPivot;
    int g_UITextureEnable;
    float g_UIOpacity;
    float2 g_UIEmpty;
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
VS_OUTPUT_UV UIVS(VS_INPUT_UV input)
{
    VS_OUTPUT_UV output = (VS_OUTPUT_UV)0;

    float2 Pos = input.Pos.xy - g_UIPivot * g_UIMeshSize;

    // mul : 행렬 곱. g_matWVP 는 World * View * Proj 이므로 정점을 여기에 곱하게 되면
    // 투영 공간으로 변환된 정점의 위치가 나온다.
    output.Pos = mul(float4(Pos, input.Pos.z, 1.f), g_UIWVP);

    if (g_UITextureEnable)
        output.UV = UpdateAnimation2D(input.UV);

    else
        output.UV = input.UV;

    return output;
}

PS_OUTPUT_SINGLE UIPS(VS_OUTPUT_UV input)
{
    PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE)0;

    if (g_UITextureEnable)
    {
        float4 TextureColor = g_BaseTexture.Sample(g_PointSmp, input.UV);

        output.Color.rgb = TextureColor.rgb * g_UITint.rgb;

        output.Color.a = TextureColor.a * g_UIOpacity;
    }

    else
    {
        output.Color.rgb = g_UITint.rgb;
        output.Color.a = g_UITint.a * g_UIOpacity;

    }

    return output;
}
