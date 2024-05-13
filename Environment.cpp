#include "Environment.h"

Environment::Environment()
{
	//create tileData and update their datas
	//grass
	TileData& tileGrass = mTilesData[(int)TilesType::GRASS];
	tileGrass.mColor = WHITE;
	tileGrass.mSpeedMultiplier = 0.5f;

	//road
	TileData& tileRoad = mTilesData[(int) TilesType::ROAD];
	tileRoad.mColor = WHITE;
	tileRoad.mSpeedMultiplier = 1.0f;

	//obstacle (tree)
	TileData& tileObstacle = mTilesData[(int) TilesType::OBSTACLE];
	tileObstacle.mColor = { 220, 220, 220, 255 };
	tileObstacle.mIsObstacle = true;

	//checkpoint
	TileData& tileCheckpoint = mTilesData[(int) TilesType::CHECKPOINT];
	//tileCheckpoint.mColor = LIGHTGRAY;
	tileCheckpoint.mColor = { 230, 230, 230, 255 };
	tileCheckpoint.mSpeedMultiplier = tileRoad.mSpeedMultiplier;


	//finishLine
	TileData& tileFinishLine = mTilesData[(int) TilesType::FINISHLINE];
	tileFinishLine.mColor = WHITE;
	tileFinishLine.mSpeedMultiplier = tileRoad.mSpeedMultiplier;

	//add all created types to mTilesData
	for (int i = 0; i < (int) TilesType::MAX_COUNT; i++)
	{
		TileData& tileData = mTilesData[i];
		tileData.mTileType = (TilesType) i;
	}

	//Create the Checkpoints
	InitCheckpoints();
}

void Environment::InitCheckpoints()
{
	mAllCheckpoints.clear();

	const int checkpointTileID = (int) TilesType::CHECKPOINT;
	const int finishLineTileID = (int) TilesType::FINISHLINE;

	//For every tile
	for (int y = 0; y < mTilesY; y++)
	{
		for (int x = 0; x < mTilesX; x++)
		{
			//check if the tile is a checkpoint or a finishLine
			if (mTiles[y][x] == checkpointTileID || mTiles[y][x] == finishLineTileID)
			{
				//if there is an existing checkpoint on top of an other tile checkpoint -> get that first checkpoint and make it bigger to fit both tiles
				if (y - 1 >= 0 && (mTiles[y - 1][x] == checkpointTileID || mTiles[y-1][x] == finishLineTileID))
				{ 
					Checkpoint* checkpoint = GetCheckpointAtPos(x, y - 1);
					checkpoint->mArea.height += mTileSize;
				}
				//if there is an existing checkpoint on the left of an other tile checkpoint -> get that first checkpoint and make it bigger to fit both tiles
				else if (x - 1 >= 0 && (mTiles[y][x - 1] == checkpointTileID || mTiles[y][x - 1] == finishLineTileID))
				{
					Checkpoint* checkpoint = GetCheckpointAtPos(x - 1, y);
					checkpoint->mArea.width += mTileSize;
				}
				//if there is no checkpoint near our ile checkpoint, create one on top of it
				else
				{
					Checkpoint newCheckpoint {};
					newCheckpoint.mArea = { x * mTileSize, y * mTileSize, mTileSize, mTileSize };

					//if the tile is a finish line, change the checkpoint data to correspond it
					if (mTiles[y][x] == finishLineTileID)
					{
						newCheckpoint.mIsFinishLine = true;
					}

					//add all created checkpoints to mAllCheckpoints
					mAllCheckpoints.push_back(newCheckpoint);
				}
			}
		}
	}
}

void Environment::Init()
{
	//Load all textures of tile
	TileData& tileGrass = mTilesData[(int) TilesType::GRASS];
	tileGrass.ImageTexture = LoadTexture("resources/land_grass04.png");

	TileData& tileRoad = mTilesData[(int) TilesType::ROAD];
	tileRoad.ImageTexture = LoadTexture("resources/road/road_asphalt22.png");

	TileData& tileObstacle = mTilesData[(int) TilesType::OBSTACLE];
	tileObstacle.ImageTexture = LoadTexture("resources/tree_small.png");

	TileData& tileCheckpoint = mTilesData[(int) TilesType::CHECKPOINT];
	tileCheckpoint.ImageTexture = LoadTexture("resources/road/road_asphalt22.png");

	TileData& tileFinishLine = mTilesData[(int) TilesType::FINISHLINE];
	tileFinishLine.ImageTexture = LoadTexture("resources/road/road_asphalt88.png");

	//reset checkpoints
	for (Checkpoint& checkpoint : mAllCheckpoints)
	{
		checkpoint.mIsPassed = false;
	}
}

void Environment::Draw()
{
	//Draw all of my tiles that are not obstacle
	for (int y = 0; y < mTilesY; y++)
	{
		for (int x = 0; x < mTilesX; x++)
		{
			const TileData* theTile = GetTileDataAtPos(x, y);
			if (!theTile->mIsObstacle)
			{
				DrawTextureEx(theTile->ImageTexture, { x * mTileSize, y * mTileSize }, 0, 0.4f, theTile->mColor);
			}
		}
	}

	//draw all my obstacle tiles on top of it
	for (int y = 0; y < mTilesY; y++)
	{
		for (int x = 0; x < mTilesX; x++)
		{
			const TileData* theTile = GetTileDataAtPos(x, y);
			if (theTile->mIsObstacle)
			{
				DrawTextureEx(theTile->ImageTexture, { x * mTileSize - 10.0f, y * mTileSize - 10.0f }, 0, 0.5f, theTile->mColor);
			}
		}
	}

	//DEBUG checkpoint **************************************************************************
	for (Checkpoint& checkpoint : mAllCheckpoints)
	{
		Color debugColor = { 130, 158, 159, 255 };
		if (!checkpoint.mIsFinishLine)
		{
			DrawRectangleLinesEx(checkpoint.mArea, 2.0f, checkpoint.mIsPassed ? GREEN : debugColor);
		}
	}
}

bool Environment::CanPassFinishLine()
{
	//check if all checkpoints have been passed to pass the finish line
	for (Checkpoint& checkpoint : mAllCheckpoints)
	{
		if (!checkpoint.mIsFinishLine && !checkpoint.mIsPassed)
		{
			return false;
		}
	}

	return true;
}

//get the checkpoint of a specific tile
Checkpoint* Environment::GetCheckpointAtPos(int tileX, int tileY)
{
	//don't check if out of screen
	if (tileX >= mTilesX || tileX < 0 || tileY >= mTilesY || tileY < 0)
	{
		return nullptr;
	}

	Vector2 pos { tileX * mTileSize, tileY * mTileSize };
	for (Checkpoint& checkpoint : mAllCheckpoints)
	{
		if (CheckCollisionPointRec(pos, checkpoint.mArea))
		{
			return &checkpoint;
		}
	}

	return nullptr;
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
