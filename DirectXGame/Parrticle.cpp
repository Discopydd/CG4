#include "Parrticle.h"
using namespace MathUtility;
Particle::~Particle()
{

}

void Particle::Initialize(Model* model,Vector3 position)
{
	assert(model);

	model_ = model;
	objectColor_.Initialize();
	color_ = { 1,1,0,1 };
	worldTransform_.translation_ = position;
	worldTransform_.Initialize();
}

void Particle::Update()
{
	//worldTransform_.translation_ += {0.0f, 0.1f, 0.0f};
	objectColor_.SetColor(color_);
	worldTransform_.UpdateMatrix();
}

void Particle::Draw(Camera& camera)
{
	model_->Draw(worldTransform_, camera,&objectColor_);
}
