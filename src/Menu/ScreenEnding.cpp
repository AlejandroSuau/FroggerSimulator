#include "ScreenEnding.h"
#include "Game/Managers/GameManager.h"

#include "raylib.h"

#include <string>


ScreenEndingState& ScreenEndingState::getInstance()
{
	static ScreenEndingState singleton;
	return singleton;
}


void ScreenEndingState::InitScreen(void)
{
	finishScreen = 0;
	GameManager& GameInst = GameManager::GetGameManager();

	if (GameInst.GetEndResult() == EndResult::GameOver) {
		StopMusicStream(GameInst.GetMainThemeMusic());
		PlayMusicStream(GameInst.GetGameOverMusic());
	}
}

void ScreenEndingState::UpdateScreen(float deltaTime)
{
	GameManager& GameInst = GameManager::GetGameManager();
	UpdateMusicStream(GameInst.GetGameOverMusic());
	if (IsKeyPressed(KEY_ENTER) )
	{
		finishScreen = 1; // GAMEPLAY

	}
	if (IsKeyPressed(KEY_O))
	{
		finishScreen = 2;   // OPTIONS
	}
}

void ScreenEndingState::DrawScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    GameManager& GameInst = GameManager::GetGameManager();

    const int centerX = GetScreenWidth() / 2;
    const int centerY = GetScreenHeight() / 2;

    const int titleSize = 32;
    const int textSize = 24;

    const char* title = GameInst.GetEndResult() == EndResult::Win ? "YOU WIN!" : "GAME OVER";
    const Color titleColor = GameInst.GetEndResult() == EndResult::Win ? GREEN : RED;

    DrawText(
        title,
        centerX - MeasureText(title, titleSize) / 2,
        centerY - 120,
        titleSize,
        titleColor);

    const std::string gameScore = "GAME SCORE: " + std::to_string(GameInst.GetScore());

    DrawText(
        gameScore.c_str(),
        centerX - MeasureText(gameScore.c_str(), textSize) / 2,
        centerY - 50,
        textSize,
        WHITE);

    const std::string highScore = "HIGH SCORE: " + std::to_string(GameInst.GetHighScore());

    DrawText(
        highScore.c_str(),
        centerX - MeasureText(highScore.c_str(), textSize) / 2,
        centerY,
        textSize,
        YELLOW);

    const char* playText = "Press Enter for Playing";

    DrawText(
        playText,
        centerX - MeasureText(playText, textSize) / 2,
        centerY + 80,
        textSize,
        WHITE);

    const char* optionsText = "Press 'O' for Options";

    DrawText(
        optionsText,
        centerX - MeasureText(optionsText, textSize) / 2,
        centerY + 120,
        textSize,
        WHITE);
}

void ScreenEndingState::UnloadScreen(void)
{
}

int  ScreenEndingState::FinishScreen(void)
{
	return finishScreen;
}