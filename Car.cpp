#include "Car.h"

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <cmath>

bool isInObstacle = false;

Car::Car( Environment& environment )
	: mEnvironment( environment )
{
}

void Car::Init()
{
	//Load Car Texture
	mCarTexture = LoadTexture("resources/car_blue_small_5.png");

	//Initialize all variable 
	isInObstacle = false;
	mX = 860;
	mY = 600;
	mRound = 1;
	mSpeed = 0;
	mAngle = 0;
}

bool Car::Update(float deltaTime)
{
	float targetSpeed = 0.0f;
	float accelerationSpeed = mAccelerationSpeed;

	//Go forward and Backward
	if (IsKeyDown(KEY_W))
	{
		targetSpeed = mMaxSpeed;
	}
	else if (IsKeyDown(KEY_S))
	{
		targetSpeed = -mMaxSpeed;
	}
	else
	{
		accelerationSpeed = mDeccelerationSpeed;
	}

	mSpeed = Lerp(mSpeed, targetSpeed, deltaTime * accelerationSpeed);

	//Turn
	if (IsKeyDown(KEY_D) && !isInObstacle)
	{
		mAngle += mSpeed / mMaxSpeed * mVelocity * DEG2RAD * deltaTime;
	}

	if (IsKeyDown(KEY_A) && !isInObstacle)
	{
		mAngle -= mSpeed / mMaxSpeed * mVelocity * DEG2RAD * deltaTime;
	}


	//Get pos of car in environment
	int carRow = floorf(mY / mEnvironment.mTileSize);
	int carColumn = floorf(mX / mEnvironment.mTileSize);

	const TileData* tiledata = mEnvironment.GetTileDataAtPos(carColumn, carRow);

	//change spped of car considering tiles
	float speedMultiplier = 1.0f;
	if (tiledata != nullptr)
	{
		speedMultiplier = tiledata->mSpeedMultiplier;
	}

	//MOVE in forward
	mCurrentSpeedMultiplier = Lerp(mCurrentSpeedMultiplier, speedMultiplier, deltaTime * 10.0f);

	float x = mX + cos(mAngle) * (mSpeed * mCurrentSpeedMultiplier * deltaTime);
	float y = mY + sin(mAngle) * (mSpeed * mCurrentSpeedMultiplier * deltaTime);

	//car collide ?
	bool hasCollided = false;
	for (int offsetRow = -1; offsetRow <= 1; offsetRow++)
	{
		for (int offsetColumn = -1; offsetColumn <= 1; offsetColumn++)
		{
			float tilePosX = carColumn + offsetColumn;
			float tilePosY = carRow + offsetRow;

			//check if car is on same pos as tile and check the 8 around it
			if (tilePosY < mEnvironment.mTilesY && tilePosX < mEnvironment.mTilesX
				&& tilePosY >= 0 && tilePosX >= 0)
			{
				const TileData* tiledata = mEnvironment.GetTileDataAtPos(tilePosX, tilePosY);

				if (tiledata != nullptr)
				{
					//check if tile is an obstacle
					if (tiledata->mIsObstacle)
					{
						Rectangle tile { tilePosX * mEnvironment.mTileSize, tilePosY * mEnvironment.mTileSize,
							mEnvironment.mTileSize, mEnvironment.mTileSize };

						//check if has collided
						if (CheckCollisionWith(x, y, tile))
						{
							x = mX;
							y = mY;
							mSpeed = 0;
							hasCollided = true;
							isInObstacle = true;
							break;
						}

						isInObstacle = false;
					}
					//check if tile is an obstacle or a finish line
					else if (tiledata->mTileType == TilesType::CHECKPOINT || tiledata->mTileType == TilesType::FINISHLINE)
					{
						bool canPass = true;

						//get the checkpoint at the car pos
						Checkpoint* checkpoint = mEnvironment.GetCheckpointAtPos(tilePosX, tilePosY);
						if (checkpoint->mIsFinishLine)
						{
							//check if we can pass finish line
							canPass = mEnvironment.CanPassFinishLine();
							//if yes and all round not completed -> new round + reset checkpoint
							if (mEnvironment.CanPassFinishLine() && mRound < mMaxRound)
							{
								mRound += 1;
								for (Checkpoint& checkpoint : mEnvironment.mAllCheckpoints)
								{
									checkpoint.mIsPassed = false;
								}
							}
							//if yes and all round completed -> end game
							else if (mEnvironment.CanPassFinishLine() && mRound >= mMaxRound)
							{
								return true;
							}
						}

						//passing a checkpoint if not already passed
						if (canPass && !checkpoint->mIsPassed && CheckCollisionWith(mX, mY, checkpoint->mArea))
						{
							checkpoint->mIsPassed = true;
						}
						
					}
				}
			}
		}
		if (hasCollided)
		{
			break;
		}
	}

	//new Pos of car
	mX = x;
	mY = y ;

	//Collision on wall
	if (mY < 0)
	{
		mY = 0;
	}
	if (mX < 0)
	{
		mX = 0;
	}
	if (mX > GetScreenWidth()) 
	{
		mX = GetScreenWidth(); 
	}
	if (mY > GetScreenHeight()) 
	{
		mY = GetScreenHeight(); 
	}

	return false;
}

void Car::Draw()
{
	//Draw Car
	Rectangle source { 0, 0, 65, 37 };
	Rectangle dest { mX, mY, 65, 35 };

	Vector2 origin{ mWidth / 1.3f, mHeight / 2 };

	DrawTexturePro(mCarTexture, source, dest, origin, mAngle * RAD2DEG, WHITE);

	//Show lap count
	DrawText(TextFormat("Lap %i/%i", mRound, mMaxRound), 10, 10, 50, WHITE);

	//DEBUG *******************************************************************************
	//DrawDebug();
}

void Car::DrawDebug()
{
	Vector2 hitboxForwardPos = GetHitboxPos(mX, mY, 0);
	Vector2 hitboxBackwardPos = GetHitboxPos(mX, mY, 1);

	DrawCircleLines(hitboxForwardPos.x, hitboxForwardPos.y, mHitboxRadius, RED);
	DrawCircleLines(hitboxBackwardPos.x, hitboxBackwardPos.y, mHitboxRadius, RED);

	int carRow = floorf(mY / mEnvironment.mTileSize);
	int carColumn = floorf(mX / mEnvironment.mTileSize);

	for (int offsetRow = -1; offsetRow <= 1; offsetRow++)
	{
		for (int offsetColumn = -1; offsetColumn <= 1; offsetColumn++)
		{
			float tilePosX = carColumn + offsetColumn;
			float tilePosY = carRow + offsetRow;

			//check if car is on same pos as tile and check the 8 around it
			if (tilePosY < mEnvironment.mTilesY && tilePosX < mEnvironment.mTilesX
				&& tilePosY >= 0 && tilePosX >= 0)
			{
				const TileData* tiledata = mEnvironment.GetTileDataAtPos(tilePosX, tilePosY);

				if (tiledata != nullptr)
				{
					const float tileSize = mEnvironment.mTileSize;

					//Draw all tiles around car, if one is an obstacle -> turn red
					DrawRectangleLines(tilePosX * tileSize, tilePosY * tileSize, tileSize, tileSize, tiledata->mIsObstacle ? RED : WHITE);
				}
			}
		}
	}
}

//Collision with the car
bool Car::CheckCollisionWith(float carPosX, float carPosY, const Rectangle& bounds)
{
	Vector2 hitboxForwardPos = GetHitboxPos(carPosX, carPosY, 0);
	Vector2 hitboxBackwardPos = GetHitboxPos(carPosX, carPosY, 1);

	return CheckCollisionCircleRec(hitboxForwardPos, mHitboxRadius, bounds) || CheckCollisionCircleRec(hitboxBackwardPos, mHitboxRadius, bounds);
}

//Get new car Hitbox pos
Vector2 Car::GetHitboxPos(float carPosX, float carPosY, int hitboxIndex)
{
	//forward hitbox
	if (hitboxIndex == 0)
	{
		return { carPosX, carPosY };
	}
	//backward hitbox
	else if (hitboxIndex == 1)
	{
		return { carPosX + cos(mAngle) * (-mHitboxRadius * 2), carPosY + sin(mAngle) * (-mHitboxRadius * 2)};
	}

	return { carPosX, carPosY };
}
