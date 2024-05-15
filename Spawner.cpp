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
		//mSpawnTime = mTimeBetweenWave;
		//mCurrentSpawnTime = mSpawnTime;

		//if (mCurrentSpawnTime <= 0)
		//{
			NewWave();
		//}
	}
	else if (mEnemyKilled < mEnemyToSpawn)
	{
		mSpawnTime = 1.0f;
	}

	//mCurrentTimeBeforeNewWave -= deltaTime;

	//if (mCurrentTimeBeforeNewWave <= 0)
	//{
	//	NewWave();

	//}
}

void Spawner::NewWave()
{
	mSpawnTime = mTimeBetweenWave;
	mCurrentSpawnTime = mSpawnTime;

	if (mCurrentSpawnTime <= 0)
	{
		mWaveCount++;

		mEnemyKilled = 0;
		mEnemyToSpawn++;
		mEnemy = mEnemyToSpawn;

		//mCurrentTimeBeforeNewWave += mTimeBeforeNewWave;
	}

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
