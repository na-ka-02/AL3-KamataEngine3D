#pragma once
#include "ViewProjection.h"

//前方宣言
class Player;

///
///カメラコントローラー
/// 
class CameraController
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CameraController();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CameraController();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 追従対象のポインタ
	/// </summary>
	void SetTarget(Player* target) { target_ = target; }

	/// <summary>
	/// カメラの瞬間合わせ
	/// </summary>
	void Reset();

	/// <summary>
	/// ワールドトランスフォームを取得
	/// </summary>
	//const WorldTransform& Player::GetWorldTransform(){return worldTransform_};

private:
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	//プレイヤーの情報のポインタ
	Player* target_ = nullptr;
	//追跡対象とカメラの座標の差
	Vector3 targetOffset_ = { 0,0,-15.0f };
};