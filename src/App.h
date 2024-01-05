#ifndef APP_H
#define APP_H

#include "GameState.h"

#include <SDL.h>

#include <string>
#include <vector>


//Starts up SDL and creates window
bool init(GameState& gameState);

//Loads media
bool loadMedia(GameState& gameState);

////Frees media and shuts down SDL
//void close();

//Loads individual image
SDL_Texture* loadTexture(std::string path, GameState& gameState);

//Fill up a vector with the pixel coordinates of images which will act as game floor tiles
bool generateViewportTiles(std::vector<SDL_Rect>& viewports, GameState& gameState);

#endif // !APP_H

