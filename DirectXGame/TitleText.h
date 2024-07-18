#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"

class TitleText
{
public:
	/// <summary>
	/// 初期化
	/// モデルのポインタ
	/// </summary>
	void Initialize(Model* model, ViewProjection* viewProjection);
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
private:
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection* viewProjection_;
	//3Dモデル
	Model* model_ = nullptr;
};