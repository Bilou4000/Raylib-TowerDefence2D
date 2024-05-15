#include "GameManager.h"

#include <iostream>

void GameManager::Init()
{
	//initialize environment
    mEnvironment.Init();

	mPosTurret = LoadTexture("resources/towerDefense_tile016-removebg-preview.png");
}

bool GameManager::Update(float deltaTime)
{
	//update turrets
	for (Turret& turret : mAllTurrets)
	{
		turret.Update(deltaTime);
	}

	//enemies update
	for (std::shared_ptr<Enemy>& enemy : mAllEnemies)
	{
		if (enemy != nullptr)
		{
			enemy->Update(deltaTime);
		}
	}

	//bullets update
	for (std::shared_ptr<Bullet>& bullet : mAllBullets)
	{
		if (bullet != nullptr)
		{
			bullet->Update(deltaTime);
		}
	}

	//update spawner
	mSpawner.Update(deltaTime);

	//create new turret
	CreateNewTurret();

	//destroy bullets and enemies
	DestroyBulletAndEnemies();

	//create new wave if time is up
	//mCurrentTimeBeforeNewWave -= deltaTime;

	//if (mCurrentTimeBeforeNewWave <= 0)
	//{
	//	mSpawner.NewWave();
	//	mCurrentTimeBeforeNewWave += mTimeBeforeNewWave;
	//}
	

	return false;
}

void GameManager::CreateNewTurret()
{
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

			if (canPlaceTurret && mMoney >= mTurretCost)
			{
				mAllTurrets.emplace_back(this, x, y);
				mMoney -= mTurretCost;
			}
		}
	}
}

void GameManager::DestroyBulletAndEnemies()
{
	for (int bullet = 0; bullet < mAllBullets.size(); bullet++)
	{
		for (int enemy = 0; enemy < mAllEnemies.size(); enemy++)
		{
			if (mAllEnemies[enemy] != nullptr && mAllBullets[bullet] != nullptr &&
				CheckCollisionCircles({ mAllBullets[bullet]->mX, mAllBullets[bullet]->mY }, 8, { mAllEnemies[enemy]->mX, mAllEnemies[enemy]->mY }, 20))
			{
				//destroy bullet if it touches an enemy
				mAllBullets[bullet].reset();

				//damage enemy if health > 0, else if health <= 0 -> destroy enemy 
				if (mAllEnemies[enemy]->mLives > 0)
				{
					mAllEnemies[enemy]->mLives--;
				}
				else if (mAllEnemies[enemy]->mLives <= 0)
				{
					mMoney += 5;
					mSpawner.SetEnemyKilled(1);
					mAllEnemies[enemy].reset();
				}
			}
		}

		//destroy bullet if it gets out of screen
		if (mAllBullets[bullet] != nullptr && (mAllBullets[bullet]->mX < 0 || mAllBullets[bullet]->mY < 0
			|| mAllBullets[bullet]->mX > GetScreenWidth() || mAllBullets[bullet]->mY > GetScreenHeight()))
		{
			mAllBullets[bullet].reset();
			printf("isdestroyed\n");
		}
	}
}

void GameManager::Draw()
{
	//Draw rectangle with all game info (wave, money etc.)
	DrawRectangle(0, 720, GetScreenWidth(), GetScreenHeight() - 720, {113, 137, 137, 255});
	DrawText(TextFormat("WAVE : %d", mSpawner.GetCurrentWave()),
		GetScreenWidth() / 2 - MeasureText(TextFormat("WAVE : %d", mSpawner.GetCurrentWave()), 40) / 2,
		785, 40, WHITE);
	DrawText(TextFormat("NEXT wave in : %.2f", mSpawner.GetCurrentTimeBeforeWave()),
		GetScreenWidth() - MeasureText(TextFormat("NEXT wave in : %.2f", mSpawner.GetCurrentTimeBeforeWave()), 30) - 30,
		785, 30, WHITE);
	DrawText(TextFormat("MONEY : %d", mMoney), 30, 785, 40, WHITE);

	//Draw Environment (tiles)
	mEnvironment.Draw();

	//Draw possible turret placement
	DrawTurretPlacement();

	//Draw Enemies
	for (std::shared_ptr<Enemy>& enemy : mAllEnemies)
	{
		if (enemy != nullptr)
		{
			enemy->Draw();
		}
	}

	//Draw all turrets
	for (Turret& turret : mAllTurrets)
	{
		turret.Draw();
	}

	//Draw all bullets
	for (std::shared_ptr<Bullet>& bullet : mAllBullets)
	{
		if (bullet != nullptr)
		{
			bullet->Draw();
		}
	}
}

void GameManager::DrawTurretPlacement()
{
	int mouseX = floorf(GetMouseX() / mEnvironment.mTileSize);
	int mouseY = floorf(GetMouseY() / mEnvironment.mTileSize);

	//Draw possible turret placement
	const TileData* tiledata = mEnvironment.GetTileDataAtPos(mouseX, mouseY);

	if (tiledata != nullptr && tiledata->mTileType == TilesType::GRASS)
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
			if (mMoney >= mTurretCost)
			{
				DrawTextureEx(mPosTurret, { mouseX * mEnvironment.mTileSize, mouseY * mEnvironment.mTileSize }, 0, 0.4f, GREEN);
			}
			else if (mMoney < mTurretCost)
			{
				DrawTextureEx(mPosTurret, { mouseX * mEnvironment.mTileSize, mouseY * mEnvironment.mTileSize }, 0, 0.4f, RED);
			}
		}
	}
}

void GameManager::SpawnEnemy(float x, float y)
{
	mAllEnemies.push_back(std::make_shared<Enemy>(mEnvironment, mMainPath, x, y, 3));
}

void GameManager::SpawnBullet(float x, float y, float angle)
{
	mAllBullets.push_back(std::make_shared<Bullet>(x, y, angle));
}

std::vector<std::shared_ptr<Enemy>>& GameManager::GetAllEnemies()
{
	return mAllEnemies;
}
