#pragma once

#include "raylib.h"

#include "Environment.h"
#include "Enemy.h"

class GameManager;

class Turret
{
public:
	Turret(GameManager* gameManager, float x, float y);

	void Update(float deltaTime);
	void Draw();
	void FindEnemy();

	float mX;
	float mY;

private:
	float mRange = 200;
	float mAngle = 0;

	Texture2D mTexture;
	Environment mEnvironment{};
	Enemy* mEnemy = nullptr;

	GameManager* mGameManager;
};

