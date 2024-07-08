#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final
{
	float x;
	float y;
	float z;

	//演算子オーバーロード
	Vector3& operator+=(const Vector3& num)
	{
		x += num.x;
		y += num.y;
		z += num.z;
		return *this;
	}
};

//足し算(Vector3+Vector3)
Vector3 operator+(const Vector3& num1, const Vector3& num2);
//足し算(Vector3+float)
//Vector3 operator+(const Vector3& num1, const float num2);

//引き算(Vector3-Vector3)
Vector3 operator-(const Vector3& num1, const Vector3& num2);
//引き算(Vector3-float)
//Vector3 operator-(const Vector3& num1, const float num2);

//割り算(Vector3%Vector3)
Vector3 operator/(const Vector3& num1, const Vector3& num2);
//割り算(Vector3%float)
//Vector3 operator/(const Vector3& num1, const float num2);

//掛け算(Vector3*Vector3)
Vector3 operator*(const Vector3& num1, const Vector3& num2);
//掛け算(Vector3*float)
//Vector3 operator*(const Vector3& num1, const float num2);
