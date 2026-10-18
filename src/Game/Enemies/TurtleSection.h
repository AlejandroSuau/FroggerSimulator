#pragma once

#include "raylib.h"
#include "Turtle.h"

#include <array>

class Player;
class ScreenLayout;

class TurtleSection
{
public:
    static constexpr int LANE_COUNT = 2;

    static constexpr int TURTLES_PER_LANE = 3;
    struct TurtleLane
    {
        int row = 0;
        float speed = 0.0f;
        std::array<Turtle, TURTLES_PER_LANE> turtles;
    };

    void Init(const ScreenLayout& layout);
    void Update(float deltaTime, const ScreenLayout& layout);
    void Draw() const;
    void Unload();

    bool CheckCollision(
        const Player& player,
        const ScreenLayout& layout) const;

private:
    static constexpr float TURTLE_GAP = 120.0f;

    Texture2D turtleTexture_{};
    std::array<TurtleLane, LANE_COUNT> lanes_{};
};