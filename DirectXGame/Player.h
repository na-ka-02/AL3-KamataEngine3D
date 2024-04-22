#pragma once
#pragma once
#include "WorldTransform.h"
#include "Model.h"

class Player
{
public:
	//初期化
	void Initialize(Model* model, uint32_t textureHandle);
	//更新
	void Update();
	//描画
	void Draw();

private:
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//3Dモデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};