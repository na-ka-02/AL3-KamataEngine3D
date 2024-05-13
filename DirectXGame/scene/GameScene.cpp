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
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ブロックモデルの読み込み(2-1)
	textureHandle_ = TextureManager::Load("sample.png");
	//ブロックモデルの読み込み(2-2)
	blockTextureHandle_ = TextureManager::Load("./Resources./cube./cube.jpg");
	//スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, { 100,50 });
	//3Dモデルの生成(1-3)
	model_ = Model::Create();
	//3Dモデルの生成(2-3の天球)
	modelSkydome_=Model::CreateFromOBJ("skydome",true);
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	//ブロックモデル(2-1)
	blockModel_ = Model::Create();
	//ブロックモデル(2-2)
	block_ = Model::Create();

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
	}

	//サウンドデータの読み込み
	soundDataHandle_ = audio_->LoadWave("fanfare.wav");
	//音声再生
	audio_->PlayWave(soundDataHandle_);
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

	//スペースキーを押した瞬間
	if (input_->TriggerKey(DIK_SPACE))
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
		//
		viewProjection_.UpdateMatrix();
	}

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

	//デバッグカメラ←3Dモデル直下に書く
	blockModel_->Draw(worldTransform_, debugCamera_->GetViewProjection(), blockTextureHandle_);

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
