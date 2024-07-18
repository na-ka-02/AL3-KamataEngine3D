#pragma once
#include "DirectXCommon.h"
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"
#include"TitleText.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleScene();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// デスフラグのgetter
	/// </summary>
	bool IsFinished()const { return finished_; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//タイトルバー
	TitleText* titleText = nullptr;
	Model* titleTextModel_ = nullptr;

	//終了フラグ
	bool finished_ = false;
};