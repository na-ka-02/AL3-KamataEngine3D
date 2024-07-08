#pragma once
#define _USE_MATH_DEFINES
#include "math.h"
#include"Vector3.h"
#include "WorldTransform.h"
#include"ObjectColor.h"
#include<array>

class Model;
class ViewProjection;
class Player;

/// <summary>
/// デス演出用パーティクル
/// </summary>
class DeathParticles
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	///描画 
	/// </summary>
	void Draw();
	/// <summary>
	/// 
	/// </summary>
private:
	Model* model_;
	ViewProjection* viewProjection_;
	WorldTransform worldTransform_;
	//パーティクルの個数
	static inline const uint32_t kNumParticles = 8;
	std::array<WorldTransform, kNumParticles>worldTransforms_;
	//存続時間(消滅までの時間)<秒>
	static inline const float kDuration = 4.0f;
	//移動の速さ
	static inline const float kSpeed = 0.1f;
	//分割した1個分の角度
	static inline const float kAngleUnit = 2.0f * static_cast<float>(M_PI) / kNumParticles;
	//終了フラグ
	bool isFinished_ = false;
	//経過時間カウント
	float counter_ = 0.0f;
	//色変更のオブジェクト
	ObjectColor objectColor_;
	//色の数値
	Vector4 color_;
};