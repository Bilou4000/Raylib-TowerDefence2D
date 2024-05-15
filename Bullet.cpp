#include "Bullet.h"

#include "raymath.h"
#include <iostream>
#include <cmath>

#include "GameManager.h"

Bullet::Bullet(GameManager* gameManager, float x, float y, float angle)
	: mGameManager(gameManager), mX(x), mY(y), mAngle(angle)
{
	mTexture = LoadTexture("resources/towerDefense_tile272.png");
}

void Bullet::Update(float deltaTime)
{
	//Moving forward
	float x = mX + cosf(mAngle) * mSpeed * deltaTime;
	float y = mY + sinf(mAngle) * mSpeed * deltaTime;

	mX = x;
	mY = y;

	//std::vector<std::shared_ptr<Enemy>>& allEnemies = mGameManager->GetAllEnemies();

	//for (int enemy = 0; enemy < allEnemies.size(); enemy++)
	//{
	//	if (allEnemies[enemy] != nullptr &&
	//		CheckCollisionCircles({ mX, mY }, 8, { allEnemies[enemy]->mX, allEnemies[enemy]->mY }, 20))
	//	{
	//		allEnemies[enemy].reset();
	//	}
	//}
}

void Bullet::Draw()
{
	Rectangle source{ 0, 0, mTexture.width, mTexture.height };
	Rectangle dest{ mX, mY, mTexture.width / 2.0f, mTexture.height / 2.0f };
	Vector2 origin{ dest.width / 2, dest.height / 2 };

	DrawTexturePro(mTexture, source, dest, origin, mAngle * RAD2DEG, WHITE);

	//debug
	//DrawCircleLines(mX, mY, 8, RED);
}
