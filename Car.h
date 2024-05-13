#pragma once

#include "Environment.h"

class Car
{
public:
	Car(Environment& environment);

	void Init();
	bool Update(float deltaTime);
	void Draw();

	void DrawDebug();

	bool CheckCollisionWith(float carPosX, float carPosY, const Rectangle& bounds);
	Vector2 GetHitboxPos(float carPosX, float carPosY, int hitboxIndex);

	float mX = 640;
	float mY = 360;
private:
	const float mWidth = 60;
	const float mHeight = 30;
	const float mHitboxRadius = mHeight / 2;

	const float mVelocity = 100.0f;
	const float mAccelerationSpeed = 5.0f;
	const float mDeccelerationSpeed = 3.0f;
	const float mMaxSpeed = 200.0f;

	float mAngle = 0;
	float mSpeed = 0;
	float mCurrentSpeedMultiplier = 0.0f;

	int mRound = 1;
	int mMaxRound = 3;

	Texture2D mCarTexture;
	Environment& mEnvironment;
};

