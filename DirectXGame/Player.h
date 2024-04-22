#pragma once
#pragma once
#include "WorldTransform.h"
#include "Model.h"

class Player
{
public:
	//������
	void Initialize(Model* model, uint32_t textureHandle);
	//�X�V
	void Update();
	//�`��
	void Draw();

private:
	//���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;
	//3D���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
};