#include "Environment.h"

Environment::Environment()
{
	//create tileData and update their datas
	//grass
	TileData& tileGrass = mTilesData[(int)TilesType::GRASS];
	tileGrass.mColor = WHITE;

	//road
	TileData& tileRoad = mTilesData[(int) TilesType::ROAD];
	tileRoad.mColor = WHITE;
	tileRoad.mIsRoad = true;

	//spawn vertical
	TileData& tileSpawnVertical = mTilesData[(int) TilesType::SPAWN_VERTICAL];
	tileSpawnVertical.mColor = WHITE;
	tileSpawnVertical.mIsRoad = true;

	//spawn horizontal
	TileData& tileSpawnHorizontal = mTilesData[(int) TilesType::SPAWN_HORIZONTAL];
	tileSpawnHorizontal.mColor = WHITE;
	tileSpawnHorizontal.mIsRoad = true;

	//add all created types to mTilesData
	for (int i = 0; i < (int) TilesType::MAX_COUNT; i++)
	{
		TileData& tileData = mTilesData[i];
		tileData.mTileType = (TilesType) i;
	}
}

void Environment::Init()
{
	//Load all textures of tile
	TileData& tileGrass = mTilesData[(int) TilesType::GRASS];
	tileGrass.ImageTexture = LoadTexture("resources/towerDefense_tile188.png");

	TileData& tileRoad = mTilesData[(int) TilesType::ROAD];
	tileRoad.ImageTexture = LoadTexture("resources/road/towerDefense_tile159.png");

	TileData& tileSpawnVertical = mTilesData[(int) TilesType::SPAWN_VERTICAL];
	tileSpawnVertical.ImageTexture = LoadTexture("resources/towerDefense_tile178.png");

	TileData& tileSpawnHorizontal = mTilesData[(int) TilesType::SPAWN_HORIZONTAL];
	tileSpawnHorizontal.ImageTexture = LoadTexture("resources/towerDefense_tile224.png");
}

void Environment::Draw()
{
	//Draw all tiles
	for (int y = 0; y < mTilesY; y++)
	{
		for (int x = 0; x < mTilesX; x++)
		{
			const TileData* theTile = GetTileDataAtPos(x, y);

			DrawTextureEx(theTile->ImageTexture, { x * mTileSize, y * mTileSize }, 0, 0.4f, theTile->mColor);
		}
	}
}

//get the datas of a specific tile
const TileData* Environment::GetTileDataAtPos(int tileX, int tileY) const
{
	if(tileX >= mTilesX || tileX < 0 || tileY >= mTilesY || tileY < 0)
	{
		return nullptr;
	}

	return &mTilesData[mTiles[tileY][tileX]];
}
