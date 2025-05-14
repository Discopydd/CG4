#include "Parrticle.h"
#include <algorithm>
using namespace MathUtility;
Particle::~Particle()
{

}

void Particle::Initialize(Model* model,Vector3 position,Vector3 velocity)
{
	assert(model);

	model_ = model;
	objectColor_.Initialize();
	color_ = { 1,1,0,1 };
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 0.2f,0.2f,0.2f };

	counter_ = 0.0f;
	isFinished_ = false;
}

void Particle::Update()
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
	worldTransform_.translation_ += velocity_;
	objectColor_.SetColor(color_);
	worldTransform_.UpdateMatrix();
}

void Particle::Draw(Camera& camera)
{
	model_->Draw(worldTransform_, camera,&objectColor_);
}
