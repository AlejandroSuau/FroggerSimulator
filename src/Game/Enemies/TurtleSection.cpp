#include "TurtleSection.h"

#include "Game/Player.h"
#include "Game/ScreenLayout.h"

#include <algorithm>

void TurtleSection::Init(const ScreenLayout& layout)
{
    turtleTexture_ = LoadTexture("resources/Game/Enemies/TurtleEnabled.png");

    static constexpr std::array<int, LANE_COUNT> rows {1, 4};
    static constexpr std::array<float, LANE_COUNT> speeds { -70.0f, -110.0f};

    for (int i = 0; i< LANE_COUNT; ++i) {
        auto& lane = lanes_[i];

        lane.row = rows[i];
        lane.speed = speeds[i];

        // Add one cause we skip first row (housing)
        const auto center = layout.GetCellCenter(lane.row + 1, 0);
        for (int j = 0; j < TURTLES_PER_LANE; ++j) {
            const float x = 
                layout.GetRight() - turtleTexture_.width - j * (turtleTexture_.width + TURTLE_GAP);
            const float y = center.y - turtleTexture_.height / 2.0f ;

            auto& turtle = lanes_[i].turtles[j];
            turtle.Init(turtleTexture_, { x, y }, lane.speed);
        }
    }
}

void TurtleSection::Update(float deltaTime, const ScreenLayout& layout)
{
    for (auto& lane : lanes_) {
        for (auto& turtle : lane.turtles) {
            turtle.Update(deltaTime);
            
            const auto bounds = turtle.GetBounds();
            if (bounds.x <= layout.GetLeft()) {
                auto position = turtle.GetPosition();
                position.x = layout.GetRight() + TURTLE_GAP;
                turtle.SetPosition(position);
            }
        }
    }
}

bool TurtleSection::CheckCollision(const Player& player, const ScreenLayout& layout) const
{
    const Rectangle playerBounds = player.GetBounds(layout);

    for (const auto& lane : lanes_) {
        for (const auto& turtle : lane.turtles) {
            if (CheckCollisionRecs(playerBounds, turtle.GetBounds())) {
                return true;
            }
        }
    }

    return false;
}

void TurtleSection::Draw() const
{
    for (const auto& lane : lanes_) {
        for (const auto& turtle : lane.turtles) {
            turtle.Draw();
        }
    }
}

void TurtleSection::Unload()
{
    UnloadTexture(turtleTexture_);
}