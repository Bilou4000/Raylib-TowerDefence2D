#pragma once

#include "raylib.h"

#include "Environment.h"
#include "Enemy.h"

#include <memory>

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
	const float mFireRate = 1;
	float mCurrentFireTime = 1/mFireRate;

	float mRange = 200;
	float mAngle = 0;

	Texture2D mTexture;
	Environment mEnvironment{};
	std::weak_ptr<Enemy> mEnemy;

	GameManager* mGameManager;
};

