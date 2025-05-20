#include "effect.h"
#include <algorithm>
using namespace KamataEngine::MathUtility;
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

}

void Effect::Update()
{
	if (isFinished_) {
		return;
	}
	// 
	counter_ += 1.0f / 60.0f;

	// フェード処理
	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);

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
