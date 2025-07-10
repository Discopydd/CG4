#pragma once
#include "KamataEngine.h"
#include <array>
#include <memory>

class NumberDrawer {
public:
    ~NumberDrawer();
    void Initialize(uint32_t textureHandle, const KamataEngine::Vector2& position);
    void Draw(int number);

private:
    static constexpr int kDigitNum = 5;
    static constexpr float kDigitWidth = 32.0f;
    static constexpr float kDigitHeight = 64.0f;

    KamataEngine::Sprite* digits_[kDigitNum] = {};
    KamataEngine::Vector2 basePos_;
};
