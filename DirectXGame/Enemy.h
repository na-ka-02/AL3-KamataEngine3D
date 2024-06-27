﻿#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"
#define _USE_MATH_DEFINES
#include "math.h"

class Enemy
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//3Dモデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	//歩行の速さ
	static inline const float kWalkSpeed = 0.1f;
	//速度
	Vector3 velocity_ = {};
	//最初の角度
	static inline const float kWalkMotionAngleStart = static_cast<float>(cosf((2 / 3) * M_PI));
	//アニメーションの周期となる時間[秒]
	static inline const float kWalkMotionTime = 3.0f;
	//最後の角度
	static inline const float lWalkMotionAngleEnd = static_cast<float>(cos((4 / 3) * M_PI));
	//経過時間
	float walkTimer_ = 0.0f;
};
