#pragma once
#ifndef SELECTION_TILE_H
#define SELECTION_TILE_H

#include "Texture.h"

// Class containing information on a tile in the selection menu
class SelectionTile
{
public:
	Texture* selectionTileTexture;

	int xPos;
	int yPos;

	SelectionTile(int xPos, int yPos);

	~SelectionTile();
};

#endif // !TILE_H
