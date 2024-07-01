#define NOMINMAX
#include "Player.h"
#include"MapChipField.h"
#include <cassert>
#include<easing.h>
#include"DebugText.h"

//角

//エラー消す
#pragma warning(disable:4100)


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
	worldTransform_.rotation_.y = 5.0f / 2.0f;
}

void Player::Update()
{
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();
	//地面についている時
	if (onGround_)
	{
		//移動入力
		keyPush();
	}
	//空中
	else
	{
		//落下速度
		velocity_ += Vector3(0, -kGravityAcceleration, 0);
		//落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}

	//接地状態
	//着地フラグ
	bool landing = false;
	//地面との当たり判定
	//下降中かそうじゃないか
	if (velocity_.y < 0)
	{
		//Y座標が地面以下になったら着地
		if (worldTransform_.translation_.y <= 2.0f)
		{
			landing = true;
		}
	}

	//接地判定
	//ジャンプ開始
	if (onGround_)
	{
		if (velocity_.y > 0.0f)
		{
			//空中状態に移行
			onGround_ = false;
		}
	}
	else
	{
		//着地
		if (landing)
		{
			//めり込み排斥
			worldTransform_.translation_.y = 2.0f;
			//摩擦で横方向速度が減衰する
			velocity_.x *= (1.0f - kAttenuationLanding);
			//下方向速度をリセット
			velocity_.y = 0.0f;
			//接地状態に移行
			onGround_ = true;
		}
	}

	//衝突判定を初期化
	CollisionMapInfo collisionMapInfo;
	//移動量に速度の値をコピー
	collisionMapInfo.move = velocity_;
	//マップチップ衝突チェック
	CollisionMap(collisionMapInfo);
	//
	CollisionMapTop(collisionMapInfo);
	//
	groundCollision(collisionMapInfo);
	//
	wallCollision(collisionMapInfo);
	//
	resultCollisionMove(collisionMapInfo);

	velocity_ = collisionMapInfo.move;

	//移動
	worldTransform_.translation_ += velocity_;

	//旋回制御
	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 2.0f / 60.0f;
		{
			//左右の自キャラ角度テーブル
			float destinationRotationYTable[] =
			{
			std::numbers::pi_v < float> *5.0f / 2.0f,
			std::numbers::pi_v<float>*3.0f / 2.0f
			};
			//状態に応じた角度を取得する
			float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

			//自キャラの角度を設定する(線形補間)
			worldTransform_.rotation_.y = Ease(destinationRotationY, turnFirstRotationY_, turnTimer_);
		}
	}
	//行列計算
	worldTransform_.UpdateMatrix();
}

void Player::Draw()
{
	//3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}

//キー入力
void Player::keyPush()
{
	//左右移動操作
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT))
	{
		//左右加速
		Vector3 acceleration = {};
		//		//右入力
		if (Input::GetInstance()->PushKey(DIK_RIGHT))
		{
			//左移動中の右入力
			if (velocity_.x < 0.0f)
			{
				velocity_.x *= (1.0f - kAcceleration);
			}
			//右向き
			if (lrDirection_ != LRDirection::kRight)
			{
				lrDirection_ = LRDirection::kRight;
				//旋回開始時の角度を記録
				turnFirstRotationY_ = worldTransform_.rotation_.y;
				//旋回タイマーに時間を設定
				turnTimer_ = 1.0f;
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
				turnFirstRotationY_ = worldTransform_.rotation_.y;
				//旋回タイマーに時間を設定
				turnTimer_ = 1.0f;
			}
			//加速度
			acceleration.x -= kAcceleration;
		}

		//加速 / 減速
		velocity_ += acceleration;
		velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
	}//速度減衰
	else
	{
		///非入力時は移動減衰をかける
		velocity_.x *= (1 - kAttenuation);
		if (velocity_.x * velocity_.x < 0.001f)
		{
			velocity_.x = 0;
		}
	}

	//ジャンプ処理
	if (Input::GetInstance()->TriggerKey(DIK_UP))
	{
		//ジャンプ初速
		velocity_ += Vector3(0, kJumpAcceleration, 0);
	}
}

//マップチップの情報
void Player::SetMapChipField(MapChipField* mapChipfield)
{
	mapChipField_ = mapChipfield;
}

//判定結果を反映して移動させる
void Player::resultCollisionMove(const CollisionMapInfo& info)
{
	//移動
	worldTransform_.translation_ += info.move;
}

//天井に当たったか
void Player::celingCollision(const CollisionMapInfo& info)
{
	//天井に当たったら表示
	if (info.ceiling)
	{
		DebugText::GetInstance()->ConsolePrintf("hit ceiling\n");
		velocity_.y = 0;
	}
}

//地面に接しているか
void Player::groundCollision(const CollisionMapInfo& info)
{
	if (onGround_)
	{
		//移動入力
		keyPush();
	}
	//空中
	else
	{
		//落下速度
		velocity_ += Vector3(0, -kGravityAcceleration, 0);
		//落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}
	//着地フラグ
	if (info.landing)
	{
		//着地状態に切り替える(落下を止める)
		onGround_ = true;
		//着地時にX速度を減衰
		velocity_.x *= (1.0f - kAttenuationLanding);
		//Y速度をゼロにする
		velocity_.y = 0.0f;
	}
	//ジャンプ開始
	if (velocity_.y > 0.0f)
	{
		onGround_ = false;
	}
	else
	{
		//上昇あり？
		if (info.move.y <= 0)
		{
			return;
		}
		//移動後の4つの角の座標(上)
		std::array<Vector3, static_cast<uint32_t>(Corner::kNumCorner)>positionsNew{};
		for (uint32_t i = 0; i < positionsNew.size(); ++i)
		{
			positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
		}
		//マップチップ呼び出し
		MapChipType mapChipType{};
		//真下の当たり判定を行う
		bool hit = false;
		//左下点の判定
		IndexSet indexSet{};
		//座標取得
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[int(Corner::kLeftBottom)] + Vector3(0, 2.5f, 0));
		mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
		//左下が当たった判定
		if (mapChipType == MapChipType::kBlock)
		{
			hit = true;
		}
		//右下点の判定
		//座標取得
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[int(Corner::kRightBottom)] + Vector3(0, 2.5f, 0));
		mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
		//左下が当たった判定
		if (mapChipType == MapChipType::kBlock)
		{
			hit = true;
		}
		//落下開始
		if (!hit)
		{
			//空中状態に切り替える
			onGround_ = false;
		}
	}
}

//壁に接触しているか
void Player::wallCollision(const CollisionMapInfo& info)
{
	CollisionMapInfo collisionMapInfo;
	//壁接触による減速
	if (collisionMapInfo.hitWall)
	{
		velocity_.x *= (1.0f - kAttenuationWall);
	}
}

//ワールド座標を取得
Vector3 Player::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos{};
	//ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

//AABB
AABB Player::GetAABB()
{
	Vector3 worldPos = GetWorldPosition();

	AABB aabb{};

	aabb.min = { worldPos.x - kWidth / 2.0f,worldPos.y - kHeight,worldPos.z - kWidth / 2.0f };
	aabb.max = { worldPos.x + kWidth / 2.0f,worldPos.y + kHeight,worldPos.z + kWidth / 2.0f };

	return aabb;
}



//マップチップとプレイヤーの衝突判定
void Player::CollisionMap(CollisionMapInfo& info)
{
	//上判定
	CollisionMapTop(info);
	//下判定
	CollisionMapBottom(info);
	//右判定
	CollisionMapRight(info);
	//左判定
	CollisionMapLeft(info);
}

//移動後の4つの角の座標
//上角衝突判定
void Player::CollisionMapTop(CollisionMapInfo& info)
{

	//上昇あり？
	if (info.move.y <= 0)
	{
		return;
	}
	//移動後の4つの角の座標(上)
	std::array<Vector3, static_cast<uint32_t>(Corner::kNumCorner)>positionsNew{};
	for (uint32_t i = 0; i < positionsNew.size(); ++i)
	{
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}

	//マップチップ呼び出し
	MapChipType  mapChipType{};
	//真上の当たり判定を行う
	bool hit = false;
	//左上点の判定
	IndexSet indexSet{};
	//座標取得
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[int(Corner::kLeftTop)]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	//左上が当たった判定
	if (mapChipType == MapChipType::kBlock)
	{
		hit = true;
	}
	//右上点の判定
	//座標取得
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[int(Corner::kRightTop)]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	//右上が当たった判定
	if (mapChipType == MapChipType::kBlock)
	{
		hit = true;
	}

	//ブロックにヒット?
	if (hit)
	{
		//めり込みを排除する方向に移動量を設定する
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);
		//めり込み先ブロックの移動矩形
		Rect rect = mapChipField_->GetRectbyIndex(indexSet.xIndex, indexSet.yIndex);
		info.move.y = std::max(0.0f, rect.bottom - worldTransform_.translation_.y - kHeight / 2 - kBlank);
		//天井に当たったことを記録する
		info.ceiling = true;
	}
}

//下角衝突判定
void Player::CollisionMapBottom(CollisionMapInfo& info)
{
	//降下あり?
	if (info.move.y >= 0)
	{
		return;
	}
	//移動後の4つの角の座標の計算(下)
	std::array<Vector3, static_cast<uint32_t>(Corner::kNumCorner)>positionsNew{};
	for (uint32_t i = 0; i < positionsNew.size(); ++i)
	{
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}
	//マップチップ呼び出し
	MapChipType mapChipType{};
	//真下の当たり判定を行う
	bool hit = false;
	//左下点の判定
	IndexSet indexSet{};
	//座標取得
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[int(Corner::kLeftBottom)]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	//左下が当たった判定
	if (mapChipType == MapChipType::kBlock)
	{
		hit = true;
	}
	//右下点の判定
	//座標取得
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[int(Corner::kRightBottom)]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	//右下が当たった判定
	if (mapChipType == MapChipType::kBlock)
	{
		hit = true;
	}

	//ブロックにヒット?
	if (hit)
	{
		//めり込みを排除する方向に移動量を設定する
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);
		//めり込み先ブロックの移動矩形
		Rect rect = mapChipField_->GetRectbyIndex(indexSet.xIndex, indexSet.yIndex);
		info.move.y = std::min(0.0f, rect.top - worldTransform_.translation_.y + kHeight / 2 + kBlank);
		//床に当たったことを記録する
		info.landing = true;
	}
}

//右角衝突判定
void Player::CollisionMapRight(CollisionMapInfo& info)
{
	//右移動アリ?
	if (info.move.x)
	{
		return;
	}

	//右上と右下の当たり判定
	//右上点の判定
	//移動後の4つの角の座標の計算(下)
	std::array<Vector3, static_cast<uint32_t>(Corner::kNumCorner)>positionsNew{};
	for (uint32_t i = 0; i < positionsNew.size(); ++i)
	{
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}
	//マップチップ呼び出し
	MapChipType mapChipType{};
	//真下の当たり判定を行う
	bool hit = false;
	IndexSet indexSet{};
	//座標取得
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[int(Corner::kRightTop)]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	//右上が当たった判定
	if (mapChipType == MapChipType::kBlock)
	{
		hit = true;
	}

	//右下点の判定
	//座標取得
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[int(Corner::kRightBottom)]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	//右下が当たった判定
	if (mapChipType == MapChipType::kBlock)
	{
		hit = true;
	}

	//ブロックにヒット?
	if (hit)
	{
		//めり込みを排除する方向に移動量を設定する
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);
		//めり込み先ブロックの移動矩形
		Rect rect = mapChipField_->GetRectbyIndex(indexSet.xIndex, indexSet.yIndex);
		info.move.x = std::max(0.0f, rect.left - worldTransform_.translation_.x + kWidth / 2 - kBlank);
		//壁に当たったことを記録する
		info.hitWall = true;
	}
}

//左角衝突判定
void Player::CollisionMapLeft(CollisionMapInfo& info)
{
	//左移動アリ?
	if (info.move.x)
	{
		return;
	}

	//左上と左下の当たり判定
	//左上点の判定
	//移動後の4つの角の座標の計算(下)
	std::array<Vector3, static_cast<uint32_t>(Corner::kNumCorner)>positionsNew{};
	for (uint32_t i = 0; i < positionsNew.size(); ++i)
	{
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}
	//マップチップ呼び出し
	MapChipType mapChipType{};
	//真下の当たり判定を行う
	bool hit = false;
	IndexSet indexSet{};
	//座標取得
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[int(Corner::kLeftTop)]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	//左上が当たった判定
	if (mapChipType == MapChipType::kBlock)
	{
		hit = true;
	}

	//左下点の判定
	//座標取得
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[int(Corner::kLeftBottom)]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	//左下が当たった判定
	if (mapChipType == MapChipType::kBlock)
	{
		hit = true;
	}

	//ブロックにヒット?
	if (hit)
	{
		//めり込みを排除する方向に移動量を設定する
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);
		//めり込み先ブロックの移動矩形
		Rect rect = mapChipField_->GetRectbyIndex(indexSet.xIndex, indexSet.yIndex);
		info.move.x = std::min(0.0f, rect.right - worldTransform_.translation_.x - kWidth / 2 + kBlank);
		//壁に当たったことを記録する
		info.hitWall = true;
	}
}

//角の当たり判定
Vector3 Player::CornerPosition(const Vector3& center, Corner corner)
{
	Vector3 offsetTable[kNumCorner] =
	{
	{ +kWidth / 2.0f,-kHeight / 2.0f,0 },
	{ -kWidth / 2.0f,-kHeight / 2.0f,0 },
	{ +kWidth / 2.0f,+kHeight / 2.0f,0 },
	{ -kWidth / 2.0f,+kHeight / 2.0f,0 }
	};
	return center + offsetTable[static_cast<uint32_t>(corner)];
}
