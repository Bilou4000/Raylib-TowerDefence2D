#include "Enemy.h"

Enemy::Enemy(Environment& environment, std::vector<Vector2> path, float x, float y, float lives, float speed)
	: mEnvironment(environment), mPath(path), mX(x), mY(y), mLives(lives)
{
	mTexture = LoadTexture("resources/towerDefense_tile247.png");
	mSpeed += speed;

	//initialze all variable
	mIsAtCastle = false;
	mAngle = 0;
	mMaxLives = mLives;
}

void Enemy::Update(float deltaTime)
{
	Vector2 nextPos = mPath[mPathIndex];

	mAngle = atan2(nextPos.y - mY, nextPos.x - mX);

	//move Forward
	float x;
	float y;

	if (mPathIndex >= mPath.size() - 1)
	{
		x = mX;
		y = mY;
		mIsAtCastle = true;
		printf("ATTACK\n");
	}
	else
	{
		x = mX + cos(mAngle) * ( mSpeed * deltaTime );
		y = mY + sin(mAngle) * ( mSpeed * deltaTime );
	}

	//new Pos of enemy
	mX = x;
	mY = y;

	if (Vector2Distance({ mX,mY }, nextPos) <= mMinDistance) 
	{
		mPathIndex++;
	}
}

void Enemy::Draw()
{
	//Draw Enemy
	Rectangle source{ 0, 0, 128, 128 };
	Rectangle dest{ mX, mY, 128, 128 };

	Vector2 origin{ mWidth / 2, mHeight / 2 };

	DrawTexturePro(mTexture, source, dest, origin, mAngle * RAD2DEG, WHITE);

	//healthbar
	DrawRectangle(mX - mTexture.width / 6, mY - 50, 15 * mMaxLives, 10, DARKGRAY);
	DrawRectangle(mX - mTexture.width / 6, mY - 50, 15 * mLives, 10, RED);

	//Debug
	//DrawDebug();
}

void Enemy::DrawDebug()
{
	DrawCircleLines(mX, mY, 20, RED);
}

bool Enemy::GetIfAtCaslte()
{
	return mIsAtCastle;
}
