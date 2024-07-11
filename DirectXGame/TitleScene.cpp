#include "TitleScene.h"
#include <Input.h>

/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize()
{
}

/// <summary>
/// 更新
/// </summary>
void TitleScene::Update()
{
	if (Input::GetInstance()->PushKey(DIK_SPACE))
	{
		finished_ = true;
	}
}

/// <summary>
/// 描画
/// </summary>
void TitleScene::Draw()
{
}
