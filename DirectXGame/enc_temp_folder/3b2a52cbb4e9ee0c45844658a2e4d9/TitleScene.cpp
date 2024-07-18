#include "TitleScene.h"
#include <Input.h>

/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
{
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
}

/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	//タイトルバーの初期化
	titleText = new TitleText;
	titleTextModel_ = Model::CreateFromOBJ("Title", true);
	titleText->Initialize(titleTextModel_, &viewProjection_);

	//終了フラグ
	finished_ = false;
}

/// <summary>
/// 更新
/// </summary>
void TitleScene::Update()
{
	//タイトルバーの更新
	titleText->Update();
	//スペース押したらシーン切り替え
	if (Input::GetInstance()->PushKey(DIK_SPACE))
	{
		finished_ = true;
	}
	//行列の更新
	//viewProjection_.UpdateMatrix();
}

/// <summary>
/// 描画
/// </summary>
void TitleScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	//描画
	titleText->Draw();
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
}
