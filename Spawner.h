#pragma once

class GameManager;

class Spawner
{
public:
	Spawner(GameManager* gameManager, float x, float y);

	void Update(float deltaTime);

	void NewWave();
	void SetEnemyKilled(int count);

	int GetCurrentWave();
	float GetCurrentTimeBeforeWave();

	float mX = 10;
	float mY = 10;

	int mEnemyKilled = 0;

private:
	const float mTimeBetweenWave = 5.0f;
	const float mTimeBeforeNewWave = 10.0f;

	float mCurrentTimeBeforeNewWave = mTimeBeforeNewWave;

	float mSpawnTime = 1.0f; //time between enemy
	float mCurrentSpawnTime = mTimeBetweenWave;
	int mEnemyToSpawn = 2;
	int mEnemy = mEnemyToSpawn;

	int mWaveCount = 1;

	GameManager* mGameManager;
};

