#include "GameScene.h"
#include <cassert>
using namespace KamataEngine::MathUtility;
using namespace KamataEngine;
GameScene::GameScene() {

}

GameScene::~GameScene() {
	Model2::StaticFinalize();
	delete testModel_;
	delete debugCamera_;
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	camera_.Initialize();
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	Model2::StaticInitialize();
	testModel_ = Model2::CreateRing(128, 5.0f, 10.0f);
	textureHandle_ = TextureManager::Load("gradationLine.png");
	worldTransform_.Initialize();
	objectColor_.Initialize();
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
	}
	else {
		camera_.UpdateMatrix();
	}
	
	static float time = 0.0f;
	time += 1.0f / 60.0f;

	float scale = 1.0f + 0.1f * std::sin(time * 2.0f);
	worldTransform_.scale_ = { scale, scale, 1.0f };

	//testModel_->SetAlpha(0.6f + 0.4f * std::sin(time * 2.0f));

	float h = std::fmod(time * 60.0f, 360.0f);
	float s = 1.0f;
	float v = 1.0f;

	float c = v * s;
	float x = c * (1 - fabsf(fmodf(h / 60.0f, 2.0f) - 1));
	float m = v - c;

	float r, g, b;
	if (h < 60) { r = c; g = x; b = 0; }
	else if (h < 120) { r = x; g = c; b = 0; }
	else if (h < 180) { r = 0; g = c; b = x; }
	else if (h < 240) { r = 0; g = x; b = c; }
	else if (h < 300) { r = x; g = 0; b = c; }
	else { r = c; g = 0; b = x; }

	//Vector4 ringColor = { r + m, g + m, b + m, 0.6f + 0.4f * std::sin(time * 2.0f) };
	Vector4 ringColor = { r + m, g + m, b + m, 1.0f };
	objectColor_.SetColor(ringColor);


	worldTransform_.rotation_.z -= 0.02f;
	worldTransform_.UpdateMatrix();
	
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
	Model2::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	testModel_->Draw(worldTransform_, camera_, textureHandle_,&objectColor_);
	// 3Dオブジェクト描画後処理
	Model2::PostDraw();
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

