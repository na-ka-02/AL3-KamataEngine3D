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
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);
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
};