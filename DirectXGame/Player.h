#pragma once
#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"
#include<numbers>
#include <Input.h>
#include<algorithm>

class MapChipField;

//キャラの左右の向き
enum class LRDirection
{
	kRight,
	kLeft,
};


//角
enum Corner
{
	kRightBottom,//右下
	kLeftBottom,//左下
	kRightTop,//右上
	kLeftTop,//左上
	kNumCorner//要素数
};

//衝突判定フラグ
struct CollisionMapInfo
{
	//天井衝突フラグ
	bool ceiling = false;
	//着地フラグ
	bool landing = false;
	//壁接触フラグ
	bool hitWall = false;
	//移動量
	Vector3 move;
};

class Player
{
public:
	///コンストラクタ
	Player();

	///デストラクタ
	~Player();

	/// <summary>
	/// 初期化
	/// モデルのポインタ
	/// </summary>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 移動処理関数
	/// </summary>
	void keyPush();
	/// <summary>
	/// ワールドトランスフォームを返す
	/// </summary>
	WorldTransform& GetWolrdTransform() { return worldTransform_; }
	/// <summary>
	/// 追従カメラの速度加算
	/// </summary>
	const Vector3& GetVelocity()const { return velocity_; }
	/// <summary>
	/// マップチップの情報を取得
	/// </summary>
	void SetMapChipField(MapChipField* mapChipfield);
	/// <summary>
	/// 判定結果を反映して移動させる
	/// </summary>
	void resultCollisionMove(const CollisionMapInfo& info);
	/// <summary>
	/// 天井に接触してるか
	/// </summary>
	void celingCollision(const CollisionMapInfo& info);
	/// <summary>
	/// 地面に接しているか
	/// </summary>
	void groundCollision(const CollisionMapInfo& info);
	/// <summary>
	///壁に接触しているか 
	/// </summary>
	void wallCollision(const CollisionMapInfo& info);

private:
	/// <summary>
	/// 移動処理関数
	/// </summary>
	void CollisionMap(CollisionMapInfo& info);
	void CollisionMapTop(CollisionMapInfo& info);
	void CollisionMapBottom(CollisionMapInfo& info);
	void CollisionMapRight(CollisionMapInfo& info);
	void CollisionMapLeft(CollisionMapInfo& info);
	/// <summary>
	/// 指定した角の座標計算
	/// </summary>
	Vector3 CornerPosition(const Vector3& center, Corner corner);
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//3Dモデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	//マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;
	//速度
	Vector3 velocity_ = {};
	//加速度
	static inline const float kAcceleration = 0.03f;
	//速度減衰
	static inline const float kAttenuation = 0.1f;
	//着地時の速度減衰率
	static inline const float kAttenuationWall = 0.2f;
	//最大速度制限
	static inline const float kLimitRunSpeed = 1.3f;
	LRDirection lrDirection_ = LRDirection::kRight;
	//旋回開始時の角度
	float turnFirstRotationY_ = std::numbers::pi_v < float>*5.0f / 2.0f;
	//旋回タイマー
	float turnTimer_ = 0.0f;
	//旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;
	//接地状態フラグ
	bool onGround_ = true;
	//重力加速度(下方向)
	static inline const float kGravityAcceleration = 0.2f;
	//最大落下速度(下方向)
	static inline const float kLimitFallSpeed = 1.5f;
	//ジャンプ初速(上方向)
	static inline const float kJumpAcceleration = 2.0f;
	//摩擦、着地時の速度減衰率
	static inline const float kAttenuationLanding = 0.02f;
	//キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;//横
	static inline const float kHeight = 0.8f;//縦
	//ブロックにのめり込む
	static inline const float kBlank = 0.8f;
};
