#pragma once
#include"Vector3.h"

//当たり判定
struct AABB
{
	Vector3 min;//最小値
	Vector3 max;//最大値
};

inline bool isColision(const AABB& a, const AABB& b)
{
	bool hitX = (a.min.x <= b.max.x && a.max.x >= b.min.x); //x軸
	bool hitY = (a.min.y <= b.max.y && a.max.y >= b.min.y); //y軸
	bool hitZ = (a.min.z <= b.max.z && a.max.z >= b.min.z); //z軸


	if (
			hitX && hitY && hitZ
		)
	{
		//衝突
		return true;
	}
	return false;
};