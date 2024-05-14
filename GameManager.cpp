#include "GameManager.h"

#include <iostream>

void GameManager::Init()
{
	//initialize environment
    mEnvironment.Init();
	mEnemy.Init();
}

bool GameManager::Update(float deltaTime)
{
	mEnemy.Update(deltaTime);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
	{
		printf("%d, %d\n", GetMouseX(), GetMouseY());
	}

	const TileData* tiledata = mEnvironment.GetTileDataAtPos(GetMouseX(), GetMouseY());

	if (tiledata->mTileType == TilesType::GRASS)
	{
		//tiledata->mColor = DARKGREEN;
	}

	return false;
}

void GameManager::Draw()
{
	//Draw Environment (tiles)
	mEnvironment.Draw();
	mEnemy.Draw();
}
