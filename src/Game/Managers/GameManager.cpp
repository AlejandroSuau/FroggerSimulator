#include "GameManager.h"

#include "raylib.h"

#include "Menu/StateMachineMngr.h"
#include "Menu/ScreenLogo.h"
#include "Menu/ScreenTitle.h"
#include "Menu/ScreenGameplay.h"
#include "Menu/ScreenOptions.h"
#include "Menu/ScreenEnding.h"

#include <stdio.h>              // Standard input-output C library
#include <stdlib.h>             // Memory management functions: malloc(), free()
#include <string.h>             // String manipulation functions: strrchr(), strcmp()

//---------------------------------------------------------------
GameManager* GameManager::GameMngr = nullptr;


GameManager& GameManager::GetGameManager()
{
    // Previous usage had a memory leak
    static GameManager singleton;
    return singleton;
}

GameManager::GameManager()
{
}


void GameManager::InitGame()
{

    // Load global data (assets that must be available in all screens, i.e. font)
    font = LoadFont("resources/Font/PacManFont.ttf");

    mainThemeMusic_ = LoadMusicStream("resources/Sounds/Lily_Islands.mp3");
    gameOverMusic_ = LoadMusicStream("resources/Sounds/Game_Over.mp3");

    // Setup and init first screen
    ScreenState = &ScreenLogoState::getInstance();
    ScreenState->InitScreen();
     
}
//-------------------------------------------------------
void GameManager::UpdateFrame(float deltaTime)
{
 // Update
 //----------------------------------------------------------------------------------
    UpdateMusicStream(mainThemeMusic_);

    if (!onTransition)
    {
        ScreenState->UpdateScreen(deltaTime);
        
        switch (ScreenState->getScreenId())
        {
            case (int) ScreenState::LOGO:
                {
                if (int InputKey = ScreenState->FinishScreen())
                {
                    TransitionToScreen((int)ScreenState::TITLE);
                    ScreenState = &ScreenTitleState::getInstance();
                }
                } break;
            case (int) ScreenState::TITLE:
                {
                if (int InputKey = ScreenState->FinishScreen())
                {
                    if (InputKey == 1)
                    {
                        TransitionToScreen((int)ScreenState::OPTIONS);
                        ScreenState = &ScreenOptionsState::getInstance();
                    }
                    else if (InputKey == 2)
                    {
                        TransitionToScreen((int)ScreenState::GAMEPLAY);
                        ScreenState = &ScreenGameplayState::getInstance();
                    }
                }

                } break;
            case (int) ScreenState::OPTIONS:
                {
                if (int InputKey = ScreenState->FinishScreen())
                {
                    if (InputKey == 1)
                    {
                        TransitionToScreen((int)ScreenState::TITLE);
                        ScreenState = &ScreenTitleState::getInstance();
                    }
                }
                } break;
            case (int)ScreenState::GAMEPLAY:
            {
                if (int InputKey = ScreenState->FinishScreen())
                {
                    if (InputKey == 4)
                    {
                        TransitionToScreen((int)ScreenState::ENDING);
                        ScreenState = &ScreenEndingState::getInstance();
                    }
                }

            } break;
            case (int)ScreenState::ENDING:
            {    
                if (int InputKey = ScreenState->FinishScreen())
                {
                    if (InputKey == 2)
                    {
                        TransitionToScreen((int)ScreenState::OPTIONS);
                        ScreenState = &ScreenOptionsState::getInstance();
                    }
                    else if (InputKey == 1)
                    {
                        //update here the game for perform the restart

                        TransitionToScreen((int)ScreenState::TITLE);
                        ScreenState = &ScreenTitleState::getInstance();
                    }
                }
            } break;
            default: break;
        }
     }
    else UpdateTransition();    // Update transition (fade-in, fade-out)
    //----------------------------------------------------------------------------------

}

//-------------------------------------------------------

void GameManager::DrawFrame(void)
{

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw full screen rectangle in front of everything
    if (onTransition)
    {
        DrawTransition();
    }
    else
    {
        ScreenState->DrawScreen();
    }
    EndDrawing();
}

//-------------------------------------------------------

void GameManager::UnloadGame(void)
{
    ScreenState->UnloadScreen();

    ClearGameVar();

    // Unload global data loaded
    UnloadFont(font);
    UnloadMusicStream(mainThemeMusic_);
    UnloadMusicStream(gameOverMusic_);

    CloseAudioDevice();     // Close audio context
}


//----------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------
// Change to next screen, no transition
void GameManager::ChangeToScreen(int screen)
{
    // Unload current screen
    ScreenState->UnloadScreen();
    
    // Init next screen
    ScreenState->InitScreen();

}

// Request transition to next screen
void GameManager::TransitionToScreen(int screen)
{
    onTransition = true;
    transFadeOut = false;
    transToScreen = screen;
    transAlpha = 0.0f;
}

// Update transition effect (fade-in, fade-out)
void GameManager::UpdateTransition(void)
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;
            // Unload current screen
            ScreenState->UnloadScreen();

            // Init next screen
            ScreenState->InitScreen();

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = -1;
        }
    }
}

// Draw transition effect (full-screen rectangle)
void GameManager::DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

void GameManager::ClearGameVar()
{
    score = 0;
    seconds = 0;
}

void GameManager::LoseLife()
{
    if (lives_ > 0) {
        --lives_;
    }

    ResetRemainingLifeTime();
}

void GameManager::StartNewGame() 
{
    ResetLives();
    ResetRemainingLifeTime();
}

int GameManager::GetLives() const
{
    return lives_;
}

float GameManager::GetRemainingLifeTime() const
{
    return remainingLifeTimeInSeconds_;
}

void GameManager::UpdateLifeTime(float deltaTime)
{
    if (remainingLifeTimeInSeconds_ <= 0.f) { return; }
    
    remainingLifeTimeInSeconds_ -= deltaTime;
    if (remainingLifeTimeInSeconds_ < 0) {
        remainingLifeTimeInSeconds_ = 0.f;
    }
}

bool GameManager::IsGameOver() const 
{
    return lives_ <= 0;
}

void GameManager::ResetLives()
{
    lives_ = GameGlobalVar::kInitialLives;
}

void GameManager::ResetRemainingLifeTime()
{
    remainingLifeTimeInSeconds_ = GameGlobalVar::kLifeTimeInSeconds;
}

void GameManager::SetEndResult(EndResult endResult) {
    endResult_ = endResult;
}

float GameManager::GetLifeTime() const {
    return GameGlobalVar::kLifeTimeInSeconds;
}

Music& GameManager::GetMainThemeMusic()
{
    return mainThemeMusic_;
}

Music& GameManager::GetGameOverMusic()
{
    return gameOverMusic_;
}

EndResult GameManager::GetEndResult() const
{
    return endResult_;
}