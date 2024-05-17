#include "GameManager.h"

#include <iostream>

void GameManager::Init()
{
	//initialize environment
    mEnvironment.Init();

	mPosTurret = LoadTexture("resources/towerDefense_tile016-removebg-preview.png");
	mCastleUp = LoadTexture("resources/medievalStructure_02.png");
	mCastleDown = LoadTexture("resources/medievalStructure_06.png");

	ResetGame();
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

			if (enemy->GetIfAtCaslte())
			{
				mCastleLife--;
				mEnemyCount--;
				enemy.reset();
			}
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

	if (mEnemyCount <= 0)
	{
		mSpawner.NewWave();
		mWaveCount++;
	}

	if (mCastleLife <= 0)
	{
		return true;
	}

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
				if (mAllEnemies[enemy]->mLives <= 0)
				{
					mEnemyCount--;
					mMoney += mEnemyMoney;
					//mSpawner.SetEnemyKilled(1);
					mAllEnemies[enemy].reset();
				}
			}
		}

		printf("%i\n", mEnemyCount);

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
	DrawText(TextFormat("Money : %d", mMoney), 30, 785, 40, WHITE);
	DrawText(TextFormat("WAVE : %d", mWaveCount),
		GetScreenWidth() / 2 - MeasureText(TextFormat("WAVE : %d", mWaveCount), 50) / 2,
		785, 50, WHITE);

	//draw enemies count
	if (!mSpawner.GetIfWaitingForEnemy())
	{
		DrawText(TextFormat("Enemies left : %i", mEnemyCount),
			GetScreenWidth() - MeasureText(TextFormat("Enemies left : %i", mEnemyCount), 40) - 30,
			785, 40, RED);
		DrawText("Enemies left :",
			GetScreenWidth() - MeasureText(TextFormat("Enemies left : %i", mEnemyCount), 40) - 30,
			785, 40, WHITE);
	}
	else
	{
		DrawText("Enemies left : 0",
			GetScreenWidth() - MeasureText("Enemies left : 0", 40) - 30,
			785, 40, WHITE);
	}

	//Draw Environment (tiles)
	mEnvironment.Draw();

	if(mEnemyCount)

	//Draw Castle;
	DrawTextureEx(mCastleDown, { 1175, 570 }, 0, 0.8f, WHITE);
	DrawTextureEx(mCastleUp, { 1175, 470 }, 0, 0.8f, WHITE);

	//Draw Castle life bar
	DrawRectangle(1187, 480, 15 * mStartCastleLife, 10, DARKGRAY);
	DrawRectangle(1187, 480, 15 * mCastleLife, 10, RED);

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

	//draw time before new wave
	if (mSpawner.GetIfWaitingForEnemy())
	{
		DrawText(TextFormat("Next wave in : %.0f", mSpawner.GetCurrentTimeBeforeWave()),
			30, 700, 30, RED);
		DrawText("Next wave in :", 30, 700, 30, BLACK);
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

void GameManager::ResetGame()
{
	mCastleLife = mStartCastleLife;
	mWaveCount = mStartWaveCount;
	mMoney = mStartMoney;
	mEnemyCount = 0;

	mAllTurrets.clear();
	mAllEnemies.clear();
	mAllBullets.clear();

	mSpawner.ResetSpawner();
}

int GameManager::GetWavesCount()
{
	return mWaveCount;
}

std::vector<std::shared_ptr<Enemy>>& GameManager::GetAllEnemies()
{
	return mAllEnemies;
}
