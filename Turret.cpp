#include "Turret.h"

#include "raymath.h"
#include <iostream>
#include <cmath>

#include "GameManager.h"

Turret::Turret(GameManager* gameManager, float x, float y)
	: mGameManager(gameManager)
{
	mX = floorf(x / mEnvironment.mTileSize) * mEnvironment.mTileSize;
	mY = floorf(y / mEnvironment.mTileSize) * mEnvironment.mTileSize;

	mTexture = LoadTexture("resources/towerDefense_tile249.png");
}

void Turret::Update(float deltaTime)
{
	if (mEnemy == nullptr || Vector2Distance({ mEnemy->mX, mEnemy->mY }, { mX + mEnvironment.mTileSize / 2, mY + mEnvironment.mTileSize / 2 }) > mRange)
	{
		FindEnemy();
	}

	if (mEnemy != nullptr)
	{
		mAngle = atan2(mEnemy->mY - (mY + mEnvironment.mTileSize / 2), mEnemy->mX - (mX + mEnvironment.mTileSize / 2));
	}
}

void Turret::Draw()
{
	Rectangle source{ 0, 0, mTexture.width, mTexture.height };
	Rectangle dest{ mX + mEnvironment.mTileSize / 2, mY + mEnvironment.mTileSize / 2, mTexture.width / 2.0f, mTexture.height / 2.0f };

	Vector2 origin{ dest.width / 2, dest.height / 2 };

	DrawTexturePro(mTexture, source, dest, origin, mAngle * RAD2DEG, WHITE);

	//debug
	DrawCircleLines(mX + mEnvironment.mTileSize / 2, mY + mEnvironment.mTileSize / 2, mRange, RED);
}

void Turret::FindEnemy()
{
	std::vector<Enemy>& allEnemies = mGameManager->GetAllEnemies();

	mEnemy = nullptr;

	for (Enemy enemy : allEnemies)
	{
		if (Vector2Distance({ enemy.mX, enemy.mY }, { mX + mEnvironment.mTileSize / 2, mY + mEnvironment.mTileSize / 2 }) < mRange)
		{
			mEnemy = &enemy;
			return;
		}
	}
}
