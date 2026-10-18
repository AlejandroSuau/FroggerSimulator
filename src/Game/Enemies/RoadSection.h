#pragma once

#include "raylib.h"
#include "Truck.h"

#include <array>

class Player;
class ScreenLayout;

class RoadSection
{
public:
    struct RoadLane
    {
        float speed;
        std::array<Truck, 3> trucks;
    };

    static constexpr int LANE_COUNT = 5;

    void Init(const ScreenLayout& layout);
    void Update(float deltaTime, const ScreenLayout& layout);
    void Draw() const;
    void Unload();

    bool CheckCollision(const Player& player, const ScreenLayout& layout) const;

private:
    static constexpr float TRUCK_GAP = 180.f;
    static constexpr int TRUCKS_PER_LANE = 3;

    std::array<Texture2D, LANE_COUNT> truckTextures_;
    std::array<RoadLane, LANE_COUNT> lanes_;
};