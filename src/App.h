#ifndef APP_H
#define APP_H

#include "GameState.h"
#include "Tile.h"
#include "SelectionTile.h"

#include <SDL.h>

#include <string>
#include <vector>


//Starts up SDL and creates window
bool init(GameState& gameState);

//Loads media
bool loadMedia(GameState& gameState, Texture& textTexture, Texture& groundTexture, Texture& characterTexture, Texture& towerTexture, Texture& panelSelection, Texture& selectionTile, Texture& enemyTexture, Texture& gem_icon, Texture& iron_icon, Texture& stone_icon, Texture& goblin, Texture& knight, Texture& smallGoblin, Texture& towerBaseArrow, Texture& towerBaseLava, Texture& towerBaseMagic, Texture& stoneRoad, Texture& protagonist, Texture& towersText);

////Frees media and shuts down SDL
//void close();

//Loads individual image
//SDL_Texture* loadTexture(std::string path, GameState& gameState);

//Fill up a vector with the pixel coordinates of images which will act as game floor tiles
bool generateViewportTiles(std::vector<SDL_Rect>& viewports, GameState& gameState);

bool generateTiles(std::vector<std::vector<Tile>>& tiles, GameState& gameState);

#endif // !APP_H
