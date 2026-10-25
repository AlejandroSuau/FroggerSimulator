#pragma once

#include "raylib.h"
#include "ScreenLayout.h"

#include <array>
#include <utility>

class Player
{
public:
    enum class Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    void Init();
    void Unload();
    void ResetPosition();
    void AddHorizontalOffset(float amount, const ScreenLayout& layout);

    bool Update(const ScreenLayout& layout);
    void Draw(const ScreenLayout& layout) const;
    Rectangle GetBounds(const ScreenLayout& layout) const;
    std::pair<int, int> GetColumnRow() const;

private:
    static constexpr int startingRow_ = ScreenLayout::ROWS - 1;
    static constexpr int startingCol_ = ScreenLayout::COLUMNS / 2;

    int row_ = startingRow_;
    int column_ = startingCol_;
    Direction direction_ = Direction::Up;
    float horizontalOffset_ = 0.f;

    Texture2D textureUp_{};
    Texture2D textureDown_{};
    Texture2D textureLeft_{};
    Texture2D textureRight_{};

    void Move(int rowOffset, int columnOffset, const ScreenLayout& layout);
};