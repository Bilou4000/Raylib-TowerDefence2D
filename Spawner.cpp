#include "Spawner.h"

#include "GameManager.h"

Spawner::Spawner(GameManager* gameManager, float x, float y)
	: mGameManager(gameManager), mX(x), mY(y)
{
	ResetSpawner();
}

void Spawner::Update(float deltaTime)
{
	mCurrentSpawnTime -= deltaTime;

	if (mCurrentSpawnTime <= 0 && mEnemy > 0)
	{
		mIsWaitingForWave = false;

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

	printf("%i\n", mEnemyToSpawn);
}

void Spawner::NewWave()
{
	mIsWaitingForWave = true;
	mSpawnTime = mTimeBetweenWave;
	mCurrentSpawnTime = mSpawnTime;

	mWaveCount++;

	mEnemyKilled = 0;
	mEnemyToSpawn++;
	mEnemy = mEnemyToSpawn;
	mGameManager->GetAllEnemies().clear();
}

void Spawner::SetEnemyKilled(int count)
{
	mEnemyKilled += count;
}

int Spawner::GetRemainingEnemies()
{
	return mEnemy;
}

int Spawner::GetCurrentWave()
{
	return mWaveCount;
}

float Spawner::GetCurrentTimeBeforeWave()
{
	return mCurrentSpawnTime;
}

bool Spawner::GetIfWaitingForEnemy()
{
	return mIsWaitingForWave;
}

void Spawner::ResetSpawner()
{
	mIsWaitingForWave = true;

	mWaveCount = mStartWaveCount;
	mEnemyToSpawn = mStartEnemyToSpawn;
	mEnemy = mEnemyToSpawn;
	mEnemyKilled = 0;
}
