#pragma once
#include"KamataEngine.h"
#include "../Parrticle.h"
#include "../effect.h"

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

	void ParticleBorn(KamataEngine::Vector3 position);

	void EffectBorn(KamataEngine::Vector3 center);
private: // メンバ変数
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;

	KamataEngine::Camera camera_;
	KamataEngine::Model* modelParticle_ = nullptr;

	std::list<Particle*>particles_;

	KamataEngine::Model* modelEffect_ = nullptr;
	std::list<Effect*> effects_;

	bool _isDebugCameraActrive = false;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};