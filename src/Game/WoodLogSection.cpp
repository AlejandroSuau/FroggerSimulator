#include "WoodLogSection.h"

#include "Game/Player.h"
#include "Game/ScreenLayout.h"

#include <algorithm>

void WoodLogSection::Init(const ScreenLayout& layout)
{
    logTextures_[0] = LoadTexture("resources/Game/Enemies/Log1U.png");
    logTextures_[1] = LoadTexture("resources/Game/Enemies/Log2U.png");
    logTextures_[2] = LoadTexture("resources/Game/Enemies/Log4U.png");

    static constexpr std::array<int, LANE_COUNT> rows { 0, 2, 3};
    static constexpr std::array<float, LANE_COUNT> speeds { 70.0f, 100.0f, 130.0f };
    static constexpr std::array<int, LANE_COUNT> logCounts {2, 3, 2};

    for (int laneIndex = 0; laneIndex < LANE_COUNT; ++laneIndex)
    {
        LogLane& lane = lanes_[laneIndex];

        lane.row = rows[laneIndex];
        lane.speed = speeds[laneIndex];

        lane.logs.clear();
        lane.logs.reserve(logCounts[laneIndex]);

        const Texture2D& texture = logTextures_[laneIndex];
        const Vector2 center = layout.GetCellCenter(lane.row + 1, 0);

        for (int logIndex = 0; logIndex < logCounts[laneIndex]; ++logIndex)
        {
            const float x = layout.GetLeft() + logIndex * (texture.width + LOG_GAP);
            const float y = center.y - texture.height / 2.0f;

            WoodLog log;
            log.Init(texture, { x, y }, lane.speed);
            lane.logs.push_back(log);
        }
    }
}

void WoodLogSection::Unload()
{
    for (auto& texture : logTextures_) {
        UnloadTexture(texture);
    }
}

void WoodLogSection::Update(float deltaTime, const ScreenLayout& layout)
{
    for (auto& lane : lanes_) {
        for (auto& log : lane.logs) {
            log.Update(deltaTime);

            const auto bounds = log.GetBounds();
            if (bounds.x >= layout.GetRight()) {
                auto position = log.GetPosition();
                position.x = layout.GetLeft() - LOG_GAP - log.GetBounds().width;
                log.SetPosition(position);
            }
        }
    }
}

float WoodLogSection::GetCarrySpeed(const Player& player, const ScreenLayout& layout) const
{
    const Rectangle playerBounds = player.GetBounds(layout);
    for (const LogLane& lane : lanes_) {
        for (const WoodLog& log : lane.logs) {
            if (CheckCollisionRecs(playerBounds, log.GetBounds())) {
                return log.GetSpeed();
            }
        }
    }

    return 0.0f;
}

void WoodLogSection::Draw() const
{
    for (const auto& lane : lanes_) {
        for (const auto& log : lane.logs) {
            log.Draw();
        }
    }
}