#pragma once

#include "raylib.h"

class ScreenLayout
{
public:
	static constexpr int ROWS = 13;
	static constexpr int COLUMNS = 14;
	static constexpr int CELL_SIZE = 48;

	ScreenLayout(int startX = 0, int startY = 0);

	void Draw() const;

	Vector2 GetCellCenter(int row, int column) const;
	bool IsValidCell(int row, int column) const;

	void SetDebugEnabled(bool enabled);
	bool IsDebugEnabled() const;

private:
	const int startX_;
	const int startY_;

	bool debugEnabled_ = true;
};