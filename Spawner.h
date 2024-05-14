#pragma once

class GameManager;

class Spawner
{
public:
	Spawner(GameManager* gameManager, float x, float y);

	void Update(float deltaTime);

	float mX = 10;
	float mY = 10;

private:
	const float mSpawnTime = 1.0f;

	int mEnemyToSpawn = 5;
	float mCurrentSpawnTime = mSpawnTime;

	int mCurrentWave = 1;

	GameManager* mGameManager;
};

