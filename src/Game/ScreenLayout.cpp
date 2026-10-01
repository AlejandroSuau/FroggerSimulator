#include "ScreenLayout.h"

ScreenLayout::ScreenLayout(int startX, int startY)
    : startX_(startX)
    , startY_(startY) {}

void ScreenLayout::Draw() const
{
    if (!debugEnabled_) { return; }

    for (int row = 0; row < ROWS; ++row) {
        for (int column = 0; column < COLUMNS; ++column) {
            const int x = startX_ + column * CELL_SIZE;
            const int y = startY_ + row * CELL_SIZE;

            // Debug cell
            DrawRectangleLines(x, y, CELL_SIZE, CELL_SIZE, RED);

            const Vector2 center = GetCellCenter(row, column);

            // Yellow center point
            DrawCircleV(center, 2.0f, YELLOW);
        }
    }
}

Vector2 ScreenLayout::GetCellCenter(int row, int column) const
{
    return {
        static_cast<float>(startX_ + column * CELL_SIZE + CELL_SIZE / 2),
        static_cast<float>(startY_ + row * CELL_SIZE + CELL_SIZE / 2)
    };
}

bool ScreenLayout::IsValidCell(int row, int column) const
{
    return (row >= 0 && row < ROWS && column >= 0 && column < COLUMNS);
}

void ScreenLayout::SetDebugEnabled(bool enabled)
{
    debugEnabled_ = enabled;
}

bool ScreenLayout::IsDebugEnabled() const
{
    return debugEnabled_;
}