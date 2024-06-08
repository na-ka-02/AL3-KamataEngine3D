#pragma once
#include "ViewProjection.h"

//矩形
struct Rect
{
	float left = 0.0f;//左端
	float right = 1.0f;//右端
	float bottom = 0.0f;//下端
	float top = 1.0f;//上端
};


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

	/// <summary>
	/// カメラ移動範囲
	/// </summary>
	void SetMovableArea(Rect area) { movableArea_ = area; }

private:
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	//プレイヤーの情報のポインタ
	Player* target_ = nullptr;
	//追跡対象とカメラの座標の差
	Vector3 targetOffset_ = { 0,0,-20.0f };
	//カメラの目標座標
	Vector3 targetIndex;
	//座標補間割合
	static inline const float kInteerpolationRate = 1.6f;
	//速度掛け率
	static inline const float kVelocityBias = 0.3f;
	//追従対象の各方向へのカメラ移動範囲
	static inline const Rect margin={50,-50,50,-50};
	//カメラ移動範囲
	Rect movableArea_ = { 0,100,0,100 };
};


