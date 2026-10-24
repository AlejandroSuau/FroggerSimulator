#include "ScreenTitle.h"
#include "Game/Managers/GameManager.h"

ScreenTitleState& ScreenTitleState::getInstance()
{
	static ScreenTitleState singleton;
	return singleton;
}


void ScreenTitleState::InitScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;
	TraceLog(LOG_INFO, "ScreenTitleState::InitScreen");
	
	logo_ = LoadTexture("resources/Menu/MainLogo.png");
	GameManager& GameInst = GameManager::GetGameManager();
	PlayMusicStream(GameInst.GetMainThemeMusic());
}

void ScreenTitleState::UpdateScreen(float deltaTime)
{
	GameManager& GameInst = GameManager::GetGameManager();
	UpdateMusicStream(GameInst.GetMainThemeMusic());

	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
	{
		finishScreen = 2;   // GAMEPLAY
	}

	if (IsKeyPressed(KEY_O))
	{
		finishScreen = 1;   // OPTIONS
	}
}

void ScreenTitleState::DrawScreen(void)
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

	GameManager& GameInst = GameManager::GetGameManager();

	const auto logoWidth = static_cast<float>(logo_.width);
	const auto logoHeight = static_cast<float>(logo_.height);
	Rectangle srcRect{ 0.f, 0.f, logoWidth, logoHeight };
	Rectangle dstRect{ GetScreenWidth() / 2 - logoWidth / 2.f, 100.f, logoWidth, logoHeight};

	DrawTexturePro(logo_, srcRect, dstRect, { 0.f, 0.f }, 0.f, WHITE);

	const char* by_credits = "By Alejandro Suau R.";
	float posx = ((GetScreenWidth() / 2.f) - (MeasureText(by_credits, 20) / 2.f));

	DrawTextEx(GameInst.GetFont(), by_credits, Vector2{ posx, 450.f }, 20, 4, WHITE);

	static const char* text_1 = "Press Enter for Playing";
	static const char* text_2 = "Press 'O' for Instructions";
	DrawText(text_1, (GetScreenWidth() / 2) - (MeasureText(text_1, 25) / 2), 500, 25, WHITE);
	DrawText(text_2, (GetScreenWidth() / 2) - (MeasureText(text_2, 25) / 2), 560, 25, WHITE);


}

void ScreenTitleState::UnloadScreen(void)
{
	GameManager& GameInst = GameManager::GetGameManager();

}

int ScreenTitleState::FinishScreen(void)
{
	return finishScreen;
}