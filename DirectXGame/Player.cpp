#define NOMINMAX
#include "Player.h"
#include <cassert>
#include<numbers>
#include <Input.h>
#include<algorithm>
#include<easing.h>

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
	//接地状態
	if (onGround_) {
		//移動入力
		//左右移動操作
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT))
		{
			//左右加速
			Vector3 acceleration = {};
			//右入力
			if (Input::GetInstance()->PushKey(DIK_RIGHT))
			{
				//左移動中の右入力
				if (velocity_.x < 0.0f)
				{
					velocity_.x += (1.0f - kAcceleration);
				}
				//右向き
				if (lrDirection_ != LRDirection::kRight)
				{
					lrDirection_ = LRDirection::kRight;
					//旋回開始時の角度を記録
					turnFirstRotationY_;
					//旋回タイマーに時間を設定
					turnTimer_ = 0.5f;
				}
				//加速度
				acceleration.x += kAcceleration;
			}
			//左入力
			else if (Input::GetInstance()->PushKey(DIK_LEFT))
			{
				//右移動中の左入力
				if (velocity_.x > 0.0f)
				{
					velocity_.x *= (1.0f - kAttenuation);
				}
				//左向き
				if (lrDirection_ != LRDirection::kLeft)
				{
					lrDirection_ = LRDirection::kLeft;
					//旋回開始時の角度を記録
					turnFirstRotationY_;
					//旋回タイマーに時間を設定
					turnTimer_ = 0.5f;
				}
				//加速度
				acceleration.x -= kAcceleration;
			}
			//加速/減速

			velocity_ += acceleration;
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
			//旋回制御
			if (turnTimer_ > 0.0f) {
				turnTimer_ -= 1.0f / 60.0f;
				{
					//左右の自キャラ角度テーブル
					float destinationRotationYTable[] =
					{
					std::numbers::pi_v < float>*5.0f / 2.0f,
					std::numbers::pi_v<float>*3.0f / 2.0f
					};
					//状態に応じた角度を取得する
					//float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
					//自キャラの角度を設定する(線形補間)
					worldTransform_.rotation_.y = easeIn(turnTimer_);
				}
			}
			else
			{
				velocity_.x *= (1 - kAttenuation);
				if (velocity_.x * velocity_.x < 0.001f)
				{
					velocity_.x = 0;
				}
			}
		}
	}
	//移動
	worldTransform_.translation_ += velocity_;
	//着地フラグ
	bool landing=false;
	//下降中かそうじゃないか
	if (velocity_.y < 0)
	{
	//Y座標が地面以下になったら着地
		if(worldTransform_.translation_.y<=1.0f)
		{
		landing=true;
		}
	}
	//ジャンプ処理
	if (Input::GetInstance()->PushKey(DIK_UP))
	{
		//ジャンプ初速
		velocity_ += Vector3(0, kJumpAcceleration, 0);
	}
	//空中
	else
	{
		//落下速度
		velocity_ += Vector3(0, -kGravityAcceleration, 0);
		//落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}

	//行列計算
	worldTransform_.UpdateMatrix();
}

void Player::Draw()
{
	//3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}