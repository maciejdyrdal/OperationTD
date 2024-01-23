#ifndef TOWER_H
#define TOWER_H

#include "Enemy.h"
#include "Texture.h"

class Tower
{
public:
	Tower(Texture* towerTexture, int x, int y);

	~Tower();

	Texture* towerTexture;

	int xPos;
	int yPos;

	int range{ 2 };
	int dps{ 7 };

	int dealDamage(Enemy& enemy);
};

#endif // !TOWER_H