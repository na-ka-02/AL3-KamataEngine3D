#pragma once
#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"
#include<numbers>
#include <Input.h>
#include<algorithm>

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
	/// <summary>
	/// 
	/// </summary>
	//const WorldTransform& Player::GetWolrdTransform();
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
	static inline const float kAcceleration = 0.05f;
	//速度減衰
	static inline const float kAttenuation = 0.2f;
	//最大速度制限
	static inline const float kLimitRunSpeed = 2.0f;
	//キャラの左右の向き
	enum class LRDirection
	{
		kRight,
		kLeft,
	};
	LRDirection lrDirection_ = LRDirection::kRight;
	//旋回開始時の角度
	float turnFirstRotationY_ = std::numbers::pi_v < float>*5.0f/2.0f;
	//旋回タイマー
	float turnTimer_ = 0.0f;
	//旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;
	//接地状態フラグ
	bool onGround_ = true;
	//重力加速度(下方向)
	static inline const float kGravityAcceleration = 0.2f;
	//最大落下速度(下方向)
	static inline const float kLimitFallSpeed = 1.5f;
	//ジャンプ初速(上方向)
	static inline const float kJumpAcceleration = 2.0f;
	//摩擦
	static inline const float kAttenuationLanding=0.02f;
};