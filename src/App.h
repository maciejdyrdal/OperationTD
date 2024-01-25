#ifndef APP_H
#define APP_H

#include "GameState.h"
#include "Tile.h"
#include "SelectionTile.h"

#include <SDL.h>

#include <string>
#include <vector>


// Start up SDL and create window
bool init(GameState& gameState);

// Load media (textures, fonts)
bool loadMedia(GameState& gameState, Texture& textTexture, Texture& groundTexture, Texture& characterTexture, Texture& towerTexture, Texture& panelSelectionTexture, Texture& selectionTile, Texture& enemyTexture, Texture& gemIconTexture, Texture& ironIconTexture, Texture& stoneIconTexture, Texture& goblinTexture, Texture& knightTexture, Texture& smallGoblinTexture, Texture& towerBaseArrowTexture, Texture& towerBaseLavaTexture, Texture& towerBaseMagicTexture, Texture& stoneRoadTexture, Texture& protagonist, Texture& towersText, Texture& bottomTexture, Texture& rightTexture, Texture& heart, Texture& heartIconTexture, Texture& assasinTexture);

// Fill up a vector with the pixel coordinates of images which will act as game floor tiles
bool generateViewportTiles(std::vector<SDL_Rect>& viewports, GameState& gameState);

// 
bool generateTiles(std::vector<std::vector<Tile>>& tiles, GameState& gameState);

#endif // !APP_H
