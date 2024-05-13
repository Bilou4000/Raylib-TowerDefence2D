#include "GameManager.h"

#include <iostream>

void GameManager::Init()
{
	//initialize environment
    environment.Init();
}

bool GameManager::Update(float deltaTime)
{
	return false;
}

void GameManager::Draw()
{
	//Draw Environment (tiles)
	environment.Draw();
}
