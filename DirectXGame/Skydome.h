﻿#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

///
///天球
///</summary>
class Skydome
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>

	Skydome();

	/// <summary>
	/// デストラクタ
	/// </summary>

	~Skydome();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model,ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
};
