#include "Turret.h"

#include "raymath.h"
#include <iostream>
#include <cmath>

#include "GameManager.h"

Turret::Turret(GameManager* gameManager, float x, float y)
	: mGameManager(gameManager)
{
	mX = x;
	mY = y;

	mTexture = LoadTexture("resources/towerDefense_tile249.png");
}

void Turret::Update(float deltaTime)
{
	std::shared_ptr<Enemy> enemy = mEnemy.lock();

	//if no enemy in range -> search for new enemy
	if (enemy == nullptr || Vector2Distance({ enemy->mX, enemy->mY }, { mX + mEnvironment.mTileSize / 2, mY + mEnvironment.mTileSize / 2 }) > mRange)
	{
		FindEnemy();
	}

	//if enemy in range -> shoot
	if (enemy != nullptr)
	{
		mAngle = atan2(enemy->mY - (mY + mEnvironment.mTileSize / 2), enemy->mX - (mX + mEnvironment.mTileSize / 2));

		mCurrentFireTime -= deltaTime;
		if (mCurrentFireTime <= 0)
		{
			mGameManager->SpawnBullet(mX + mEnvironment.mTileSize / 2, mY + mEnvironment.mTileSize / 2, mAngle);

			mCurrentFireTime += 1 / mFireRate;
		}
	}
}

void Turret::Draw()
{
	Rectangle source{ 0, 0, mTexture.width, mTexture.height };
	Rectangle dest{ mX + mEnvironment.mTileSize / 2, mY + mEnvironment.mTileSize / 2, mTexture.width / 2.0f, mTexture.height / 2.0f };
	Vector2 origin{ dest.width / 2, dest.height / 2 };

	DrawTexturePro(mTexture, source, dest, origin, mAngle * RAD2DEG, WHITE);

	//debug
	//DrawCircleLines(mX + mEnvironment.mTileSize / 2, mY + mEnvironment.mTileSize / 2, mRange, RED);
}

//Find if enemy in range
void Turret::FindEnemy()
{
	std::vector<std::shared_ptr<Enemy>>& allEnemies = mGameManager->GetAllEnemies();

	mEnemy.reset();

	for (std::shared_ptr<Enemy>& enemy : allEnemies)
	{
		if (enemy != nullptr &&
			Vector2Distance({ enemy->mX, enemy->mY }, { mX + mEnvironment.mTileSize / 2, mY + mEnvironment.mTileSize / 2 }) < mRange)
		{
			mEnemy = enemy;
			return;
		}
	}
}
