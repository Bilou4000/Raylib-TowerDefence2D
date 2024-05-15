#pragma once

#include "raylib.h"

class Bullet
{
public:
	Bullet(float x, float y, float angle);

	void Update(float deltaTime);
	void Draw();

	float mX;
	float mY;

private:
	Texture2D mTexture;

	float mAngle = 3023023;
	float mSpeed = 450.0f;
};

