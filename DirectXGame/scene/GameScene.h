#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "DebugCamera.h"
#include "WorldTransform.h"
#include "vector"
#include"Player.h"
#include"Skydome.h"
#include"MapChipField.h"
#include"CameraController.h"
#include<iostream>
#include<vector>
#include<string>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	//2-4
	//表示ブロック
	void GenerateBlocks();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	//自キャラ
	Player* player_ = nullptr;
	//天球
	Skydome* skydome_ = nullptr;
	//マップチップフィールド
	MapChipField* mapChipField_;
	//追従カメラ
	CameraController* cameraController_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	//サウンドデータハンドル
	uint32_t soundDataHandle_ = 0;
	//音声再生ハンドル
	uint32_t voiceHandle_ = 0;

	//スプライト
	Sprite* sprite_ = nullptr;
	//3Dモデル
	Model* model_ = nullptr;

	//デバックカメラ有効
	bool isDebugCameraActive_ = false;
	//デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	//ImGuiで値を入力する変数
	float inputFloat3[3] = { 0,0,0 };

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	//ブロック(2-1)
	Model* blockModel_;
	//ブロック(2-2)
	Model* block_ = nullptr;
	//ブロックのテクスチャー(2-2)
	uint32_t blockTextureHandle_ = 0u;
	//ブロック用のワールド変換(可変長要素)
	//std::vectorを重ねると二次元配列になる
	std::vector<std::vector<WorldTransform*>>worldTransformBlockModels_;

	//2-3
	//天球のモデル
	Model* modelSkydome_ = nullptr;

};
