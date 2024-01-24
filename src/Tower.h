#ifndef TOWER_H
#define TOWER_H

#include "Enemy.h"
#include "Texture.h"

class Tower
{
public:
	Tower(Texture* towerTexture, int x, int y, int range, int dps);

	~Tower();

	Texture* towerTexture;

	int xPos;
	int yPos;

	int range;
	int dps;

	int dealDamage(Enemy& enemy);
};

#endif // !TOWER_H
