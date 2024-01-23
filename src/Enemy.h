#ifndef ENEMY_H
#define ENEMY_H

#include "Texture.h"

#include "GameState.h"

class Enemy
{
public:
	Texture* enemyTexture;

	int xPos;
	int yPos;

	Enemy(Texture* enemyTexture, int xPos, int yPos, int hp, int timeToMove);

	~Enemy();

	// Deals damage to enemy and returns its health afterwards
	int takeDamage(int damage);

	int getHp();

	bool move(int x, int y, GameState& gameState);

	int moveCount{ 0 };

	int timeToMove;

	bool isDead{ false };
private:
	int hp;

};

#endif // !ENEMY_H
