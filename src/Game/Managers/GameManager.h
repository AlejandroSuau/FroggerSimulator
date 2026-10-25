#pragma once

#include "raylib.h"

#include "Game/GlobalGameDefines.h"
#include "Menu/StateMachineMngr.h" 

using namespace std;

enum class EndResult
{
	Win,
	GameOver
};

class GameManager
{
private:


public:
	GameManager();

	void InitGame();						// Initialize game
	void UpdateFrame(float deltaTime);      // Update game (one frame)
	void DrawFrame(void);                    // Draw game (one frame)
	void UnloadGame(void);

	void ClearGameVar();

	void LoseLife();
	int GetLives() const;
	float GetLifeTime() const;
	float GetRemainingLifeTime() const;
	void UpdateLifeTime(float deltaTime);

	bool IsGameOver() const;

	void ResetLives();
	void ResetRemainingLifeTime();

	void StartNewGame();
	void SetEndResult(EndResult endResult);
	EndResult GetEndResult() const;

	Font& GetFont() { return font; }

	int GetScore() const { return score_; }
	void SetScore(int newValue) { score_ = newValue; }
	int GetHighScore() const { return highScore_; }
	void UpdateHighScore();

	void IncreaseScore(int newValue) { score_ += newValue; }
	void DecreaseScore(int newValue) { score_ -= newValue; }

	static GameManager& GetGameManager();

	Music& GetMainThemeMusic();
	Music& GetGameOverMusic();

private:
	//----------------------------------------------------
	//TODO to move to ScreensMngr?
	void ChangeToScreen(int screen);     // Change to screen, no transition effect

	void TransitionToScreen(int screen); // Request transition to next screen
	void UpdateTransition(void);         // Update transition effect
	void DrawTransition(void);           // Draw transition effect (full-screen rectangle)

	float transAlpha = 0.0f;
	bool onTransition = false;
	bool transFadeOut = false;
	int transFromScreen = -1;
	int transToScreen = -1;

	int score_ = 0;
	int highScore_ = 0;

	int lives_ = 0;
	float remainingLifeTimeInSeconds_ = 0.f;
	EndResult endResult_ = EndResult::GameOver;

	//------------

	Font font = { 0 };
	Music mainThemeMusic_{};
	Music gameOverMusic_{};

	StateMachineMngr* ScreenState;

};