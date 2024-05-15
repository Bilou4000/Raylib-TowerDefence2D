#pragma once

#include "raylib.h"

#include "Turret.h"
#include "Spawner.h"
#include "Bullet.h"

#include <memory>

class GameManager
{
public:
	void Init();
	bool Update(float deltaTime);
	void Draw();

	void DrawTurretPlacement();

	void CreateNewTurret();
	void DestroyBulletAndEnemies();

	void SpawnEnemy(float x, float y);
	void SpawnBullet(float x, float y, float angle);

	std::vector<std::shared_ptr<Enemy>>& GetAllEnemies();

private:
	const int mTurretCost = 30;
	//const float mTimeBeforeNewWave = 10.0f;

	//float mCurrentTimeBeforeNewWave = mTimeBeforeNewWave;

	Texture2D mPosTurret;
	Environment mEnvironment {};
	Spawner mSpawner{this, 50, 150 };

	std::vector<std::shared_ptr<Bullet>> mAllBullets{};
	std::vector<Turret> mAllTurrets{};
	std::vector<std::shared_ptr<Enemy>> mAllEnemies{};

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

	int mMoney = 60;
};

