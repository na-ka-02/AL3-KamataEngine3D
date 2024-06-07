#define NOMINMAX
#include "CameraController.h"
#include"Player.h"
#include"WorldTransform.h"
#include"easing.h"
#include<algorithm>


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
	
	//自キャラの速度を取得
	Vector3 targetVelocity = target_->GetVelocity();
	
	//追従対象とオフセットと追従対象の速度からカメラの目標座標を計算
	targetIndex.x = targetWorldTransform.translation_.x + targetOffset_.x + targetVelocity.x * kVelocityBias;
	targetIndex.y = targetWorldTransform.translation_.y + targetOffset_.y + targetVelocity.y * kVelocityBias;
	targetIndex.z = targetWorldTransform.translation_.z + targetOffset_.z + targetVelocity.z * kVelocityBias;
	
	//座標補間によるゆったり追従
	viewProjection_->translation_ = Lerp(viewProjection_->translation_, targetIndex, kInteerpolationRate);
	
	//追従対象が画面外に出ないように補正
	viewProjection_->translation_.x = std::max(viewProjection_->translation_.x, targetIndex.x + margin.left);
	viewProjection_->translation_.x = std::min(viewProjection_->translation_.x, targetIndex.x + margin.right);
	viewProjection_->translation_.y = std::max(viewProjection_->translation_.y, targetIndex.y + margin.bottom);
	viewProjection_->translation_.y = std::min(viewProjection_->translation_.y, targetIndex.y + margin.top);
	
	//移動範囲制限
	//clampの中身(ビュープロジェクションの最大最小範囲を指定,左と下,右と上)で比べる
	viewProjection_->translation_.x = std::clamp(viewProjection_->translation_.x, movableArea_.left, movableArea_.right);
	viewProjection_->translation_.y = std::clamp(viewProjection_->translation_.y, movableArea_.bottom, movableArea_.top);

	//行列を更新
	viewProjection_->UpdateMatrix();
}

//カメラの瞬間合わせ
void CameraController::Reset()
{
	//追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWolrdTransform();
	
	//追従対象からカメラの座標を計算
	viewProjection_->translation_.x = targetWorldTransform.translation_.x + targetOffset_.x;
	viewProjection_->translation_.y = targetWorldTransform.translation_.y + targetOffset_.y;
	viewProjection_->translation_.z = targetWorldTransform.translation_.z + targetOffset_.z;
}


