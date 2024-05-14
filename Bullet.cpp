#include "Bullet.h"

#include "raymath.h"
#include <iostream>
#include <cmath>

Bullet::Bullet(float x, float y, float angle)
	: mX(x), mY(y), mAngle(angle)
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
}

void Bullet::Draw()
{
	Rectangle source{ 0, 0, mTexture.width, mTexture.height };
	Rectangle dest{ mX, mY, mTexture.width / 2.0f, mTexture.height / 2.0f };
	Vector2 origin{ dest.width / 2, dest.height / 2 };

	DrawTexturePro(mTexture, source, dest, origin, mAngle * RAD2DEG, WHITE);
}
