#pragma once

#include "raylib.h"
#include "ScreenLayout.h"

#include <array>

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

    void Update(const ScreenLayout& layout);
    void Draw(const ScreenLayout& layout) const;

private:
    int row_ = ScreenLayout::ROWS - 1;
    int column_ = ScreenLayout::COLUMNS / 2;
    Direction m_direction = Direction::Up;

    Texture2D textureUp_{};
    Texture2D textureDown_{};
    Texture2D textureLeft_{};
    Texture2D textureRight_{};

    void Move(int rowOffset, int columnOffset, const ScreenLayout& layout);
};