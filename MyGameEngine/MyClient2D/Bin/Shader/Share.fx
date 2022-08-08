
//HLSL ���
//�޸������� �ۼ��ǳ� ��Ŭ��尡 ����
// �� ������ ��������뵵�� ���

//�� �׸� -> ��ƿ��Ƽ -> �ؽ�Ʈ���� -> .fx�� ���� ����. ��������� �صд�.

/*��##############�� ���̴� ������ ���� ����� �Ǹ� 
�� ���忡�� ���� - ��
�� ��������Ʈ fx ��Ŭ�� - �Ӽ�
	�� HLSL �����Ϸ� �׸�
	- ������ �̸��� ����� ������ ������ �ȳ���. SpriteColorVS �� ����
	- ���̴� ���� (ȿ���� �ش�)
	- ���̴� �� (5.0������ ����� ��)
*/

//Dx11�� ����Ÿ���� �ִ� 8������ �ѹ��� ����� �� �ִ�.
//SV_TARGET0 �� 0�� ����Ÿ�ٿ� ����Ѵ�. �̶� 0�� ������ �����ϴ�.

struct PS_OUTPUT_SINGLE
{
	float4 Color : SV_TARGET; //����Ÿ���� ����۵� ��� �ִ�.
};

//������۴� 16����Ʈ ������ ����� �Ѵ�.
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