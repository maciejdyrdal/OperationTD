#ifndef PLAYER_H
#define PLAYER_H

#include "GameState.h"
#include "Texture.h"

class Player
{
public:
	Texture* playerTexture;

	int xPos;
	int yPos;

	Player(Texture* playerTexture, int xPos, int yPos);

	~Player();
};

#endif // PLAYER_H