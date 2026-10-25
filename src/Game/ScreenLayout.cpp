#include "ScreenLayout.h"

#include <algorithm>
#include <assert.h>

ScreenLayout::ScreenLayout(int startX, int startY)
    : startX_(startX)
    , startY_(startY) {
}

void ScreenLayout::Init() {
    bushTexture_ = LoadTexture("resources/Game/Bush.png");
    floorTexture_ = LoadTexture("resources/Game/Floor.png");
    homeTexture_ = LoadTexture("resources/Game/Home.png");
    pointTexture_ = LoadTexture("resources/Game/Point.png");
}

void ScreenLayout::Unload() {
    UnloadTexture(bushTexture_);
    UnloadTexture(floorTexture_);
    UnloadTexture(homeTexture_);
    UnloadTexture(pointTexture_);
}

void ScreenLayout::DrawBackground() const {
    for (int row = 0; row < ROWS; ++row) {
        for (int column = 0; column < COLUMNS; ++column) {
            const int x = startX_ + column * CELL_SIZE;
            const int y = startY_ + row * CELL_SIZE;
            
            if (row == 0) {
                DrawHomeTexture(column, x, y);
            }
            else if (row == ROWS / 2 || row == ROWS - 1) {
                DrawTexture(floorTexture_, x, y, WHITE);
            }
        }
    }
}

void ScreenLayout::DrawHomeTexture(int column, int x, int y) const {
    auto itHomeColumn = homeColumnAndFilledStatus_.find(column);
    if (itHomeColumn != homeColumnAndFilledStatus_.end()) {
        if (bool isHomeFilled = itHomeColumn->second) {
            DrawTexture(pointTexture_, x, y, WHITE);
        } else {
            DrawTexture(homeTexture_, x, y, WHITE);
        }
    } else {
        DrawTexture(bushTexture_, x, y, WHITE);
    }
}

void ScreenLayout::DrawDebug() const
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

bool ScreenLayout::FillHome(int row, int column)
{
    if (row != 0) { return false; }

    auto it = homeColumnAndFilledStatus_.find(column);
    if (it == homeColumnAndFilledStatus_.cend() || it->second) {
        return false;
    }

    homeColumnAndFilledStatus_[column] = true;
    return true;
}

std::optional<bool> ScreenLayout::GetHomeStatus(int column, int row) const
{
    if (row != 0) { return std::nullopt; }

    const auto it = homeColumnAndFilledStatus_.find(column);
    if (it != homeColumnAndFilledStatus_.cend()) {
        return it->second;
    }

    return std::nullopt;
}

bool ScreenLayout::AreAllHomesFilled() const
{
    return std::all_of(
        homeColumnAndFilledStatus_.cbegin(),
        homeColumnAndFilledStatus_.cend(), 
        [](const auto& entry) { return entry.second; });
}

void ScreenLayout::UnfillHomes()
{
    for (auto it = homeColumnAndFilledStatus_.begin(); it != homeColumnAndFilledStatus_.end(); ++it) {
        it->second = false;
    }
}

Vector2 ScreenLayout::GetCellCenter(int row, int column) const
{
    return {
        static_cast<float>(startX_ + column * CELL_SIZE + CELL_SIZE / 2),
        static_cast<float>(startY_ + row * CELL_SIZE + CELL_SIZE / 2)
    };
}

bool ScreenLayout::IsHomeColumn(int column) const {
    return (
        homeColumnAndFilledStatus_.find(column) != homeColumnAndFilledStatus_.end());
}

bool ScreenLayout::IsValidCell(int row, int column) const
{
    if (auto homeStatus = GetHomeStatus(column, row)) {
        return !(*homeStatus);
    }

    return (row > 0 && row < ROWS && column >= 0 && column < COLUMNS);
}

void ScreenLayout::SetDebugEnabled(bool enabled)
{
    debugEnabled_ = enabled;
}

bool ScreenLayout::IsDebugEnabled() const
{
    return debugEnabled_;
}

float ScreenLayout::GetLeft() const
{
    return static_cast<float>(startX_);
}

float ScreenLayout::GetRight() const
{
    return static_cast<float>(startX_ + COLUMNS * CELL_SIZE);
}