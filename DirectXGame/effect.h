#pragma once
#include<KamataEngine.h>

using namespace KamataEngine;

class Effect {
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	KamataEngine::ObjectColor objectColor_;
	KamataEngine::Vector4 color_;
	bool isFinished_ = false;           // 終了フラグ
	float counter_ = 0.0f;              // 経過時間
	const float kDuration = 1.0f;       // 存続時間（秒）
public:
	~Effect();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);
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

	void SetScale(const Vector3& scale) { worldTransform_.scale_ = scale; }
	void SetRotate(const Vector3& rotate) { worldTransform_.rotation_ = rotate; }
	void SetTranslate(const Vector3& translate) { worldTransform_.translation_ = translate; }

};
