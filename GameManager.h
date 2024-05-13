#pragma once

#include "raylib.h"
#include "Environment.h"

class GameManager
{
public:
	void Init();
	bool Update(float deltaTime);
	void Draw();

private:
	Environment environment {};
};

