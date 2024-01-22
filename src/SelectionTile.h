#pragma once
#ifndef SELECTION_TILE_H
#define SELECTION_TILE_H

#include "Texture.h"

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
