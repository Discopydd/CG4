#pragma once
#include<KamataEngine.h>

using namespace KamataEngine;

class Particle {
	private:
		WorldTransform worldTransform_;
		Model* model_ = nullptr;
	public:
	~Particle();
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

};