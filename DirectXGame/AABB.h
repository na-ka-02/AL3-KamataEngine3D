#pragma once
#include"Vector3.h"

//当たり判定
struct AABB
{
	Vector3 min;//最小値
	Vector3 max;//最大値
};

bool aabb(const AABB&a, const AABB& b);