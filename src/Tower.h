#ifndef TOWER_H
#define TOWER_H

#include "Enemy.h"
#include "Texture.h"
#include "GameState.h"

// Tower class containing its texture, position, damage radius, damage per second and number of attacks performed each second
class Tower
{
public:
	Tower(Texture* towerTexture, int x, int y, int range, int dps, int attacksPerSec);

	~Tower();

	Texture* towerTexture;

	int xPos;
	int yPos;

	int range;
	int dps;
	int attacksPerSec;

	// Deal damage to enemy if in range and return its hp afterwards
	int dealDamage(Enemy& enemy, GameState& gameState);
};

#endif // !TOWER_H
