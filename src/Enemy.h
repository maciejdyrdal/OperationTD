#ifndef ENEMY_H
#define ENEMY_H

#include "Texture.h"

#include "GameState.h"

// Enemy class containing its texture, position, hp etc
class Enemy
{
public:
	Texture* enemyTexture;

	int xPos;
	int yPos;

	Enemy(Texture* enemyTexture, int xPos, int yPos, int hp, int timeToMove, int secondsPerMove);

	~Enemy();

	int takeDamage(int damage, GameState& gameState);

	int getHp();

	// Moves to a given position if it is a valid tile
	bool move(int x, int y, GameState& gameState);

	int moveCount{ 0 };

	int timeToMove;

	bool isDead{ false };

	int secondsPerMove;
private:
	int hp;

	int maxHp;
};

#endif // !ENEMY_H
