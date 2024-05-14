#include "Bullet.h"

Bullet::Bullet(float x, float y)
	: mX(x), mY(y)
{
	mTexture = LoadTexture("resources/towerDefense_tile249.png");
}
