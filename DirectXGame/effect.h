#pragma once
#include<KamataEngine.h>

class Effect {
private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::ObjectColor objectColor_;
	KamataEngine::Vector4 color_;
	bool isFinished_ = false;           // 終了フラグ
	float counter_ = 0.0f;              // 経過時間
	const float kDuration = 1.0f;       // 存続時間（秒）
	KamataEngine::Vector3 baseScale_ = {1.0f, 1.0f, 1.0f};
public:
	~Effect();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model* model);
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(KamataEngine::Camera& camera);
	/// <summary>
	/// 終了判定Getter
	/// </summary>
	bool IsFinished() const { return isFinished_; }

	void SetScale(const KamataEngine::Vector3& scale) { worldTransform_.scale_ = scale; }
	void SetRotate(const KamataEngine::Vector3& rotate) { worldTransform_.rotation_ = rotate; }
	void SetTranslate(const KamataEngine::Vector3& translate) { worldTransform_.translation_ = translate; }

};
