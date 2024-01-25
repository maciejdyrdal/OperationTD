#ifndef PLAYER_H
#define PLAYER_H

#include "GameState.h"
#include "Texture.h"

// Player class containing its position and texture
class Player
{
public:
	Texture* playerTexture;

	int xPos;
	int yPos;

	// Number of attacks player can perform during the game
	int playerAttacksLeft{ 10 };

	// Amount of damage player deals to enemies
	int playerDamage{ 10 };

	Player(Texture* playerTexture, int xPos, int yPos);

	~Player();
};

#endif // PLAYER_H