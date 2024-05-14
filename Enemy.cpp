#include "Enemy.h"

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <cmath>

Enemy::Enemy(Environment& environment, std::vector<Vector2> path)
			: mEnvironment(environment), mPath(path)
{

}

void Enemy::Init()
{
	mTexture = LoadTexture("resources/towerDefense_tile247.png");

	//initialze all variable
	mIsAtCastle = false;
	mAngle = 0;
	mX = 50;
	mY = 150;
}

void Enemy::Update(float deltaTime)
{
	mSpeed = mMaxSpeed;

	Vector2 nextPos = mPath[mPathIndex];

	mAngle = atan2(nextPos.y - mY, nextPos.x - mX);

	//move Forward
	float x;
	float y;

	if (mPathIndex >= mPath.size() - 1)
	{
		x = mX;
		y = mY;
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

	//Debug
	DrawDebug();
}

void Enemy::DrawDebug()
{

}
