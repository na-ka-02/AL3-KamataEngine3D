#pragma once
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
};