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

	Enemy(Texture* playerTexture, int xPos, int yPos, int hp);

	~Enemy();

	// Deals damage to enemy and returns its health afterwards
	int takeDamage(int damage);

	int getHp();

	bool move(int x, int y, GameState& gameState);

private:
	int hp;

};

#endif // !ENEMY_H
