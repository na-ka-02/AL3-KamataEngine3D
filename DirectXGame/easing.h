#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

//イーズイン
float easeIn(float x)
{
	return 1.0f - cosf((x * (float)M_PI) / 2);
}
//イーズアウト
float easeOut(float x)
{
	return sinf((x * (float)M_PI) / 2);
}