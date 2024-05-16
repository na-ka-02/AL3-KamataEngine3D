#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	//NuLLポインタチェック
	assert(model);
	//ワールド変換の初期化
	model_=model;
	textureHandle_=textureHandle;
}

void Player::Update()
{
}

void Player::Draw()
{
}
