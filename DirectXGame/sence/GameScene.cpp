#include "GameScene.h"
#include <cassert>
#include<random>
#include <ctime>
using namespace KamataEngine::MathUtility;
using namespace KamataEngine;
GameScene::GameScene() {

}

GameScene::~GameScene() {
	delete modelParticle_;
	delete modelEffect_;
	for (Effect* effect : effects_) {
		delete effect;
	}
	effects_.clear();
	delete debugCamera_;
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
	modelEffect_ = Model::CreateFromOBJ("rhombus", true);
	camera_.Initialize();
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
}

void GameScene::Update() {
	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		_isDebugCameraActrive = !_isDebugCameraActrive;
	}
#endif // _DEBUG
	if (_isDebugCameraActrive) {
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		camera_.TransferMatrix();
	} else {
		camera_.UpdateMatrix();
	}
	effects_.remove_if([](Effect* effect) {
		if (effect->IsFinished()) {
			delete effect;
			return true;
		}
		return false;
		});

	if (rand() % 20 == 0) {
        float x = (rand() / (float)RAND_MAX) * 60.0f - 30.0f;
        float y = (rand() / (float)RAND_MAX) * 40.0f - 20.0f;
        Vector3 position = { x, y, 0.0f };
        EffectBorn(position);
	}
	for (Effect* effect : effects_) {
		effect->Update();
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
	/*for (Particle* particle : particles_) {
		particle->Draw(camera_);
	}*/
	for (Effect* effect : effects_) {
		effect->Draw(camera_);
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

void GameScene::EffectBorn(Vector3 center)
{
	const int numEffects = 10;

    std::random_device seed;
    std::mt19937 rng(seed());
    std::uniform_real_distribution<float> scaleDistY(3.5f, 5.0f);  // Y方向のサイズ
	std::uniform_real_distribution<float> scaleDistX(0.5f, 1.0f);  // X方向のサイズ
    std::uniform_real_distribution<float> angleOffset(-0.3f, 0.3f); // ちょっとしたズレ

    for (int i = 0; i < numEffects; ++i) {
        float angle = i * (2.0f * 3.1415926f / numEffects); // 弧度制御
		angle += angleOffset(rng);
        Effect* effect = new Effect();
        effect->Initialize(modelEffect_);
        effect->SetTranslate(center);
        effect->SetRotate({ 0.0f, 0.0f, angle });
        effect->SetScale({ scaleDistX(rng), scaleDistY(rng), 5.0f});

        effects_.push_back(effect);
    }
}

