#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

//イージング
inline float Ease(float start, float finish, float t)
{
	return (1.0f - t) * start + t * finish;
}

//イージング(Vector3)
 inline Vector3 Lerp(Vector3 start, Vector3 index, float time)
{
	Vector3 result = {};
	result.x = (1.0f - time) * start.x + time * index.x;
	result.y = (1.0f - time) * start.y + time * index.y;
	result.z = (1.0f - time) * start.z + time * index.z;
	return result;
}

//イーズイン
inline float EaseIn(float x)
{
	return 1.0f - cosf((x * (float)M_PI) / 2);
}

//イーズアウト
inline float EaseOut(float x)
{
	return sinf((x * (float)M_PI) / 2);
}