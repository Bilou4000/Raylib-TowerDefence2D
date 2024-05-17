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
	void ChooseSpawner();

	void SpawnEnemy(float x, float y);
	void SpawnBullet(float x, float y, float angle);

	void ResetGame();

	int GetWavesCount();

	std::vector<std::shared_ptr<Enemy>>& GetAllEnemies();

	int mEnemyCount = 0;

private:
	const int mTurretCost = 30;
	const int mEnemyMoney = 5;
	const int mStartCastleLife = 5;
	const int mStartMoney = 60;
	const int mStartWaveCount = 1;
	const int mToAddSpeed = 10.0f;

	const Vector2 mPosMainSpawn{ 50, 150 };
	const Vector2 mPosSecondSpawn { 500, 20 };

	Texture2D mPosTurret;
	Texture2D mCastleUp;
	Texture2D mCastleDown;
	Environment mEnvironment {};
	Spawner mSpawner{this, 50, 150 };

	const std::vector<Vector2> mMainPath {
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

	const std::vector<Vector2> mSecondPath {
		{ 500, 300 },
		{ 605, 300 },
		{ 605, 600 },
		{ 850, 600 },
		{ 850, 155 },
		{ 1100, 155 },
		{ 1100, 604 },
		{ 1227, 604 },
		{ 1270, 604 },
	};

	std::vector<Vector2> mCurrentPath = mMainPath;
	std::vector<std::shared_ptr<Bullet>> mAllBullets {};
	std::vector<std::shared_ptr<Enemy>> mAllEnemies {};
	std::vector<Turret> mAllTurrets {};

	int mMoney = mStartMoney;
	int mCastleLife = mStartCastleLife;
	int mWaveCount = mStartWaveCount;
	float mCurrentToAddSpeed = 0;
};

