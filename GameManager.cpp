#include "GameManager.h"

#include <iostream>

void GameManager::Init()
{
	//initialize car and environment + countdown
    car.Init();
    environment.Init();

	mCountdown = mMaxCountdown;
}

bool GameManager::Update(float deltaTime)
{
	//update timer
	mTimer += GetFrameTime();

	car.Update(deltaTime);

	//if car end game -> end game
	if (car.Update(deltaTime))
	{
		Init();
		return true;
	}

	return false;
}

void GameManager::Draw()
{
	//Draw Car, Environment (tiles) and show timer
	environment.Draw();
	car.Draw();

	DrawText(TextFormat("Time : %.2fs", mTimer), GetScreenWidth() - (MeasureText(TextFormat("Time : %.2fs", mTimer), 50)) - 10, 10, 50, WHITE);
}

bool GameManager::StartRace()
{
	//Countdown
	static float timeElapsed = 0.0f;
	timeElapsed += GetFrameTime();
	if (timeElapsed >= mTimeOfCountdown)
	{
		timeElapsed -= mTimeOfCountdown;
		mCountdown--;
	}

	return (mCountdown == 0);
}

void GameManager::DrawStartRace()
{
	//Draw Countdown

	const char* text = TextFormat("%i", mCountdown);
	float posX = GetScreenWidth() / 2 - (MeasureText(TextFormat("%i", mCountdown), 380) / 2);
	float posY = 180;
	float fontSize = 380;
	float outlineSize = 5;

	Color color = WHITE;
	Color outlineColor = BLACK;

	DrawText(text, posX - outlineSize, posY - outlineSize, fontSize, outlineColor);
	DrawText(text, posX + outlineSize, posY - outlineSize, fontSize, outlineColor);
	DrawText(text, posX - outlineSize, posY + outlineSize, fontSize, outlineColor);
	DrawText(text, posX + outlineSize, posY + outlineSize, fontSize, outlineColor);
	DrawText(text, posX, posY, fontSize, color);
}

float GameManager::GetTimer()
{
	return mTimer;
}

void GameManager::ResetTimer()
{
	mTimer = 0;
}
