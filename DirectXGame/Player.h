﻿#pragma once
#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"

class Player
{
public:
	///コンストラクタ
	Player();

	///デストラクタ
	~Player();

	/// <summary>
	/// 初期化
	/// モデルのポインタ
	/// </summary>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	/// <summary>
	/// 更新処理
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
	//速度
	Vector3 velocity_ = {};
	//加速度
	static inline const float kAcceleration = 0.5f;
	//速度減衰
	static inline const float kAttenuation = 0.5f;
	//最大速度制限
	static inline const float kLimitRunSpeed = 0.3f;
	//キャラの左右の向き
	enum class LRDirection
	{
		kRight,
		kLeft,
	};
	LRDirection lrDirection_ = LRDirection::kRight;
	//旋回開始時の角度
	float turnFirstRotationY_ = 5.0f / 2.0f;
	//旋回タイマー
	float turnTimer_ = 0.0f;
	//旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;
	//接地状態フラグ
	bool onGround_ = true;
	//重力加速度(下方向)
	static inline const float kGravityAcceleration = 0.98f;
	//最大落下速度(下方向)
	static inline const float kLimitFallSpeed = 0.49f;
	//ジャンプ初速(上方向)
	static inline const float kJumpAcceleration = 0.98;
};