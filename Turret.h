#pragma once

#include "raylib.h"

#include "Environment.h"

class Turret
{
public:
	Turret(float x, float y);

	void Update();
	void Draw();
private:
	float mX;
	float mY;

	Texture2D mTexture;
	Environment mEnvironment{};
};

