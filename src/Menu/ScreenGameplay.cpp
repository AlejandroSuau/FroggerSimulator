
#pragma once

#include "ScreenGameplay.h"
#include "raylib.h"
#include "Game/Managers/GameManager.h"
#include "Game/GlobalGameDefines.h"

#include <string>


ScreenGameplayState::ScreenGameplayState()
	: screenLayout_(325, 150) {}

ScreenGameplayState& ScreenGameplayState::getInstance()
{
	static ScreenGameplayState singleton;
	return singleton;
}

void ScreenGameplayState::InitScreen(void)
{
	framesCounter_ = 0;
	finishScreen_ = 0;

	player_.Init();
}

void ScreenGameplayState::UpdateScreen(float deltaTime)
{
	EvaluateInput();

	//put here all the code for updating in the screen the gameplay
	player_.Update(deltaTime);	
}

void ScreenGameplayState::DrawScreen(void)
{

	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

	GameManager& GameInst = GameManager::GetGameManager();

	//put here all the code for drawing in the screen the gameplay
	screenLayout_.Draw();
	player_.Draw(screenLayout_);
	
	// UI Score, lives

	Font font = GameInst.GetFont();

	DrawText("SCORE:", 300.f, 100.f, 25, WHITE);
	DrawText(to_string(GameInst.GetScore()).c_str(), 440.f, 100.f, 25, WHITE);


}

void ScreenGameplayState::UnloadScreen(void)
{
	player_.Unload();
}

int  ScreenGameplayState::FinishScreen(void)
{
	return finishScreen_;
}

void ScreenGameplayState::EvaluateInput()
{
	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
	{
		finishScreen_ = 4;   // END SCREEN
	}
}

void ScreenGameplayState::DebugOptions()
{

}

void ScreenGameplayState::DrawDebug()
{
	GameManager& GameInst = GameManager::GetGameManager();

}