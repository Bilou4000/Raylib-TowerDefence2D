#pragma once

#include "raylib.h"
#include "Turret.h"
//************** will have to change for spwaner ; taking care of all enemies

class GameManager
{
public:
	void Init();
	bool Update(float deltaTime);
	void Draw();

	std::vector<Enemy>& GetAllEnemies();

private:
	Texture2D mPosTurret;
	Environment mEnvironment {};

	std::vector<Turret> mAllTurrets{};
	std::vector<Enemy> mAllEnemies{};

	std::vector<Vector2> mMainPath {
		{ 200, 154 },
		{ 200, 606 },
		{ 400, 606 },
		{ 400, 300 },
		{ 605, 300 },
		{ 605, 600 },
		{ 850, 600 },
		{ 850, 155 },
		{ 1100, 155 },
		{ 1100, 604 },
		{ 1227, 604 },
		{ 1270, 604 },
	};
};

