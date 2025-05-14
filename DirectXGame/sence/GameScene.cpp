#include "GameScene.h"
#include <cassert>
#include<random>
using namespace KamataEngine::MathUtility;

GameScene::GameScene() {

}

GameScene::~GameScene() {
	delete modelParticle_;
	for (Particle* particle : particles_) {
		delete particle;
	}
	particles_.clear();
}

void GameScene::Initialize() {
	std::random_device seedGenerator;
	std::mt19937 randomEngine(seedGenerator());
	std::uniform_real_distribution<float>distribution(-1.0f, 1.0f);
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	modelParticle_ = Model::CreateSphere(4, 4);
	camera_.Initialize();

	//パーティクルの生成
	for (int i = 0; i < 150; i++) {
		Particle* particle = new Particle();
		//位置
		Vector3 position = { 0.0f,0.0f,0.0f };
		//移動量
		Vector3 velocity = { distribution(randomEngine),distribution(randomEngine),0 };
		Normalize(velocity);                            // 方向单位化
		velocity *= distribution(randomEngine);         // 加上一个随机的速度幅度
		velocity *= 0.1f;
		//パーティクルの初期化
		particle->Initialize(modelParticle_, position, velocity);

		particles_.push_back(particle);
	}
}

void GameScene::Update() {
	for (Particle* particle : particles_) {
		particle->Update();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	for (Particle* particle : particles_) {
		particle->Draw(camera_);
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}