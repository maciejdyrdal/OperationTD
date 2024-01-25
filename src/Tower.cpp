#include "Tower.h"

#include "Enemy.h"

Tower::Tower(Texture* towerTexture, int x, int y, int range, int dps, int attacksPerSec)
	:towerTexture{ towerTexture }, xPos{ x }, yPos(y), range{ range }, dps{ dps }, attacksPerSec{ attacksPerSec } {}

Tower::~Tower() {}

// Deals damage to enemy if in range and returns its hp afterwards
int Tower::dealDamage(Enemy& enemy)
{
	int attacksMade{ 0 };
	for (int x{ -range }; x <= range; ++x)
	{
		for (int y{ -range }; y <= range; ++y)
		{
			if (enemy.xPos == xPos + (x * 64) && enemy.yPos == yPos + (y * 64) && attacksMade < attacksPerSec)
			{
				enemy.takeDamage(dps);
				++attacksMade;
			}
		}
	}
	return enemy.getHp();
}