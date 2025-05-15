#pragma once
#include<KamataEngine.h>

using namespace KamataEngine;

class Particle {
private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::ObjectColor objectColor_;
	KamataEngine::Vector4 color_;
	KamataEngine::Vector3 velocity_;

	bool isFinished_ = false;           // 終了フラグ
	float counter_ = 0.0f;              // 経過時間
	const float kDuration = 1.0f;       // 存続時間（秒）
public:
	~Particle();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, Vector3 position, Vector3 velocity);
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(Camera& camera);

	/// <summary>
	/// 終了判定Getter
	/// </summary>
	bool IsFinished() const { return isFinished_; }

};