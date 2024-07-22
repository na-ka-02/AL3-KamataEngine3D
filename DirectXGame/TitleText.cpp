#include "TitleText.h"
#include <cassert>

/// <summary>
/// 初期化
/// </summary>
/// <param name="model"></param>
/// <param name="viewProjection"></param>
/// <param name="position"></param>
void TitleText::Initialize(Model* model, ViewProjection* viewProjection)
{
	//NuLLポインタチェック
	assert(model);
	//ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 8,8,8 };
	worldTransform_.translation_ = { 0,0,0 };
	//メンバ変数に記憶
	model_ = model;
	viewProjection_ = viewProjection;
}

/// <summary>
/// 更新
/// </summary>
void TitleText::Update()
{
	worldTransform_.UpdateMatrix();
}

/// <summary>
/// 描画
/// </summary>
void TitleText::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
