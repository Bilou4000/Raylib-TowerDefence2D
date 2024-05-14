#include "Turret.h"

#include "raymath.h"
#include <iostream>
#include <cmath>

Turret::Turret(float x, float y)
{
	mX = x;
	mY = y;

	mTexture = LoadTexture("resources/towerDefense_tile249.png");
}

void Turret::Update()
{
}

void Turret::Draw()
{
	int mouseX = floorf(mX / mEnvironment.mTileSize);
	int mouseY = floorf(mY / mEnvironment.mTileSize);

	const TileData* tiledata = mEnvironment.GetTileDataAtPos(mouseX, mouseY);

	if (tiledata != nullptr && tiledata->mTileType == TilesType::GRASS)
	{
		DrawTextureEx(mTexture, { mouseX * mEnvironment.mTileSize, mouseY * mEnvironment.mTileSize }, 0, 0.4f, WHITE);
	}
}
