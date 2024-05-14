#include "GameManager.h"

#include <iostream>

//printf("%i\n", static_cast< int >( tiledata->mTileType ));

void GameManager::Init()
{
	//initialize environment
    mEnvironment.Init();
	mEnemy.Init();

	mPosTurret = LoadTexture("resources/towerDefense_tile108.png");
	mTurretIndex = 0;
}

bool GameManager::Update(float deltaTime)
{
	mEnemy.Update(deltaTime);

	//create new turret
	int mouseX = floorf(GetMouseX() / mEnvironment.mTileSize);
	int mouseY = floorf(GetMouseY() / mEnvironment.mTileSize);

	const TileData* tiledata = mEnvironment.GetTileDataAtPos(mouseX, mouseY);

	if (tiledata != nullptr && tiledata->mTileType == TilesType::GRASS)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			mAllTurrets.push_back(Turret(GetMouseX(), GetMouseY()));
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
	mEnemy.Draw();

	//Draw all turrets
	if (!mAllTurrets.empty())
	{
		for (int turret = 0; turret < mAllTurrets.size(); turret++)
		{
			mAllTurrets[turret].Draw();
		}
	}
}
