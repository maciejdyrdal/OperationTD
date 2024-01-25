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
	// Game screen dimension constants
	const int m_TILE_SIDE_LENGTH = 64;
	const int m_SCREEN_WIDTH_TILE_COUNT = 15;
	const int m_SCREEN_WIDTH = m_TILE_SIDE_LENGTH * m_SCREEN_WIDTH_TILE_COUNT;
	const int m_SCREEN_HEIGHT_TILE_COUNT = 10;
	const int m_SCREEN_HEIGHT = m_TILE_SIDE_LENGTH * m_SCREEN_HEIGHT_TILE_COUNT;

	// Selector panel dimension constants
	const int s_PANEL_TILE_SIDE_LENGTH = 64;
	const int s_SCREEN_WIDTH_PANEL_COUNT = 2;
	const int s_SCREEN_PANEL_WIDTH = s_PANEL_TILE_SIDE_LENGTH * s_SCREEN_WIDTH_PANEL_COUNT;
	const int s_SCREEN_HEIGHT_PANEL_COUNT = 5;
	const int s_SCREEN_PANEL_HEIGHT = s_PANEL_TILE_SIDE_LENGTH * s_SCREEN_HEIGHT_PANEL_COUNT;

	// The window we'll be rendering to
	SDL_Window* m_Window = NULL;

	// The window renderer
	SDL_Renderer* m_Renderer = NULL;

	// Globally used font
	TTF_Font* m_Font = NULL;
	int m_FontSize = 18;

	// The application timer
	Timer m_Timer;

	// In memory text stream
	std::stringstream m_TimeText;
	std::stringstream s_WoodAmountText;

	// Array containing the filenames of textures to be loaded
	const std::array<std::string, 25> m_textureFilenames{ "img/ground.png", "img/character.png", "img/tower.png", "img/panelSelection.png", "img/selectionTile.png", "img/enemy.png", "img/gem_icon.png", "img/iron_icon.png", "img/stone_icon.png", "img/goblin.png", "img/knight.png", "img/smallGoblin.png", "img/towerBaseArrow.png", "img/towerBaseLava.png", "img/towerBaseMagic.png", "img/stoneRoad.png", "img/protagonist.png", "img/towersText.png", "img/upgradesText.png", "img/upgradeSword.png", "img/wood_icon.png", "img/bottomTexture.png", "img/rightTexture.png", "img/heart.png", "img/heart_icon.png"};
	int enemyCount{ 5 };
	
	// Starting amounts of building resources 
	int woodAmount = 300;
	int stoneAmount = 150;
	int gemAmount = 90;
	int ironAmount = 50;

	// Resource costs of each tower
	std::tuple<int, int, int, int> arrowTowerCost{ 200, 50, 0, 20 };
	std::tuple<int, int, int, int> lavaTowerCost{ 100, 200, 20, 100 };
	std::tuple<int, int, int, int> magicTowerCost{ 100, 100, 100, 100 };

	// Hit points which get reduces whenever an enemy reaches the end tile; lowering this value to 0 means the player has lost the game
	int health = 10;

	// Predetermined path for enemies to follow
	std::vector<std::tuple<int, int>> enemyPath{ {14, 5}, {13, 5}, {12, 5}, {12, 4}, {12, 3}, {11, 3}, {10, 3}, {10, 4}, {10, 5}, {10, 6}, {10, 7} };
	
	// Separate variable which stores the location of the end tile
	std::tuple<int, int> heartLocation{ std::get<0>(enemyPath[enemyPath.size()-1]),  std::get<1>(enemyPath[enemyPath.size() - 1]) };

	GameState(SDL_Window* window, SDL_Renderer* renderer);

	~GameState();
};

#endif // !GAMESTATE_H
