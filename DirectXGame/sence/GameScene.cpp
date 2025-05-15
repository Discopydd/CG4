#include "GameScene.h"
#include <cassert>
#include<random>
#include <ctime>
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
	srand((unsigned)time(NULL));
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	modelParticle_ = Model::CreateSphere(4, 4);
	camera_.Initialize();
}

void GameScene::Update() {

	particles_.remove_if([](Particle* particle) {
		if (particle->IsFinished()) {
			delete particle;
			return true;
		}
		return false;
		});

	if (rand() % 20 == 0) {
		float x = (rand() / (float)RAND_MAX) * 60.0f - 30.0f;
		float y = (rand() / (float)RAND_MAX) * 40.0f - 20.0f;
		Vector3 position = { x, y, 0.0f };
		ParticleBorn(position);
	}
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

void GameScene::ParticleBorn(Vector3 position)
{
	std::random_device seedGenerator;
	std::mt19937 randomEngine(seedGenerator());
	std::uniform_real_distribution<float>distribution(-1.0f, 1.0f);

	for (int i = 0; i < 30; i++) {
		Particle* particle = new Particle();

		Vector3 velocity = { distribution(randomEngine), distribution(randomEngine), 0 };
		Normalize(velocity);
		velocity *= distribution(randomEngine);
		velocity *= 0.1f;

		particle->Initialize(modelParticle_, position, velocity);
		particles_.push_back(particle);
	}
}
