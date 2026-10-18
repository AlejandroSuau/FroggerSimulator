#pragma once

#include "raylib.h"
#include "Truck.h"

#include <array>

class Player;
class ScreenLayout;

class RoadSection
{
public:
    static constexpr int TRUCKS_PER_LANE = 3;
    struct RoadLane
    {
        float speed;
        std::array<Truck, TRUCKS_PER_LANE> trucks;
    };

    static constexpr int LANE_COUNT = 5;

    void Init(const ScreenLayout& layout);
    void Update(float deltaTime, const ScreenLayout& layout);
    void Draw() const;
    void Unload();

    bool CheckCollision(const Player& player, const ScreenLayout& layout) const;

private:
    static constexpr float TRUCK_GAP = 180.f;

    std::array<Texture2D, LANE_COUNT> truckTextures_;
    std::array<RoadLane, LANE_COUNT> lanes_;
};