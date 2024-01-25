#ifndef APP_H
#define APP_H

#include "GameState.h"
#include "Tile.h"
#include "SelectionTile.h"

#include <SDL.h>

#include <string>
#include <vector>


// Start up SDL and initialize all game components (window, renderer etc)
bool init(GameState& gameState);

// Absolutely horrendous function that loads all game textures and fonts thanks to the wonders of the SDL2 library
// SDL2 refuses to work with textures that are stored in a runtime-generated data structure (such as a vector)
// The code compiles just fine, but the textures are not displayed on the screen
// Therefore, the loadMedia() function has over 20 arguments with the texture names
// They could be stored in an std::array or C-style array, but our soultion is (arguably) more readable
//  - the textures are referred to by their variable names instead of indexed array elements 
bool loadMedia(GameState& gameState, Texture& textTexture, Texture& groundTexture, Texture& characterTexture, Texture& towerTexture, Texture& panelSelectionTexture, Texture& selectionTile, Texture& enemyTexture, Texture& gemIconTexture, Texture& ironIconTexture, Texture& stoneIconTexture, Texture& goblinTexture, Texture& knightTexture, Texture& smallGoblinTexture, Texture& towerBaseArrowTexture, Texture& towerBaseLavaTexture, Texture& towerBaseMagicTexture, Texture& stoneRoadTexture, Texture& protagonist, Texture& towersText, Texture& bottomTexture, Texture& rightTexture, Texture& heart, Texture& heartIconTexture, Texture& assasinTexture, Texture& menuTexture, Texture& victoryScreen, Texture& failureScreen);

// Create a Viewport object which stores the tile coordinates and sizes
bool generateViewportTiles(std::vector<SDL_Rect>& viewports, GameState& gameState);

// Generate the tiles for the game map
bool generateTiles(std::vector<std::vector<Tile>>& tiles, GameState& gameState);

// Generate the tiles for the selection menu
bool generateSelectionTiles(std::vector<std::vector<SelectionTile>>& Selectiontiles, GameState& gameState);

// Create a Viewport object which stores the selection tile coordinates and sizes
bool generateSelectionViewportTiles(std::vector<SDL_Rect>& viewports, GameState& gameState);

#endif // !APP_H
