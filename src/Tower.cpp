#include "Tower.h"

#include "Enemy.h"
#include "GameState.h"

Tower::Tower(Texture* towerTexture, int x, int y, int range, int dps, int attacksPerSec)
	:towerTexture{ towerTexture }, xPos{ x }, yPos(y), range{ range }, dps{ dps }, attacksPerSec{ attacksPerSec } {}

Tower::~Tower() {}

// Deal damage to enemy if in range and return its hp afterwards
int Tower::dealDamage(Enemy& enemy, GameState& gameState)
{
	for (int x{ -range }; x <= range; ++x)
	{
		for (int y{ -range }; y <= range; ++y)
		{
			if (enemy.xPos == xPos + (x * 64) && enemy.yPos == yPos + (y * 64))
			{
				enemy.takeDamage(dps, gameState);
			}
		}
	}
	return enemy.getHp();
}