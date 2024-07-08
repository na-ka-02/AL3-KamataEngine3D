#include"Vector3.h"

//足し算(Vector3+Vector3)
Vector3 operator+(const Vector3& num1, const Vector3& num2)
{
	// TODO: return ステートメントをここに挿入します
	Vector3 result{};
	result.x = num1.x + num2.x;
	result.y = num1.y + num2.y;
	result.z = num1.z + num2.z;
	return result;
}

//引き算(Vector3-Vector3)
Vector3 operator-(const Vector3& num1, const Vector3& num2)
{
	// TODO: return ステートメントをここに挿入します
	Vector3 result{};
	result.x = num1.x - num2.x;
	result.y = num1.y - num2.y;
	result.z = num1.z - num2.z;
	return result;
}

//割り算(Vector3%Vector3)
Vector3 operator/(const Vector3& num1, const Vector3& num2)
{
	// TODO: return ステートメントをここに挿入します
	Vector3 result{};
	result.x = num1.x / num2.x;
	result.y = num1.y / num2.y;
	result.z = num1.z / num2.z;
	return result;
}

//掛け算(Vector3*Vector3)
Vector3 operator*(const Vector3& num1, const Vector3& num2)
{
	// TODO: return ステートメ
	Vector3 result{};
	result.x = num1.x * num2.x;
	result.y = num1.y * num2.y;
	result.z = num1.z * num2.z;
	return result;
}