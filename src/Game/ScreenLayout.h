#pragma once

#include "raylib.h"

#include <unordered_map>
#include <optional>

class ScreenLayout
{
public:
	static constexpr int ROWS = 13;
	static constexpr int COLUMNS = 14;
	static constexpr int CELL_SIZE = 48;

	ScreenLayout(int startX = 0, int startY = 0);

	void Init();
	void Unload();

	void DrawBackground() const;
	void DrawDebug() const;

	Vector2 GetCellCenter(int row, int column) const;
	bool IsValidCell(int row, int column) const;

	void SetDebugEnabled(bool enabled);
	bool IsDebugEnabled() const;

	float GetLeft() const;
	float GetRight() const;

	bool IsHomeColumn(int column) const;
	std::optional<bool> GetHomeStatus(int column, int row) const;
	bool FillHome(int row, int column);
	bool AreAllHomesFilled() const;
	void UnfillHomes();

private:
	const int startX_;
	const int startY_;

	// Column => IsFilled
	std::unordered_map<int, bool> homeColumnAndFilledStatus_ {
		{0,  false},
		{2,  false},
		{4,  false},
		{6, false},
		{8, false},
		{10, false},
		{12, false},
	};

	bool debugEnabled_ = false;

	Texture2D bushTexture_;
	Texture2D floorTexture_;
	Texture2D homeTexture_;
	Texture2D pointTexture_;

	void DrawHomeTexture(int column, int x, int y) const;
};