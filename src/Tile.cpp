#include "Tile.h"

Tile::Tile(int xPos, int yPos)
	:hasBuilding{ false }, tileTexture{ NULL }, xPos{ xPos }, yPos{ yPos } {}

Tile::~Tile() {}