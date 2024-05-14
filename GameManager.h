#pragma once

#include "raylib.h"
#include "Environment.h"
//************** will have to change for spwaner ; taking care of all enemies
#include "Enemy.h"

class GameManager
{
public:
	void Init();
	bool Update(float deltaTime);
	void Draw();

private:
	Environment mEnvironment {};

	std::vector<Vector2> mMainPath {
		{ 194, 154 },
		{ 203, 606 },
		{ 399, 604 },
		{ 400, 299 },
		{ 600, 304 },
		{ 605, 603 },
		{ 846, 599 },
		{ 854, 150 },
		{ 1101, 154 },
		{ 1099, 603 },
		{ 1270, 604 },
	};

	Enemy mEnemy{ mEnvironment, mMainPath };
};

