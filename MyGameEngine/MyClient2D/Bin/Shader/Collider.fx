
#include "Share.fx"

cbuffer ColliderCBuffer : register(b10)
{
    float4 g_ColliderColor;
    matrix g_ColliderWVP;
};

float4 ColliderVS(float3 Pos : POSITION) : SV_Position
{
    return mul(float4(Pos, 1.f), g_ColliderWVP);
}

float4 ColliderPS() : SV_TARGET
{
    return g_ColliderColor;
}