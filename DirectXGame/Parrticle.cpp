#include "Parrticle.h"
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
}

void Particle::Update()
{
	worldTransform_.translation_ += velocity_;
	objectColor_.SetColor(color_);
	worldTransform_.UpdateMatrix();
}

void Particle::Draw(Camera& camera)
{
	model_->Draw(worldTransform_, camera,&objectColor_);
}
