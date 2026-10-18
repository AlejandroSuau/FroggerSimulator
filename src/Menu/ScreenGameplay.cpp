
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
	screenLayout_.Init();
	roadSection_.Init(screenLayout_);
}

void ScreenGameplayState::UpdateScreen(float deltaTime)
{
	EvaluateInput();
	// DebugOptions();

	//put here all the code for updating in the screen the gameplay
	player_.Update(deltaTime);	
	roadSection_.Update(deltaTime, screenLayout_);
	if (roadSection_.CheckCollision(player_, screenLayout_)) {
		player_.ResetPosition();
	}
}

void ScreenGameplayState::DrawScreen(void)
{

	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

	GameManager& GameInst = GameManager::GetGameManager();

	//put here all the code for drawing in the screen the gameplay	
	screenLayout_.DrawBackground();

	roadSection_.Draw();

	player_.Draw(screenLayout_);

	screenLayout_.DrawDebug();

	// UI Score, lives

	Font font = GameInst.GetFont();

	DrawText("SCORE:", 300.f, 100.f, 25, WHITE);
	DrawText(to_string(GameInst.GetScore()).c_str(), 440.f, 100.f, 25, WHITE);


}

void ScreenGameplayState::UnloadScreen(void)
{
	roadSection_.Unload();
	player_.Unload();
	screenLayout_.Unload();
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