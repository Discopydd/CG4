#pragma once
#include "KamataEngine.h"
class Player

{
	public:
     ~Player();
    void Initialize(KamataEngine::Camera* camera);
    void Update();
    void Draw();

private:
    KamataEngine::Model* model_;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::ObjectColor objectColor;
	KamataEngine::Camera* camera_;
	KamataEngine::Input* input_ = nullptr;
	const float kSpeed = 0.2f;
};

