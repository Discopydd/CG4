#include "effect.h"
using namespace KamataEngine::MathUtility;
Effect::~Effect()
{

}

void Effect::Initialize(Model* model)
{
	assert(model);

	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.scale_ = { 5,5,5 };
	worldTransform_.rotation_.z = -MathUtility::PI / 4.0f;

}

void Effect::Update()
{
	worldTransform_.UpdateMatrix();
}

void Effect::Draw(Camera& camera)
{
	model_->Draw(worldTransform_, camera);
}
