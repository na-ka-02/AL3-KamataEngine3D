#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	//NuLLポインタチェック
	assert(model);
	//ワールド変換の初期化
	worldTransform_;
}
