#pragma once
#pragma once
#include "WorldTransform.h"
#include "Model.h"

class Player
{
public:
	/// <summary>
	/// 初期化
	/// モデルのポインタ
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);
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

};