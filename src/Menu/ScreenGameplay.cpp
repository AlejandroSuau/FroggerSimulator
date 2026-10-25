
#pragma once

#include "ScreenGameplay.h"
#include "Game/GlobalGameDefines.h"

#include <string>

#include "raylib.h"

ScreenGameplayState::ScreenGameplayState()
	: screenLayout_(24, 88) {}

ScreenGameplayState& ScreenGameplayState::getInstance()
{
	static ScreenGameplayState singleton;
	return singleton;
}

void ScreenGameplayState::InitScreen(void)
{
	screenLayout_.UnfillHomes();
	finishScreen_ = 0;

	GameManager& game = GameManager::GetGameManager();
	game.StartNewGame();

	auto& mainThemeMusic = game.GetMainThemeMusic();
	if (!IsMusicStreamPlaying(mainThemeMusic)) {
		PlayMusicStream(mainThemeMusic);
		StopMusicStream(game.GetGameOverMusic());
	}

	lifeTexture_ = LoadTexture("resources/Game/Life.png");
	
	frogSquashSound_ = LoadSound("resources/Sounds/frogger_squash.wav");
	frogPlunkSound_ = LoadSound("resources/Sounds/frogger_plunk.wav");
	frogHopSound_ = LoadSound("resources/Sounds/frogger_hop.wav");

	player_.Init();
	screenLayout_.Init();
	roadSection_.Init(screenLayout_);
	turtleSection_.Init(screenLayout_);
	woodLogSection_.Init(screenLayout_);
}

void ScreenGameplayState::UpdateScreen(float deltaTime)
{
	GameManager& game = GameManager::GetGameManager();
	UpdateMusicStream(game.GetMainThemeMusic());

	EvaluateInput();
	// DebugOptions();

	if (player_.Update(screenLayout_)) {
		PlaySound(frogHopSound_);
	}

	roadSection_.Update(deltaTime, screenLayout_);
	turtleSection_.Update(deltaTime, screenLayout_);
	woodLogSection_.Update(deltaTime, screenLayout_);

	const float carrySpeed = woodLogSection_.GetCarrySpeed(player_, screenLayout_);
	if (carrySpeed != 0.f) {
		player_.AddHorizontalOffset(carrySpeed * deltaTime, screenLayout_);
	}

	game.UpdateLifeTime(deltaTime);

	// Check frog carrying
	const auto [col, row] = player_.GetColumnRow();
	if (screenLayout_.FillHome(row, col)) {
		OnFrogReachingHouse();

		if (screenLayout_.AreAllHomesFilled()) {
			OnEndGame(EndResult::Win);
		} else {
			player_.ResetPosition();
		}
	}

	if (roadSection_.CheckCollision(player_, screenLayout_) ||
		turtleSection_.CheckCollision(player_, screenLayout_) || 
		game.GetRemainingLifeTime() <= 0.f) {
		KillPlayer();
	}
}

void ScreenGameplayState::OnEndGame(EndResult endResult)
{
	finishScreen_ = 4;
	
	GameManager& game = GameManager::GetGameManager();
	game.SetEndResult(endResult);
	game.UpdateHighScore();
}

void ScreenGameplayState::OnFrogReachingHouse()
{
	GameManager& game = GameManager::GetGameManager();
	game.IncreaseScore(GameGlobalVar::kOnReachHouseScore);
	PlaySound(frogPlunkSound_);
	player_.ResetPosition();
}

void ScreenGameplayState::KillPlayer()
{
	GameManager& game = GameManager::GetGameManager();
	
	game.LoseLife();
	player_.ResetPosition();
	PlaySound(frogSquashSound_);

	if (game.IsGameOver()) {
		OnEndGame(EndResult::GameOver);
	}
}

void ScreenGameplayState::DrawScreen(void)
{

	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

	GameManager& GameInst = GameManager::GetGameManager();

	//put here all the code for drawing in the screen the gameplay	
	screenLayout_.DrawBackground();

	roadSection_.Draw();
	turtleSection_.Draw();
	woodLogSection_.Draw();

	player_.Draw(screenLayout_);
	DrawLifeTimer();
	DrawLives();

	screenLayout_.DrawDebug();

	// UI Score, lives

	Font font = GameInst.GetFont();

	DrawText("SCORE:", 50.f, 40.f, 25, WHITE);
	DrawText(to_string(GameInst.GetScore()).c_str(), 190.f, 40.f, 25, WHITE);
}

void ScreenGameplayState::DrawLives() const
{
	const int lives = GameManager::GetGameManager().GetLives();
	const float startX = screenLayout_.GetRight();
	const float y = static_cast<float>(GetScreenHeight()) - 40;

	for (int i = 0; i < lives; ++i)
	{
		DrawTexture(
			lifeTexture_,
			static_cast<int>(startX - (i + 1) * 40),
			static_cast<int>(y),
			WHITE);
	}
}

void ScreenGameplayState::DrawLifeTimer() const
{
	GameManager& game = GameManager::GetGameManager();

	const float remaining = game.GetRemainingLifeTime();
	const float total = game.GetLifeTime();

	const float ratio = remaining / total;

	const float barX = 150.0f;
	const float barY = static_cast<float>(GetScreenHeight() - 40);

	const float barWidth = 300.0f;
	const float barHeight = 20.0f;

	DrawText(
		"TIMER:",
		50,
		static_cast<int>(barY),
		20,
		GREEN);

	DrawRectangle(
		static_cast<int>(barX),
		static_cast<int>(barY),
		static_cast<int>(barWidth),
		static_cast<int>(barHeight),
		DARKGRAY);

	DrawRectangle(
		static_cast<int>(barX),
		static_cast<int>(barY),
		static_cast<int>(barWidth * ratio),
		static_cast<int>(barHeight),
		GREEN);
}

void ScreenGameplayState::UnloadScreen(void)
{
	UnloadTexture(lifeTexture_);
	UnloadSound(frogSquashSound_);
	UnloadSound(frogPlunkSound_);
	UnloadSound(frogHopSound_);

	roadSection_.Unload();
	turtleSection_.Unload();
	woodLogSection_.Unload();
	player_.Unload();
	screenLayout_.Unload();
}

int  ScreenGameplayState::FinishScreen(void)
{
	return finishScreen_;
}

void ScreenGameplayState::EvaluateInput()
{
	if (IsKeyPressed(KEY_ENTER))
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