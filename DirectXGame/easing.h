#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

//イージング
float Ease(float angle1, float angle2, float t)
{
	return (1.0f - t) * angle1 + t * angle2;
}

//イーズイン
float EaseIn(float x)
{
	return 1.0f - cosf((x * (float)M_PI) / 2);
}

//イーズアウト
float EaseOut(float x)
{
	return sinf((x * (float)M_PI) / 2);
}