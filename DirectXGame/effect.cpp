#include "effect.h"
#include <algorithm>
using namespace KamataEngine::MathUtility;
using namespace KamataEngine;
Effect::~Effect()
{

}

void Effect::Initialize(Model* model)
{
	assert(model);

	model_ = model;
	objectColor_.Initialize();
	worldTransform_.Initialize();
	color_ = { 1,1,1,1 };
	worldTransform_.scale_ = { 0.5,5,5 };

	counter_ = 0.0f;
	isFinished_ = false;
	baseScale_ = worldTransform_.scale_;
}

void Effect::Update()
{
	if (isFinished_) return;

	counter_ += 1.0f / 60.0f;

	// アルファの点滅効果
	float alphaBase = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);
	float flicker = std::abs(std::sin(counter_ * 20.0f));
	color_.w = alphaBase * (0.5f + 0.5f * flicker);

	// カラーグラデーション（発光感の演出）
	float glow = std::sin(counter_ * 12.0f) * 0.5f + 0.5f;
	color_.x = glow;
	color_.y = glow * 0.2f;
	color_.z = 1.0f - glow * 0.5f;

	// 多軸回転（Z軸＋揺れ）
	worldTransform_.rotation_.z += 0.1f + std::sin(counter_ * 10.0f) * 0.05f;

	// 拡大縮小のパルス（高周波と低周波の合成）
	float pulse = std::sin(counter_ * 6.0f) * 0.3f + 1.0f;
	worldTransform_.scale_.x = baseScale_.x * pulse;
	worldTransform_.scale_.y = baseScale_.y * pulse;

	// 寿命終了チェック
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		isFinished_ = true;
	}
	objectColor_.SetColor(color_);
	worldTransform_.UpdateMatrix();
}

void Effect::Draw(Camera& camera)
{
	model_->Draw(worldTransform_, camera,&objectColor_);
}
