#pragma once
#include"Vector3.h"

class Model;
class ViewProjection;
class DeathParticles;

/// <summary>
/// デス演出用パーティクル
/// </summary>
class DeathParticles
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	///描画 
	/// </summary>
	void Draw();
	/// <summary>
	/// 
	/// </summary>
private:
	Model* model_;
	ViewProjection* viewProjection_;
};