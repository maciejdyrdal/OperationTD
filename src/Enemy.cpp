#include "Enemy.h"

#include "GameState.h"
#include "Random.h"

Enemy::Enemy(Texture* enemyTexture, int xPos, int yPos, int hp, int timeToMove)
	: enemyTexture{ enemyTexture }, xPos{ xPos }, yPos{ yPos }, hp{ hp }, timeToMove{ timeToMove } 
{
	maxHp = hp;
}

Enemy::~Enemy() {}

int Enemy::takeDamage(int damage, GameState& gameState)
{
	if (damage >= hp && !isDead)
	{
		hp = 0;
		isDead = true;
		if (maxHp >= 10)
		{
			gameState.woodAmount += Random::get(maxHp - 10, maxHp + 10);
			gameState.stoneAmount += Random::get(maxHp - 10, maxHp + 10);
			gameState.gemAmount += Random::get(maxHp - 10, maxHp + 10);
			gameState.ironAmount += Random::get(maxHp - 10, maxHp + 10);
		}
		else
		{
			gameState.woodAmount += Random::get(0, maxHp + 10);
			gameState.stoneAmount += Random::get(0, maxHp + 10);
			gameState.gemAmount += Random::get(0, maxHp + 10);
			gameState.ironAmount += Random::get(0, maxHp + 10);
		}
		
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

	if (0 <= x / 64 && x / 64 <= gameState.m_SCREEN_WIDTH_TILE_COUNT && 0 <= y / 64 && y / 64 <= gameState.m_SCREEN_HEIGHT_TILE_COUNT)
	{
		xPos = x;
		yPos = y;
		movedSuccessfully = true;
	}

	return movedSuccessfully;
}
