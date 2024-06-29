#include "Enemy.h"
#include <cassert>
#include "Player.h"

//初期化
void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
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
	worldTransform_.rotation_.y = 1.0f / 2.0f;
	//速度を設定する
	velocity_ = { -kWalkSpeed,0,0 };
	//経過時間
	walkTimer_ = 0.0f;
}

//更新
void Enemy::Update()
{
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();
	//タイマーを加算	
	walkTimer_ += 1.0f / 60.0f;
	//回転アニメーション
	float param = static_cast<float>(std::sin((2 * M_PI) * kWalkMotionTime) / walkTimer_);
	float radian = (kWalkMotionAngleStart + lWalkMotionAngleEnd) * (param + 1.0f) / 2.0f;
	worldTransform_.rotation_.x = static_cast<float>(radian * M_PI / 360.0f);
	//移動
	worldTransform_.translation_ += velocity_;
	//行列計算
	worldTransform_.UpdateMatrix();
}

//描画
void Enemy::Draw()
{
	//3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}

Vector3 Enemy::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos{};
	//ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

AABB Enemy::GetAABB()
{
	Vector3 worldPos = GetWorldPosition();

	AABB aabb{};

	aabb.min = { worldPos.x - kWidth / 2.0f,worldPos.y - kHeight,worldPos.z - kWidth / 2.0f };
	aabb.min = { worldPos.x + kWidth / 2.0f,worldPos.y + kHeight,worldPos.z + kWidth / 2.0f };

	return aabb;
}

void Player::OnCollision(const Enemy* enemy)
{
	(void)enemy;
	//ジャンプ初速(仮処理)
	velocity_ += Vector3(kJumpAcceleration);
}

//衝突応答
void Enemy::OnCollision(const Player* player)
{
	(void)player;
}


