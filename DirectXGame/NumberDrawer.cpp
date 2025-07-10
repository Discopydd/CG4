#include "NumberDrawer.h"
using namespace KamataEngine;
NumberDrawer::~NumberDrawer()
{
     for (int i = 0; i < kDigitNum; ++i) {
        delete digits_[i];
        digits_[i] = nullptr;
    }
}
void NumberDrawer::Initialize(uint32_t textureHandle, const Vector2& position) {
    basePos_ = position;

    for (int i = 0; i < kDigitNum; i++) {
        Vector2 pos = { basePos_.x + kDigitWidth * i, basePos_.y };
        digits_[i] = Sprite::Create(textureHandle, pos);
        digits_[i]->SetSize({ kDigitWidth, kDigitHeight });
    }
}

void NumberDrawer::Draw(int number) {
    int divisor = 10000;

    for (int i = 0; i < kDigitNum; i++) {
        int digit = number / divisor;

        digits_[i]->SetTextureRect({ kDigitWidth * digit, 0.0f }, { kDigitWidth, kDigitHeight });

        number %= divisor;
        divisor /= 10;
        digits_[i]->Draw();
    }
}