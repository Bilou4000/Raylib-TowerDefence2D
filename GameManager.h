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
		{201, 157},
		{197, 606},
		{405, 613},
		{393, 305},
		{599, 304},
		{608, 602},
		{848, 611},
		{855, 152},
		{1103, 157},
		{1103, 605},
		{1270, 604},
	};

	Enemy mEnemy{ mEnvironment, mMainPath };
};

