#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Texture.h"

#include "Timer.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <array>
#include <map>
#include <string>
#include <sstream>

class GameState
{
public:
	//Screen dimension constants
	const int m_TILE_SIDE_LENGTH = 64;
	const int m_SCREEN_WIDTH_TILE_COUNT = 9;
	const int m_SCREEN_WIDTH = m_TILE_SIDE_LENGTH * m_SCREEN_WIDTH_TILE_COUNT;
	const int m_SCREEN_HEIGHT_TILE_COUNT = 7;
	const int m_SCREEN_HEIGHT = m_TILE_SIDE_LENGTH * m_SCREEN_HEIGHT_TILE_COUNT;

	//The window we'll be rendering to
	SDL_Window* m_Window = NULL;

	//The window renderer
	SDL_Renderer* m_Renderer = NULL;

	//Globally used font
	TTF_Font* m_Font = NULL;

	int m_FontSize = 18;

	//The application timer
	Timer m_Timer;

	//In memory text stream
	std::stringstream m_TimeText;

	int enemyCount{ 5 };

	const std::array<std::string, 4> m_textureFilenames{ "img/ground.png", "img/character.png", "img/tower.png", "img/enemy.png" };

	GameState(SDL_Window* window, SDL_Renderer* renderer);

	~GameState();
};

#endif // !GAMESTATE_H
