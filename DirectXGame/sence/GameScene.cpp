#include "GameScene.h"
#include <cassert>
#include <algorithm>
using namespace KamataEngine;
using namespace KamataEngine::MathUtility;

Vector2 WorldToScreen(const Vector3& worldPos, const Matrix4x4& view, const Matrix4x4& proj, float windowWidth, float windowHeight) {
    // ワールド→ビュー→射影（w除算込み）
    Matrix4x4 vpMatrix = view * proj;
    Vector3 ndcPos = TransformCoord(worldPos, vpMatrix);  // -1.0 ~ 1.0

    // NDC → スクリーン座標へ変換
    Vector2 screenPos;
    screenPos.x = (ndcPos.x * 0.5f + 0.5f) * windowWidth;
    screenPos.y = (1.0f - (ndcPos.y * 0.5f + 0.5f)) * windowHeight;

    return screenPos;
}
GameScene::GameScene() {}

GameScene::~GameScene() {
	delete stage_;
	delete player_;
	delete damageBarSprite_;
	delete hpBarSprite_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	camera_.Initialize();
	stage_ = new Stage();
	stage_->Initialize();
	player_ = new Player();
	player_->Initialize(&camera_);

	hpBarTex_ = TextureManager::Load("HPbar.png");
	damageBarTex_ = TextureManager::Load("Damagebar.png");

	damageBarSprite_ = Sprite::Create(damageBarTex_, { 0, 0 });
	hpBarSprite_ = Sprite::Create(hpBarTex_, { 0, 0 });

	damageBarSprite_->SetSize({ 100, 20 });
	hpBarSprite_->SetSize({ 100, 20 });
	damageBarSprite_->SetColor({1.0f, 0.0f, 0.0f, 0.5f});
}

void GameScene::Update() {

	Vector3 playerPos = player_->GetWorldPosition();
	Vector2 screenPos = WorldToScreen(playerPos, camera_.matView, camera_.matProjection, 1280.0f, 720.0f);

	screenPos.x -= 50;
	screenPos.y -= 80;

	damageBarSprite_->SetPosition(screenPos);
	hpBarSprite_->SetPosition(screenPos);

	hpRatio_ -= 0.001f;
	hpRatio_ = std::clamp(hpRatio_, 0.0f, 1.0f);

	hpBarSprite_->SetSize({ 100 * hpRatio_, 20 });
	stage_->Update();
	player_->Update();
	camera_.UpdateMatrix();
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
	stage_->Draw();
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
	player_->Draw();
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);
	damageBarSprite_->Draw();
	hpBarSprite_->Draw();
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

