#include "GameManager.h"

#include <iostream>

//printf("%i\n", static_cast< int >( tiledata->mTileType ));

void GameManager::Init()
{
	//initialize environment
    mEnvironment.Init();

	mPosTurret = LoadTexture("resources/towerDefense_tile108.png");
}

bool GameManager::Update(float deltaTime)
{
	//update turrets
	for (Turret& turret : mAllTurrets)
	{
		turret.Update(deltaTime);
	}

	//enemies update
	for (Enemy& enemy : mAllEnemies)
	{
		enemy.Update(deltaTime);
	}

	mSpawner.Update(deltaTime);

	//create new turret
	int mouseX = floorf(GetMouseX() / mEnvironment.mTileSize);
	int mouseY = floorf(GetMouseY() / mEnvironment.mTileSize);

	const TileData* tiledata = mEnvironment.GetTileDataAtPos(mouseX, mouseY);

	if (tiledata != nullptr && tiledata->mTileType == TilesType::GRASS)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			float x = floorf(GetMouseX() / mEnvironment.mTileSize) * mEnvironment.mTileSize;
			float y = floorf(GetMouseY() / mEnvironment.mTileSize) * mEnvironment.mTileSize;

			bool canPlaceTurret = true;

			for (Turret& turret : mAllTurrets)
			{
				if (turret.mX == x && turret.mY == y)
				{
					canPlaceTurret = false;
					break;
				}
			}

			if (canPlaceTurret)
			{
				mAllTurrets.emplace_back(this, x, y);
			}
		}
	}

	return false;
}

void GameManager::Draw()
{
	//Draw Environment (tiles)
	mEnvironment.Draw();

	int mouseX = floorf(GetMouseX() / mEnvironment.mTileSize);
	int mouseY = floorf(GetMouseY() / mEnvironment.mTileSize);

	const TileData* tiledata = mEnvironment.GetTileDataAtPos(mouseX, mouseY);

	if (tiledata != nullptr && tiledata->mTileType == TilesType::GRASS)
	{
		DrawTextureEx(mPosTurret, { mouseX * mEnvironment.mTileSize, mouseY * mEnvironment.mTileSize }, 0, 0.4f, WHITE);
	}

	//Draw Enemies
	for (Enemy& enemy : mAllEnemies)
	{
		enemy.Draw();
	}

	//Draw all turrets
	for (Turret& turret : mAllTurrets)
	{
		turret.Draw();
	}
}

void GameManager::SpawnEnemy(float x, float y)
{
	mAllEnemies.emplace_back(mEnvironment, mMainPath, x, y);
}

std::vector<Enemy>& GameManager::GetAllEnemies()
{
	return mAllEnemies;
}
