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
#include <vector>
#include <tuple>

class GameState
{
public:
	//Screen dimension constants
	const int m_TILE_SIDE_LENGTH = 64;
	const int m_SCREEN_WIDTH_TILE_COUNT = 15;
	const int m_SCREEN_WIDTH = m_TILE_SIDE_LENGTH * m_SCREEN_WIDTH_TILE_COUNT;
	const int m_SCREEN_HEIGHT_TILE_COUNT = 10;
	const int m_SCREEN_HEIGHT = m_TILE_SIDE_LENGTH * m_SCREEN_HEIGHT_TILE_COUNT;


	const int s_PANEL_TILE_SIDE_LENGTH = 64;
	const int s_SCREEN_WIDTH_PANEL_COUNT = 2;
	const int s_SCREEN_PANEL_WIDTH = s_PANEL_TILE_SIDE_LENGTH * s_SCREEN_WIDTH_PANEL_COUNT;
	const int s_SCREEN_HEIGHT_PANEL_COUNT = 5;
	const int s_SCREEN_PANEL_HEIGHT = s_PANEL_TILE_SIDE_LENGTH * s_SCREEN_HEIGHT_PANEL_COUNT;

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
	std::stringstream s_WoodAmountText;

	const std::array<std::string, 21> m_textureFilenames{ "img/ground.png", "img/character.png", "img/tower.png", "img/panelSelection.png", "img/selectionTile.png", "img/enemy.png", "img/gem_icon.png", "img/iron_icon.png", "img/stone_icon.png", "img/goblin.png", "img/knight.png", "img/smallGoblin.png", "img/towerBaseArrow.png", "img/towerBaseLava.png", "img/towerBaseMagic.png", "img/stoneRoad.png", "img/protagonist.png", "img/towersText.png", "img/upgradesText.png", "img/upgradeSword.png", "img/wood_icon.png"};
	int enemyCount{ 5 };
	
	int woodAmount = 0;
	int stoneAmount = 0;
	int gemAmount = 0;
	int ironAmount = 0;

	std::vector<std::tuple<int, int>> enemyPath{ {14, 5}, {13, 5}, {12, 5}, {12, 4}, {12, 3}, {11, 3}, {10, 3}, {10, 4}, {10, 5}, {10, 6}, {10, 7} };

	GameState(SDL_Window* window, SDL_Renderer* renderer);

	~GameState();
};

#endif // !GAMESTATE_H
