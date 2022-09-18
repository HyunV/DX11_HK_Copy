#pragma once

#include <DirectXMath.h> //SSE2������� SIMD�������ͷ� 32��Ʈ 4���� �ڷ����� �ѹ��� ó�� ����
#include <DirectXPackedVector.h>
#include <assert.h>
#include <string>

#include "Flag.h"

#define PI 3.14159f

static float DegreeToRadian(float Degree)
{
	return Degree * PI / 180.f;
}

static float RadianToDegree(float Radian)
{
	return Radian * 180.f / PI;
}