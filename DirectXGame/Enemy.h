#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include"AABB.h"

class Player;

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
	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition();
	/// <summary>
	/// 衝突判定
	/// </summary>
	AABB GetAABB();
	/// <summary>
	/// 衝突応答
	/// </summary>
	void OnCollision(const Player* player);

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
	static inline const float kWalkMotionAngleStart = 45.0f;
	//アニメーションの周期となる時間[秒]
	static inline const float kWalkMotionTime = 3.0f;
	//最後の角度
	static inline const float lWalkMotionAngleEnd = 45.0f;
	//経過時間
	float walkTimer_ = 0.0f;
	//キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;//横
	static inline const float kHeight = 0.8f;//縦
};
