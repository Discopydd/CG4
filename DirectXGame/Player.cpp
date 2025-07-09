#include "Player.h"
using namespace KamataEngine;
Player::~Player()
{
	delete model_;
}

void Player::Initialize(Camera* camera)
{
	camera_ = camera;
	worldTransform_.Initialize();
	model_ = Model::CreateFromOBJ("Player", true);
	input_ = Input::GetInstance();
	worldTransform_.translation_ = { -30,0,0 };
	worldTransform_.scale_ = { 2,2,2 };
}
void Player::Update()
{ 
	Vector3 move = { 0,0,0 };
	if (input_->PushKey(DIK_A)) {
		move.x -= kSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		move.x += kSpeed;
	}if (input_->PushKey(DIK_W)) {
		move.y += kSpeed;
	}if (input_->PushKey(DIK_S)) {
		move.y -= kSpeed;
	}
	
	worldTransform_.translation_ += move;
	
	worldTransform_.UpdateMatrix();
}
void Player::Draw()
{
	model_->Draw(worldTransform_, *camera_);
}