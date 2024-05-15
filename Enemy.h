#pragma once

#include "raylib.h"
#include "Environment.h"

class Enemy
{
public:
	Enemy(Environment& environment, std::vector<Vector2> path, float x, float y, float lives);

	void Update(float deltaTime);
	void Draw();

	void DrawDebug();
	bool GetIfAtCaslte();

	float mX = 0;
	float mY = 0;
	int mLives = 3;

private:
	const float mWidth = 128;
	const float mHeight = 128;

	const float mMaxSpeed = 400.0f; //100
	const float mMinDistance = 5.0f;

	float mSpeed = 0;
	float mAngle = 0;
	bool mIsAtCastle = false;

	Texture2D mTexture;
	Environment& mEnvironment;

	std::vector<Vector2> mPath;
	int mPathIndex = 0;
};

