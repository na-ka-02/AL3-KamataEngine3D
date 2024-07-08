#include "Skydome.h"
#include <cassert>

Skydome::Skydome()
{
}

Skydome::~Skydome()
{
}

void Skydome::Initialize(Model* model,ViewProjection* viewProjection)
{
	//NuLLポインタチェック
	assert(model);
	//ワールド変換の初期化
	worldTransform_.Initialize();
	//メンバ変数に記憶
	model_ = model;
	viewProjection_ = viewProjection;
}

void Skydome::Update()
{
	worldTransform_.TransferMatrix();
}

void Skydome::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
