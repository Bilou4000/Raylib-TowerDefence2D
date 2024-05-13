#pragma once

#include <vector>
#include "Tile.h"

struct Checkpoint
{
    bool mIsPassed = false;
    bool mIsFinishLine = false;
    Rectangle mArea {};
};

class Environment
{
public:
	Environment();

    void InitCheckpoints();
    void Init();
	void Draw();

    bool CanPassFinishLine();

    Checkpoint* GetCheckpointAtPos(int tileX, int tileY);
	const TileData* GetTileDataAtPos(int tileX, int tileY) const;

	const float mTileSize = 50.0f;

    static const int mTilesX = 26;
    static const int mTilesY = 15;

    std::vector<Checkpoint> mAllCheckpoints;

private:

    //Map of race
    //0 is grass, 1 is road, 2 is obstacle, 3 is checkpoint and 4 is finishLine
	int mTiles[mTilesY][mTilesX]
	{
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 0, 0 },
        { 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};

    TileData mTilesData[(int) TilesType::MAX_COUNT];
};