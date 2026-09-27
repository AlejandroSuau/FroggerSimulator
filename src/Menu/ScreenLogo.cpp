#include "ScreenLogo.h"

namespace
{
    constexpr float FADE_IN_TIME = 1.0f;
    constexpr float DISPLAY_TIME = 1.0f;
    constexpr float FADE_OUT_TIME = 1.0f;
}

ScreenLogoState::ScreenLogoState()
{}

ScreenLogoState& ScreenLogoState::getInstance()
{
    static ScreenLogoState singleton;
    return singleton;
}

//-------------------------------------------------------------
void ScreenLogoState::InitScreen(void)
{
    alpha_ = 1.0f;

    logo_ = LoadTexture("resources/Logo-TheTrueBooleanGames.png");
}

//-------------------------------------------------------------
void ScreenLogoState::UpdateScreen(float deltaTime)
{
    chargeTime_ += deltaTime;
    if (chargeTime_ < FADE_IN_TIME) {
        // Fade In
        alpha_ = chargeTime_ / FADE_IN_TIME;
    } else if (chargeTime_ < FADE_IN_TIME + DISPLAY_TIME) { 
        // Showing N seconds
        alpha_ = 1.f;
    } else if (chargeTime_ < FADE_IN_TIME + DISPLAY_TIME + FADE_OUT_TIME) {
        // Fade Out
        const float fadeOutProgress = (chargeTime_ - FADE_IN_TIME - DISPLAY_TIME) / FADE_OUT_TIME;
        alpha_ = 1.f - fadeOutProgress;
    } else {
        // End
        alpha_ = 0.f;
        finishScreen_ = 1;
    }
}

//-------------------------------------------------------------
void ScreenLogoState::DrawScreen(void)
{
    Rectangle srcRect {
        0.f, 0.f, static_cast<float>(logo_.width), static_cast<float>(logo_.height) };
    Rectangle dstRect {
        0.0f, 0.0f, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) };

    DrawTexturePro(logo_, srcRect, dstRect, {0.f, 0.f}, 0.f, Fade(WHITE, alpha_));
}

//-------------------------------------------------------------
void ScreenLogoState::UnloadScreen(void)
{

}

//-------------------------------------------------------------
int  ScreenLogoState::FinishScreen(void)
{
    return finishScreen_;
}