#pragma once

#include "raylib.h"

enum class TilesType
{
	GRASS,
	ROAD,
	SPAWN_VERTICAL,
	SPAWN_HORIZONTAL,

	MAX_COUNT,
};

struct TileData
{
	TilesType mTileType = TilesType::GRASS;
	Color mColor = LIME;
	Texture2D ImageTexture;
	bool mIsRoad = false;
};

