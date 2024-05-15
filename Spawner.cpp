#include "Spawner.h"

#include "GameManager.h"

Spawner::Spawner(GameManager* gameManager, float x, float y)
	: mGameManager(gameManager), mX(x), mY(y)
{
	mEnemyKilled = 0;
}

void Spawner::Update(float deltaTime)
{
	mCurrentSpawnTime -= deltaTime;

	if (mCurrentSpawnTime <= 0 && mEnemy > 0)
	{
		//spawn enemy
		mGameManager->SpawnEnemy(mX, mY);
		mEnemy--;

		mCurrentSpawnTime += mSpawnTime;
	}

	//new wave
	if (mEnemyKilled >= mEnemyToSpawn)
	{
		NewWave();
	}
	else if (mEnemyKilled < mEnemyToSpawn)
	{
		mSpawnTime = 1.0f;
	}
}

void Spawner::NewWave()
{
	//need to fix pb where it get stuck at 5 sec
	mSpawnTime = mTimeBetweenWave;
	mCurrentSpawnTime = mSpawnTime;

	mWaveCount++;

	mEnemyKilled = 0;
	mEnemyToSpawn++;
	mEnemy = mEnemyToSpawn;
}

void Spawner::SetEnemyKilled(int count)
{
	mEnemyKilled += count;
}

int Spawner::GetCurrentWave()
{
	return mWaveCount;
}

float Spawner::GetCurrentTimeBeforeWave()
{
	return mCurrentTimeBeforeNewWave;
}
