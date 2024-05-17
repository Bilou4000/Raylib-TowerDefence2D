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
		mSpawnTime = 1.0f;
		mIsWaitingForWave = false;

		//spawn enemy
		mGameManager->SpawnEnemy(mX, mY);
		mEnemy--;

		mCurrentSpawnTime += mSpawnTime;
	}
}

void Spawner::NewWave()
{
	mIsWaitingForWave = true;
	mSpawnTime = mTimeBetweenWave;
	mCurrentSpawnTime = mSpawnTime;

	mEnemyToSpawn++;
	mEnemy = mEnemyToSpawn;
	mGameManager->mEnemyCount = mEnemyToSpawn;
	mGameManager->GetAllEnemies().clear();
}


int Spawner::GetRemainingEnemies()
{
	return mEnemy;
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

	mEnemyToSpawn = mStartEnemyToSpawn;
	mEnemy = mEnemyToSpawn;

	mGameManager->mEnemyCount = mEnemyToSpawn;
}
