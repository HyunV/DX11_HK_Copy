#pragma once

#include "Vector4.h"

union __declspec(align(16)) Matrix
{
	DirectX::XMMATRIX	m;

	struct
	{
		float	_11, _12, _13, _14;
		float	_21, _22, _23, _24;
		float	_31, _32, _33, _34;
		float	_41, _42, _43, _44;
	};

	Vector4	v[4];

	Matrix();
	Matrix(const Matrix& _m);
	Matrix(const DirectX::XMMATRIX& _m);
	Matrix(Vector4 _v[4]);

	Vector4& operator [] (int Index);

	Matrix operator = (const Matrix& _m);
	Matrix operator = (const DirectX::XMMATRIX& _m);

	Matrix operator * (const Matrix& _m)	const;
	Matrix operator * (const DirectX::XMMATRIX& _m)	const;

	void Identity(); //단위행렬 변환
	void Transpose();//행렬 전치 행과 열 위치 바꿔주는거
	void Inverse();  //역행렬

	// 최종 월드행렬 = 크기행렬 * 자전행렬 * 이동행렬 * 공전행렬 * 부모행렬

	//크기행렬
	void Scaling(const struct Vector3& _v);
	void Scaling(float x, float y, float z);
	void Scaling(const struct Vector2& _v);
	void Scaling(float x, float y);

	//위치행렬
	void Rotation(const struct Vector3& _v);
	void Rotation(float x, float y, float z);
	void RotationX(float x);
	void RotationY(float y);
	void RotationZ(float z);
	void RotationQuaternion(const struct Vector4& q);
	void RotationAxis(const struct Vector3& Axis, float Angle);

	//이동행렬
	void Translation(const struct Vector3& _v); 
	void Translation(float x, float y, float z);
	void Translation(const struct Vector2& _v);
	void Translation(float x, float y);



	// Static은 원하는 기준치가 있을때 해준다. 뭐 스케일을 10, 10, 10 늘리고 싶다던가
	static Matrix StaticTranspose(const Matrix& _m);
	static Matrix StaticInverse(const Matrix& _m);

	static Matrix StaticScaling(const struct Vector3& _v);
	static Matrix StaticScaling(float x, float y, float z);
	static Matrix StaticScaling(const struct Vector2& _v);
	static Matrix StaticScaling(float x, float y);
	static Matrix StaticRotation(const struct Vector3& _v);
	static Matrix StaticRotation(float x, float y, float z);
	static Matrix StaticRotationX(float x);
	static Matrix StaticRotationY(float y);
	static Matrix StaticRotationZ(float z);
	static Matrix StaticRotationQuaternion(const struct Vector4& q);
	static Matrix StaticRotationAxis(const struct Vector3& Axis, float Angle);
	static Matrix StaticTranslation(const struct Vector3& _v);
	static Matrix StaticTranslation(float x, float y, float z);
	static Matrix StaticTranslation(const struct Vector2& _v);
	static Matrix StaticTranslation(float x, float y);
};

