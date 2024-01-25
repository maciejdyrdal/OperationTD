#ifndef TILE_H
#define TILE_H

#include "Texture.h"

// Class containing information on a game tile 
class Tile
{
public:
	Texture* tileTexture;

	bool hasBuilding;

	int xPos;
	int yPos;

	Tile(int xPos, int yPos);
	
	~Tile();
};

#endif // !TILE_H
