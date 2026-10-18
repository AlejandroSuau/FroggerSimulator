#include "RoadSection.h"

#include "Game/Player.h"
#include "Game/ScreenLayout.h"

#include <string>

void RoadSection::Init(const ScreenLayout& layout)
{
    truckTextures_[0] = LoadTexture("resources/Game/Enemies/Truck1.png");
    truckTextures_[1] = LoadTexture("resources/Game/Enemies/Truck2.png");
    truckTextures_[2] = LoadTexture("resources/Game/Enemies/Truck3.png");
    truckTextures_[3] = LoadTexture("resources/Game/Enemies/Truck4.png");
    truckTextures_[4] = LoadTexture("resources/Game/Enemies/Truck5.png");

    static const std::array<float, LANE_COUNT> speeds { -80.0f, -120.0f, -100.0f, -150.0f, -70.0f};
    static const std::array<int, LANE_COUNT> rows { 11, 10, 9, 8, 7};

    for (int i = 0; i < LANE_COUNT; ++i)
    {
        const std::string assetPath = "resources/Game/Enemies/Truck" + std::to_string(i + 1) + ".png";
        truckTextures_[i] = LoadTexture(assetPath.c_str());
        for (int j = 0; j < TRUCKS_PER_LANE; ++j) {
            lanes_[i].speed = speeds[i];

            const Vector2 center = layout.GetCellCenter(rows[i], 0);
            const auto& texture = truckTextures_[i];
            const Vector2 position {
                layout.GetRight() - texture.width - j * (texture.width + TRUCK_GAP),
                center.y - texture.height / 2 };
            
            auto& truck = lanes_[i].trucks[j];
            truck.Init(truckTextures_[i], position, lanes_[i].speed);
        }
    }
}

void RoadSection::Unload()
{
    for (auto& texture : truckTextures_) {
        UnloadTexture(texture);
    }
}

bool RoadSection::CheckCollision(const Player& player, const ScreenLayout& layout) const
{
    const auto playerBounds = player.GetBounds(layout);
    for (auto& lane : lanes_) {
        for (auto& truck : lane.trucks) {
            if (CheckCollisionRecs(playerBounds, truck.GetBounds()))
            {
                return true;
            }
        }
    }

    return false;
}

void RoadSection::Update(float deltaTime, const ScreenLayout& layout)
{
    for (auto& lane : lanes_) {
        for (auto& truck : lane.trucks) {
            truck.Update(deltaTime);

            const auto bounds = truck.GetBounds();
            if (bounds.x <= layout.GetLeft()) {
                auto position = truck.GetPosition();
                position.x = layout.GetRight() + TRUCK_GAP;
                truck.SetPosition(position);
            }
        }
    }
}

void RoadSection::Draw() const
{
    for (const auto& lane : lanes_) {
        for (const auto& truck : lane.trucks) {
            truck.Draw();
        }
    }
}
