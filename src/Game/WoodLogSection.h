#pragma once

#include "raylib.h"
#include "WoodLog.h"

#include <array>
#include <vector>

class Player;
class ScreenLayout;

class WoodLogSection
{
public:
    static constexpr int LANE_COUNT = 3;

    struct LogLane
    {
        int row = 0;
        float speed = 0.0f;
        std::vector<WoodLog> logs;
    };

    void Init(const ScreenLayout& layout);
    void Update(float deltaTime, const ScreenLayout& layout);
    void Draw() const;
    void Unload();

    float GetCarrySpeed(
        const Player& player,
        const ScreenLayout& layout) const;

private:
    static constexpr float LOG_GAP = 180.0f;

    std::array<Texture2D, LANE_COUNT> logTextures_{};
    std::array<LogLane, LANE_COUNT> lanes_{};
};