#include "Spawner.h"

#include "GameManager.h"

Spawner::Spawner(GameManager* gameManager, float x, float y)
	: mGameManager(gameManager), mX(x), mY(y)
{
}

void Spawner::Update(float deltaTime)
{
	mCurrentSpawnTime -= deltaTime;

	if (mCurrentSpawnTime <= 0 && mEnemyToSpawn > 0)
	{
		//spawn enemy
		mGameManager->SpawnEnemy(mX, mY);

		mEnemyToSpawn--;
		mCurrentSpawnTime += mSpawnTime;
	}
}
