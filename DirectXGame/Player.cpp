#include "Player.h"
#include <cassert>
#include<numbers>
#include <Input.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	//NuLLポインタチェック
	assert(model);
	//ワールド変換の初期化
	worldTransform_.Initialize();
	//メンバ変数に記憶
	model_ = model;
	worldTransform_.translation_ = position;
	viewProjection_ = viewProjection;
	//初期回転
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

void Player::Update()
{
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();
	//移動入力
	//左右移動操作
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT))
	{
		//左右加速
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT))
		{
			acceleration.x += kAcceleration;
		}
		else if (Input::GetInstance()->PushKey(DIK_LEFT))
		{
			acceleration.x -= kAcceleration;
		}//加速/減速
		velocity_ += acceleration;

		else
		{
			velocity_.x *= (1 - kAttenuation);
			if (velocity_.x * velocity_.x < 0.001f)
			{
				velocity_.x = 0;
			}
		}
	}

	//移動
	worldTransform_.translation_ += velocity_;
	//行列計算
	worldTransform_.UpdateMatrix();
}

void Player::Draw()
{
	//3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}