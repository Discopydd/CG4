#pragma once
#include"KamataEngine.h"
#include "../Parrticle.h"
#include "../effect.h"
#include "../model2.h"
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
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;

	KamataEngine::Camera camera_;

	KamataEngine::Model2* testModel_ = nullptr;
	uint32_t textureHandle_ = 0;
	KamataEngine::WorldTransform worldTransform_;

	bool _isDebugCameraActrive = false;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};