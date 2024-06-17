#include "mathMT.h"
#include "math.h"
#include <assert.h>
#include "cmath"

//加算
Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 result = {};
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return Vector3(result);
}

//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	Vector3 result = {};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return Vector3(result);
}

//スカラー倍
Vector3 Multiply(float scalar, const Vector3& v)
{
	Vector3 result = {};
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return Vector3(result);
}

//内積 fabsf←絶対値
float Dot(const Vector3& v1, const Vector3& v2)
{
	float result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return float(result);
}

//長さ(ノルム) sqrt←ルート
float Length(const Vector3& v)
{
	float result = 0;
	result = sqrtf(Dot(v, v));
	return float(result);
}

//正規化 fabsf←絶対値
Vector3 Nomalize(const Vector3& v)
{
	Vector3 result = {};
	result.x = v.x / Length(v);
	result.y = v.y / Length(v);
	result.z = v.z / Length(v);
	return Vector3(result);
}

//1.行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result = {};
	result.m[0][0] = m1.m[0][0] + m2.m[0][0];
	result.m[0][1] = m1.m[0][1] + m2.m[0][1];
	result.m[0][2] = m1.m[0][2] + m2.m[0][2];
	result.m[0][3] = m1.m[0][3] + m2.m[0][3];
	result.m[1][0] = m1.m[1][0] + m2.m[1][0];
	result.m[1][1] = m1.m[1][1] + m2.m[1][1];
	result.m[1][2] = m1.m[1][2] + m2.m[1][2];
	result.m[1][3] = m1.m[1][3] + m2.m[1][3];
	result.m[2][0] = m1.m[2][0] + m2.m[2][0];
	result.m[2][1] = m1.m[2][1] + m2.m[2][1];
	result.m[2][2] = m1.m[2][2] + m2.m[2][2];
	result.m[2][3] = m1.m[2][3] + m2.m[2][3];
	result.m[3][0] = m1.m[3][0] + m2.m[3][0];
	result.m[3][1] = m1.m[3][1] + m2.m[3][1];
	result.m[3][2] = m1.m[3][2] + m2.m[3][2];
	result.m[3][3] = m1.m[3][3] + m2.m[3][3];
	return Matrix4x4(result);
}

//2.行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result = {};
	result.m[0][0] = m1.m[0][0] - m2.m[0][0];
	result.m[0][1] = m1.m[0][1] - m2.m[0][1];
	result.m[0][2] = m1.m[0][2] - m2.m[0][2];
	result.m[0][3] = m1.m[0][3] - m2.m[0][3];
	result.m[1][0] = m1.m[1][0] - m2.m[1][0];
	result.m[1][1] = m1.m[1][1] - m2.m[1][1];
	result.m[1][2] = m1.m[1][2] - m2.m[1][2];
	result.m[1][3] = m1.m[1][3] - m2.m[1][3];
	result.m[2][0] = m1.m[2][0] - m2.m[2][0];
	result.m[2][1] = m1.m[2][1] - m2.m[2][1];
	result.m[2][2] = m1.m[2][2] - m2.m[2][2];
	result.m[2][3] = m1.m[2][3] - m2.m[2][3];
	result.m[3][0] = m1.m[3][0] - m2.m[3][0];
	result.m[3][1] = m1.m[3][1] - m2.m[3][1];
	result.m[3][2] = m1.m[3][2] - m2.m[3][2];
	result.m[3][3] = m1.m[3][3] - m2.m[3][3];
	return Matrix4x4(result);
}

//3.行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result = {};
	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0]; result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1]; result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2]; result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];
	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0]; result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1]; result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2]; result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];
	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0]; result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1]; result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2]; result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];
	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0]; result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1]; result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2]; result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];
	return Matrix4x4(result);
}

//4.逆行列
Matrix4x4 Inverse(const Matrix4x4& m)
{
	Matrix4x4 result = {};
	const float A = /*fabsf*/(
		m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]
		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]
		);
	const float mA = (1.0f / A);

	result.m[0][0] =
		mA * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2]
			- m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]);
	result.m[0][1] =
		mA * (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2]
			+ m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]);
	result.m[0][2] =
		mA * (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2]
			- m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]);
	result.m[0][3] =
		mA * (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2]
			+ m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]);
	result.m[1][0] =
		mA * (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2]
			+ m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]);
	result.m[1][1] =
		mA * (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2]
			- m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]);
	result.m[1][2] =
		mA * (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2]
			+ m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]);
	result.m[1][3] =
		mA * (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2]
			- m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]);
	result.m[2][0] =
		mA * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][0] * m.m[3][1]
			- m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]);
	result.m[2][1] =
		mA * (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1]
			+ m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]);
	result.m[2][2] =
		mA * (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1]
			- m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]);
	result.m[2][3] =
		mA * (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1]
			+ m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]);
	result.m[3][0] =
		mA * (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1]
			+ m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]);
	result.m[3][1] =
		mA * (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1]
			- m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]);
	result.m[3][2] =
		mA * (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1]
			+ m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]);
	result.m[3][3] =
		mA * (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1]
			- m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]);

	return Matrix4x4(result);
}

//5.転置行列
Matrix4x4 Transpose(const Matrix4x4& m)
{
	Matrix4x4 result = {};
	result.m[0][0] = m.m[0][0];
	result.m[0][1] = m.m[1][0];
	result.m[0][2] = m.m[2][0];
	result.m[0][3] = m.m[3][0];
	result.m[1][0] = m.m[0][1];
	result.m[1][1] = m.m[1][1];
	result.m[1][2] = m.m[2][1];
	result.m[1][3] = m.m[3][1];
	result.m[2][0] = m.m[0][2];
	result.m[2][1] = m.m[1][2];
	result.m[2][2] = m.m[2][2];
	result.m[2][3] = m.m[3][2];
	result.m[3][0] = m.m[0][3];
	result.m[3][1] = m.m[1][3];
	result.m[3][2] = m.m[2][3];
	result.m[3][3] = m.m[3][3];
	return Matrix4x4(result);
}

//6.単位行列の作成
Matrix4x4 MakeIndentity4x4()
{
	Matrix4x4 result = {};
	result.m[0][0] = 1;
	result.m[1][1] = 1;
	result.m[2][2] = 1;
	result.m[3][3] = 1;
	return Matrix4x4(result);
}

//平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 result = {};

	result.m[0][0] = 1;
	result.m[1][1] = 1;
	result.m[2][2] = 1;
	result.m[3][3] = 1;
	result.m[3][2] = translate.z;
	result.m[3][1] = translate.y;
	result.m[3][0] = translate.x;
	return Matrix4x4(result);
}

//拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 result = {};
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1;
	return Matrix4x4(result);
}

//座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 result = {};
	float w = 0;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0]
		+ vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];

	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1]
		+ vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];

	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2]
		+ vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];

	w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3]
		+ vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	result.x /= w;
	result.y /= w;
	result.z /= w;

	return Vector3(result);
}
//X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radius)
{
	Matrix4x4 result = {};

	result.m[0][0] = 1;
	result.m[1][1] = cosf(radius);
	result.m[1][2] = sinf(radius);
	result.m[2][1] = -sinf(radius);
	result.m[2][2] = cosf(radius);
	result.m[3][3] = 1;

	return Matrix4x4(result);
}
//Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radius)
{
	Matrix4x4 result = {};

	result.m[0][0] = cosf(radius);
	result.m[0][2] = -sinf(radius);
	result.m[1][1] = 1;
	result.m[2][0] = sinf(radius);
	result.m[2][2] = cosf(radius);
	result.m[3][3] = 1;

	return Matrix4x4(result);
}
//Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radius)
{
	Matrix4x4 result = {};

	result.m[0][0] = cosf(radius);
	result.m[0][1] = sinf(radius);
	result.m[1][0] = -sinf(radius);
	result.m[1][1] = cosf(radius);
	result.m[2][2] = 1;
	result.m[3][3] = 1;

	return Matrix4x4(result);
}
//3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	Matrix4x4 makeRotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 makeRotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 makeRotateXMatrix = MakeRotateXMatrix(rotate.x);

	Matrix4x4 makeRotate = Multiply(makeRotateXMatrix, Multiply(makeRotateYMatrix, makeRotateZMatrix));

	return Matrix4x4(Multiply(MakeScaleMatrix(scale), Multiply(makeRotate, MakeTranslateMatrix(translate))));
}
//正射影行列
Matrix4x4 MakeOrthographiMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	Matrix4x4 result = {};
	result.m[0][0] = 2 / (right - left);
	result.m[1][1] = 2 / (top - bottom);
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1;
	return Matrix4x4(result);
}
//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{

	Matrix4x4 result = {};
	result.m[0][0] = 1 / aspectRatio * (1 / tan(fovY / 2));
	result.m[1][1] = 1 / tan(fovY / 2);
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);

	return Matrix4x4(result);
}
//ビューポート変換行列
Matrix4x4 MakeViewportMatirix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 result = {};
	result.m[0][0] = width / 2;
	result.m[1][1] = -(height / 2);
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][0] = left + (width / 2);
	result.m[3][1] = top + (height / 2);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1;

	return Matrix4x4(result);
}
