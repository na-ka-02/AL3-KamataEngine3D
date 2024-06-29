#include "GameScene.h"
#include "TextureManager.h"
#include "ImGuiManager.h"
#include"PrimitiveDrawer.h"
#include"AxisIndicator.h"
#include"mathMT.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	//絵
	delete sprite_;
	//3Dモデル
	delete model_;
	//デバッグカメラ
	delete debugCamera_;
	//自キャラ
	delete player_;
	//敵キャラ
	//for(std::vector<Enemy*>&enemy)

	delete enemy_;
	//天球
	delete skydome_;
	//ブロック
	delete blockModel_;
	delete block_;
	//ブロック用のワールド変換
	//拡張for文で消す→とりあえず全部の要素を消せる
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlockModels_)
	{
		for (WorldTransform* worldTransformBlockModel : worldTransformBlockLine)
		{
			{
				delete worldTransformBlockModel;
			}
		}
	}
	//ブロックの中身も全部消す。clearは全部消す。
	worldTransformBlockModels_.clear();
	//天球
	delete modelSkydome_;
	//マップチップフィールドの解放
	delete mapChipField_;
	//追従カメラ
	delete cameraController_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ブロックモデルの読み込み(2-1)
	//textureHandle_ = TextureManager::Load("./Resources./cube./cube.jpg");
	//ブロックモデルの読み込み(2-2)
	blockTextureHandle_ = TextureManager::Load("./Resources./cube./cube.jpg");
	//スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, { 1000,100 });

	//3Dモデルの生成(1-3)
	model_ = Model::CreateFromOBJ("player", true);
	//自キャラの生成
	player_ = new Player();
	//座標をマップチップ番号で指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(2, 18);
	//自キャラの初期化
	player_->Initialize(model_, &viewProjection_, playerPosition);

	//3Dモデルの生成(1-3)
	model_ = Model::CreateFromOBJ("player", true);
	//敵キャラの生成
	/*for (int32_t i = 0; i < 4;++i)
	{
	Enemy*newEnemy=new Enemy();
	Vector3 enemyPosition={2,40,0};
	newEnemy->Initialize(model_, &viewProjection_, enemyPosition);

	enemies_.push_back(newEnemy);
	}
	*/
	enemy_ = new Enemy();
	//座標をマップチップ番号で指定
	Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(15, 18);
	//敵キャラの初期化
	enemy_->Initialize(model_, &viewProjection_, enemyPosition);

	//3Dモデルの生成(2-3の天球)
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	//天球の生成(2-3)
	skydome_ = new Skydome();
	//天球の初期化(2-3)
	skydome_->Initialize(modelSkydome_, &viewProjection_);

	//マップチップの呼び出し(2-4)
	mapChipField_ = new MapChipField;
	//マップチップファイルの読み込み(2-4)
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");
	//マップチップの生成(2-4)
	GenerateBlocks();

	//マップチップの当たり判定(2-7)
	//自キャラの生成
	player_ = new Player;
	//自キャラの初期化
	player_->Initialize(model_, &viewProjection_, playerPosition);
	//プレイヤーがいるマップチップの情報
	player_->SetMapChipField(mapChipField_);



	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	debugCamera_->SetFarZ(5000);


	//カメラコントローラの初期化(2-5)
	cameraController_ = new CameraController;
	//カメラコントローラ(2-5)
	cameraController_->Initialize(&viewProjection_);
	//追従対象をセット(2-5)
	cameraController_->SetTarget(player_);
	//リセット(瞬間合わせ)(2-5)
	cameraController_->Reset();
	//移動範囲の指定
	cameraController_->SetMovableArea(movableArea_);

	//ブロックモデル(2-1)
	blockModel_ = Model::Create();
	//ブロックモデル(2-2)
	block_ = Model::Create();

#pragma region 2-1
	/*
	//2-1
	//ブロック
	//要素数
	//縦
	const uint32_t kNumBlockVirtical = 10;
	//横
	const uint32_t kNumBlockHorizontal = 20;
	//ブロック1個分の横幅
	//縦
	const float kBlockHeight = 2.0f;
	//横
	const float kBlockWidth = 2.0f;
	//要素数を変更する
	//列数を設定(縦方向のブロック数)
	worldTransformBlockModels_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i)
	{
		//1列の要素数を設定(横方向のブロック数)
		worldTransformBlockModels_[i].resize(kNumBlockHorizontal);
	}

	//キューブの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i)
	{
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j)
		{
			worldTransformBlockModels_[i][j] = new WorldTransform();
			worldTransformBlockModels_[i][j]->Initialize();

			if (j % 2 == 0)
			{
				worldTransformBlockModels_[i][j]->translation_.x = kBlockWidth * j;
			}
			if (i % 2 == 0)
			{
				worldTransformBlockModels_[i][j]->translation_.y = kBlockHeight * i;
			}
		}
	}*/
#pragma endregion

#pragma endregion

	//サウンドデータの読み込み
	//soundDataHandle_ = audio_->LoadWave("fanfare.wav");
	//音声再生
	//audio_->PlayWave(soundDataHandle_);
	//音声再生
	//voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//ライン描画が参照するビュープロダクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);

	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロダクションを推定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

}

void GameScene::Update() {

	//スプライトの今の座標を取得
	Vector2 position = sprite_->GetPosition();
	//座標を{2,1}移動
	/*position.x += 1.0f;
	position.y += 1.0f;*/
	//移動した座標をスプライトに反映
	/*sprite_->SetPosition(position);*/

	//自キャラの更新
	player_->Update();
	//敵キャラの更新
	enemy_->Update();
	//天球の更新
	skydome_->Update();
	//ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlockModels_)
	{
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine)
		{
			if (!worldTransformBlock)
			{
				continue;
			}
			worldTransformBlock->matWorld_ =
				MakeAffineMatrix
				(
					worldTransformBlock->scale_,
					worldTransformBlock->rotation_,
					worldTransformBlock->translation_
				);

			worldTransformBlock->TransferMatrix();
		}
	}

	//全ての当たり判定を行う
	CheckAllCollisions();

	//スペースキーを押した瞬間
	if (input_->TriggerKey(DIK_RETURN))
	{
		//音声停止
		if (audio_->IsPlaying(voiceHandle_))
		{
			audio_->StopWave(voiceHandle_);
		}
		else
		{
			voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
		}
	}


	//デバッグカメラの更新
	debugCamera_->Update();

	//デバッグカメラ有効無効切り替え(ifdefはDebugでしか機能しない)
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE))
	{
		isDebugCameraActive_ ^= true;
	}
#endif

	//カメラの処理
	if (isDebugCameraActive_)
	{
		//デバッグの更新
		debugCamera_->Update();
		//デバッグカメラのビュー行列
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		//デバッグカメラのプロジェクション行列
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		//ビュープロジェクション行列の更新と転送
		viewProjection_.TransferMatrix();
	}
	else
	{
		//ビューポートの行列更新
		viewProjection_.UpdateMatrix();
	}

	//追従カメラの更新
	cameraController_->Update();
	//デバッグカメラと同じ感じの処理をする
	//追従カメラのビュー行列
	viewProjection_.matView = cameraController_->GetViewProjection().matView;
	//追従カメラのプロジェクション行列
	viewProjection_.matProjection = cameraController_->GetViewProjection().matProjection;
	//ビュープロジェクション行列の更新と転送
	viewProjection_.TransferMatrix();


	//デバックテキストの表示開始
	ImGui::Begin("Debug1");
	//float3入力ボックス
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	//float3スライダー
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	//変数三つ表示
	ImGui::Text("Kamata Tarou %d.%d.%d", 2050, 12, 31);
	//デバックテキスト表示終了
	ImGui::End();

	//デモウィンドウの表示を有効化
	ImGui::ShowDemoWindow();

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();


#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	//3Dモデル描画
//model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	//ブロック
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlockModels_)
	{
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine)
		{
			if (!worldTransformBlock)
			{
				continue;
			}
			blockModel_->Draw(*worldTransformBlock, viewProjection_);
		}
	}

	//自キャラの描画
	player_->Draw();
	//敵キャラの描画
	enemy_->Draw();
	//天球の描画
	skydome_->Draw();

	//デバッグカメラ←3Dモデル直下に書く
	//blockModel_->Draw(worldTransform_, debugCamera_->GetViewProjection(), blockTextureHandle_);

	//model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();

	//ラインを描画する(始点座標、終点座標、色(RGBA)の順)
	PrimitiveDrawer::GetInstance()->DrawLine3d({ 0,0,0 }, { 0,10,0 }, { 1.0f,0.0f,0.0f,1.0f });

#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);


	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//絵を描画
	//sprite_->Draw();


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion

}

#pragma region ブロック
void GameScene::GenerateBlocks()
{
	//2-4
	//ブロック
	//要素数
	//縦
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	//横
	uint32_t nNumBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	//ブロック1個分の横幅
	////縦
	//const float kBlockHeight = 2.0f;
	////横
	//const float kBlockWidth = 2.0f;
	//要素数を変更する
	//列数を設定(縦方向のブロック数)
	worldTransformBlockModels_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i)
	{
		//1列の要素数を設定(横方向のブロック数)
		worldTransformBlockModels_[i].resize(nNumBlockHorizontal);
	}

	//キューブの生成

	for (uint32_t i = 0; i < numBlockVirtical; ++i)//縦
	{
		for (uint32_t j = 0; j < nNumBlockHorizontal; ++j)//縦
		{
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock)
			{

				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlockModels_[i][j] = worldTransform;
				worldTransformBlockModels_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}
#pragma endregion

#pragma region 自キャラと敵キャラの当たり判定
void GameScene::CheckAllCollisions()
{
	//判定対象1と2の座標
	AABB aabb1{}, aabb2{};

	//自キャラの座標
	aabb1 = player_->GetAABB();

	//自キャラと敵弾全てぼ当たり判定
	/*for (Enemy* enemy : enemy_)
	{*/
	//敵弾の座標
	aabb2 = enemy_->GetAABB();
	//}
	//AABB同士の交差判定
	if (isCollision(aabb1, aabb2))
	{
		player_->OnCollision(enemy_);
		enemy_->OnCollision(player_);
	}
}


bool GameScene::isCollision(AABB playerPos, AABB enemyPos)
{
	if(aabb(playerPos,enemyPos))
	{
	return true;
	}
	return false;
}
#pragma endregion





