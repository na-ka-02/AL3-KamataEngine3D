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
