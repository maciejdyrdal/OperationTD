#include "Enemy.h"

#include "GameState.h"

Enemy::Enemy(Texture* enemyTexture, int xPos, int yPos, int hp)
	: enemyTexture{enemyTexture}, xPos{xPos}, yPos{yPos}, hp{hp} {}

Enemy::~Enemy() {}

int Enemy::takeDamage(int damage)
{
	if (damage >= hp)
	{
		hp = 0;
	}
	else
	{
		hp -= damage;
	}

	return hp;
}

int Enemy::getHp()
{
	return hp;
}

bool Enemy::move(int x, int y, GameState& gameState)
{
	bool movedSuccessfully{ false };

	if (0 <= x / 64 <= gameState.m_SCREEN_WIDTH_TILE_COUNT && 0 <= y / 64 <= gameState.m_SCREEN_HEIGHT_TILE_COUNT)
	{
		xPos = x;
		yPos = y;
		movedSuccessfully = true;
	}

	return movedSuccessfully;
}