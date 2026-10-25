#pragma once

#include "raylib.h"

#include "StateMachineMngr.h"

#include "Game/Player.h"
#include "Game/ScreenLayout.h"
#include "Game/Enemies/RoadSection.h"
#include "Game/Enemies/TurtleSection.h"
#include "Game/WoodLogSection.h"

class ScreenGameplayState : public StateMachineMngr
{
public:

	void enter(Screen* screen) {}
	void toggle(Screen* screen) {};
	void exit(Screen* screen) {};

	virtual void InitScreen(void);
	virtual void UpdateScreen(float deltaTime);
	virtual void DrawScreen(void);
	virtual void UnloadScreen(void);
	virtual int FinishScreen(void);

	int getScreenId() { return (int)ScreenState::GAMEPLAY; }

	static ScreenGameplayState& getInstance();

private:
	ScreenGameplayState();
	ScreenGameplayState(const ScreenGameplayState& other);
	ScreenGameplayState& operator= (const ScreenGameplayState& other);

	void EvaluateInput();
	
	void DebugOptions();
	void DrawDebug();

	Texture2D lifeTexture_{};

	Player player_;
	ScreenLayout screenLayout_;
	RoadSection roadSection_;
	TurtleSection turtleSection_;
	WoodLogSection woodLogSection_;

	Sound frogSquashSound_{};
	Sound frogPlunkSound_{};
	Sound frogHopSound_{};

	int finishScreen_ = 0;
	bool mb_ReplayLevel_ = false;

	void KillPlayer();
	void DrawLifeTimer() const;
	void DrawLives() const;
	void OnFrogReachingHouse();
};