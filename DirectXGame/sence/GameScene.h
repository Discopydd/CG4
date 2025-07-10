#pragma once
#include"KamataEngine.h"
#include "../stage.h"
#include "../Player.h"
#include "../NumberDrawer.h"
using namespace KamataEngine;
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Stage* stage_ = nullptr;
	Player* player_ = nullptr;
	NumberDrawer* numberDrawer_ = nullptr;
    uint32_t numberTexHandle_= 0;
	Camera camera_;

	uint32_t hpBarTex_ = 0;
	uint32_t damageBarTex_ = 0;
	Sprite* hpBarSprite_ = nullptr;
	Sprite* damageBarSprite_ = nullptr;

	float hpRatio_ = 1.0f; // 0.0f ～ 1.0f
	int frameCount_ = 0;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};