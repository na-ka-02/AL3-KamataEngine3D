﻿#include "Player.h"
#include <cassert>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection)
{
	//NuLLポインタチェック
	assert(model);
	//ワールド変換の初期化
	worldTransform_.Initialize();
	//メンバ変数に記憶
	model_ = model;
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;
}

void Player::Update()
{
	worldTransform_.TransferMatrix();
}

void Player::Draw()
{
	//3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}