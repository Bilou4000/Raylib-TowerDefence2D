#pragma once

class GameManager;

class Spawner
{
public:
	Spawner(GameManager* gameManager, float x, float y);

	void Update(float deltaTime);
	void SetEnemyKilled(int count);

	float mX = 10;
	float mY = 10;

	int mEnemyKilled = 0;

private:
	const float mTimeBetweenWave = 5.0f;

	float mSpawnTime = 1.0f; //time between enemy
	float mCurrentSpawnTime = mTimeBetweenWave;
	int mEnemyToSpawn = 2;
	int mEnemy = mEnemyToSpawn;

	int mWaveCount = 1;

	GameManager* mGameManager;
};

