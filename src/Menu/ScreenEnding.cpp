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

	Font font = GameInst.GetFont();

	if (GameInst.GetEndResult() == EndResult::Win) {
		DrawText("YOU WIN!", (GetScreenWidth() / 2.f) - (MeasureText("YOU WIN!", 25) / 2), (GetScreenHeight() / 2.f), 25, GREEN);
	} else {
		DrawText("GAME OVER", (GetScreenWidth() / 2.f) - (MeasureText("GAME OVER", 25) / 2), (GetScreenHeight() / 2.f), 25, RED);
	}

	DrawText("Press Enter for Playing", (GetScreenWidth() / 2.f) - (MeasureText("Press Enter for Playing", 25) / 2), (GetScreenHeight() / 2.f) + 50, 25, WHITE);
	DrawText("Press 'O' for Options", (GetScreenWidth() / 2.f) - (MeasureText("Press '0' for Options", 25) / 2), (GetScreenHeight() / 2.f) + 100, 25, WHITE);

}

void ScreenEndingState::UnloadScreen(void)
{
}

int  ScreenEndingState::FinishScreen(void)
{
	return finishScreen;
}