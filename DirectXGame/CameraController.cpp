#include "CameraController.h"
#include"Player.h"
#include"WorldTransform.h"

//コンストラクタ
CameraController::CameraController()
{
}

//デストラクタ
CameraController::~CameraController()
{
}

//初期化
void CameraController::Initialize(ViewProjection* viewProjection)
{
	viewProjection_ = viewProjection;
}

//更新
void CameraController::Update()
{

	//追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWolrdTransform();
	//追従対象とオフセットからカメラの座標を計算
	viewProjection_->translation_ = targetWorldTransform.translation_ + targetOffset_;
	//行列を更新
	viewProjection_->UpdateMatrix();
}

//カメラの瞬間合わせ
void CameraController::Reset()
{
	//追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWolrdTransform();
	//追従対象からカメラの座標を計算
	viewProjection_->translation_ = targetWorldTransform.translation_ + targetOffset_;
}


