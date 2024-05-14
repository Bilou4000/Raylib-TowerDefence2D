#pragma once

#include "raylib.h"

class Bullet
{
public:
	Bullet(float x, float y);

	void Update(float deltaTime);
	void Draw();

	float mX;
	float mY;

private:
	Texture2D mTexture;
};

