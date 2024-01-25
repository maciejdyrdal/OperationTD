#include "Enemy.h"

#include "GameState.h"
#include "Random.h"

Enemy::Enemy(Texture* enemyTexture, int xPos, int yPos, int hp, int timeToMove, int secondsPerMove)
	: enemyTexture{ enemyTexture }, xPos{ xPos }, yPos{ yPos }, hp{ hp }, timeToMove{ timeToMove }, secondsPerMove{ secondsPerMove } 
{
	maxHp = hp;
}

Enemy::~Enemy() {}

// Deals damage to enemy and returns its health afterwards, also handles resource drops 
int Enemy::takeDamage(int damage, GameState& gameState)
{
	// Makes sure the hp doesn't go below 0
	if (damage >= hp && !isDead)
	{
		hp = 0;
		isDead = true;
		
		// Resource drop randomizer
		// Will it drop anything?
		if (Random::get(0, 1) == 1) {

			// Will it drop wood?
			if (Random::get(0, 2) == 1) {
				++gameState.woodAmount;
			}
			// Will it drop stone?
			else if (Random::get(0, 2) == 1){
				++gameState.stoneAmount;
			}
			// Will it drop iron?
			else if (Random::get(0, 1) == 1) {
				++gameState.ironAmount;
			}
			// It will drop a gem
			else {
				++gameState.gemAmount;
			}

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
// Moves to a given position if it is a valid tile
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
