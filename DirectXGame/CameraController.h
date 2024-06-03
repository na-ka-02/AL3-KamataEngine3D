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
	void Initialize(ViewProjection* viewProjection);

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

private:
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	//プレイヤーの情報のポインタ
	Player* target_ = nullptr;
	//追跡対象とカメラの座標の差
	Vector3 targetOffset_ = { 0,0,-15.0f };
	//矩形
	struct Rect
	{
		float left = 0.0f;//左端
		float right = 1.0f;//右端
		float bottom = 0.0f;//下端
		float top = 1.0f;//上端
	};
	//カメラ移動範囲
	Rect movableArea_ = { 0,100,0,100 };
};
