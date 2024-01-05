#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Texture.h"

#include <SDL.h>
#include <SDL_image.h>

#include <map>
#include <string>

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

	////Ground texture PNG
	//Texture* m_GroundTexture;

	////Character texture PNG
	//Texture* m_CharacterTexture;

	//List of textures used in the game (name of the file, Texture object)
	std::map<std::string, Texture> m_texturesList{};

	GameState(SDL_Window* window, SDL_Renderer* renderer);

	~GameState();
};

#endif // !GAMESTATE_H
