#pragma once

#include "Enemy.h"

class GameManager;

class Spawner
{
public:
	Spawner(GameManager* gameManager, float x, float y);

	void Update(float deltaTime);

	void NewWave();

	int GetRemainingEnemies();
	float GetCurrentTimeBeforeWave();
	bool GetIfWaitingForEnemy();

	void ResetSpawner();

	float mX = 10;
	float mY = 10;

private:
	const float mTimeBetweenWave = 5.0f;
	const float mTimeBeforeNewWave = 10.0f;
	const float mStartEnemyToSpawn = 1;

	float mSpawnTime = 1.0f; //time between enemy
	float mCurrentSpawnTime = mTimeBetweenWave;
	int mEnemyToSpawn = mStartEnemyToSpawn;
	int mEnemy = mEnemyToSpawn;

	bool mIsWaitingForWave;

	GameManager* mGameManager;
};

