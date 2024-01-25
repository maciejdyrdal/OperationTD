#include "App.h"

#include "Texture.h"
#include "GameState.h"
#include "Player.h"
#include "Tile.h"
#include "SelectionTile.h"
#include "Enemy.h"
#include "Tower.h"

#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <array>
#include <iostream>
#include <sstream>
#include <tuple>


bool init(GameState& gameState)
{
	// Initialization flag
	bool successfullyInitialized{ true };

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		PLOG_ERROR << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
		successfullyInitialized = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			PLOG_WARNING << "Warning: Linear texture filtering not enabled!";
		}

		// Create window
		gameState.m_Window = SDL_CreateWindow("OperationTD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gameState.m_SCREEN_WIDTH + gameState.s_SCREEN_PANEL_WIDTH, gameState.m_SCREEN_HEIGHT + 50, SDL_WINDOW_SHOWN);
		if (gameState.m_Window == NULL)
		{
			PLOG_ERROR << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
			successfullyInitialized = false;
		}
		else
		{
			// Create renderer for window
			gameState.m_Renderer = SDL_CreateRenderer(gameState.m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gameState.m_Renderer == NULL)
			{
				PLOG_ERROR << "Renderer could not be created! SDL Error: " << SDL_GetError() << '\n';
				successfullyInitialized = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(gameState.m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					PLOG_ERROR << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << '\n';
					successfullyInitialized = false;
				}

				// Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					PLOG_ERROR << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << '\n';
					successfullyInitialized = false;
				}
			}
		}
	}
	PLOG_INFO << "Successfully initialized.";
	return successfullyInitialized;
}

// Absolutely horrendous function that loads all game textures and fonts thanks to the wonders of the SDL2 library
// SDL2 refuses to work with textures that are stored in a runtime-generated data structure (such as a vector)
// The code compiles just fine, but the textures are not displayed on the screen
// Therefore, the loadMedia() function has over 20 arguments with the texture names
// They could be stored in an std::array or C-style array, but our soultion is (arguably) more readable
//  - the textures are referred to by their variable names instead of indexed array elements 
// Lord have mercy upon us
bool loadMedia(GameState& gameState, Texture& textTexture, Texture& groundTexture, Texture& characterTexture, Texture& towerTexture, Texture& panelSelectionTexture, Texture& selectionTile, Texture& enemyTexture, Texture& gemIconTexture, Texture& ironIconTexture, Texture& stoneIconTexture, Texture& goblin, Texture& knight, Texture& smallGoblin, Texture& towerBaseArrowTexture, Texture& towerBaseLavaTexture, Texture& towerBaseMagicTexture, Texture& stoneRoadTexture, Texture& protagonist, Texture& towersText, Texture& upgradesText, Texture& upgradeSwordTexture, Texture& woodIconTexture, Texture& bottomTexture, Texture& rightTexture, Texture& heart, Texture& heartIconTexture, Texture& assasinTexture)
{
	//Loading success flag
	bool successfullyLoaded = true;

	if (!groundTexture.loadFromFile(gameState.m_textureFilenames[0], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[0] << "!\n";
		successfullyLoaded = false;
	}
	if (!characterTexture.loadFromFile(gameState.m_textureFilenames[1], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[1] << "!\n";
		successfullyLoaded = false;
	}
	if (!towerTexture.loadFromFile(gameState.m_textureFilenames[2], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[2] << "!\n";
		successfullyLoaded = false;
	}
	if (!panelSelectionTexture.loadFromFile(gameState.m_textureFilenames[3], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[3] << "!\n";
		successfullyLoaded = false;
	}

	if (!selectionTile.loadFromFile(gameState.m_textureFilenames[4], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[4] << "!\n";
		successfullyLoaded = false;
	}

	gameState.m_Font = TTF_OpenFont("fonts/munro.ttf", gameState.m_FontSize);
	if (gameState.m_Font == NULL)
	{
		PLOG_ERROR << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << '\n';
		successfullyLoaded = false;
	}
	if (!enemyTexture.loadFromFile(gameState.m_textureFilenames[5], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[5] << "!\n";
		successfullyLoaded = false;
	}

	if (!gemIconTexture.loadFromFile(gameState.m_textureFilenames[6], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[6] << "!\n";
		successfullyLoaded = false;
	}

	if (!ironIconTexture.loadFromFile(gameState.m_textureFilenames[7], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[7] << "!\n";
		successfullyLoaded = false;
	}

	if (!stoneIconTexture.loadFromFile(gameState.m_textureFilenames[8], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[8] << "!\n";
		successfullyLoaded = false;
	}

	if (!goblin.loadFromFile(gameState.m_textureFilenames[9], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[9] << "!\n";
		successfullyLoaded = false;
	}

	if (!knight.loadFromFile(gameState.m_textureFilenames[10], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[10] << "!\n";
		successfullyLoaded = false;
	}

	if (!smallGoblin.loadFromFile(gameState.m_textureFilenames[11], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[11] << "!\n";
		successfullyLoaded = false;
	}

	if (!towerBaseArrowTexture.loadFromFile(gameState.m_textureFilenames[12], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[12] << "!\n";
		successfullyLoaded = false;
	}

	if (!towerBaseLavaTexture.loadFromFile(gameState.m_textureFilenames[13], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[13] << "!\n";
		successfullyLoaded = false;
	}

	if (!towerBaseMagicTexture.loadFromFile(gameState.m_textureFilenames[14], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[14] << "!\n";
		successfullyLoaded = false;
	}

	if (!stoneRoadTexture.loadFromFile(gameState.m_textureFilenames[15], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[15] << "!\n";
		successfullyLoaded = false;
	}

	if (!protagonist.loadFromFile(gameState.m_textureFilenames[16], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[16] << "!\n";
		successfullyLoaded = false;
	}

	if (!towersText.loadFromFile(gameState.m_textureFilenames[17], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[17] << "!\n";
		successfullyLoaded = false;
	}

	if (!upgradesText.loadFromFile(gameState.m_textureFilenames[18], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[18] << "!\n";
		successfullyLoaded = false;
	}

	if (!upgradeSwordTexture.loadFromFile(gameState.m_textureFilenames[19], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[19] << "!\n";
		successfullyLoaded = false;
	}

	if (!woodIconTexture.loadFromFile(gameState.m_textureFilenames[20], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[20] << "!\n";
		successfullyLoaded = false;
	}

	if (!bottomTexture.loadFromFile(gameState.m_textureFilenames[21], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[21] << "!\n";
		successfullyLoaded = false;
	}

	if (!rightTexture.loadFromFile(gameState.m_textureFilenames[22], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[22] << "!\n";
		successfullyLoaded = false;
	}

	if (!heart.loadFromFile(gameState.m_textureFilenames[23], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[23] << "!\n";
		successfullyLoaded = false;
	}

	if (!heartIconTexture.loadFromFile(gameState.m_textureFilenames[24], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[24] << "!\n";
		successfullyLoaded = false;
	}

	if (!assasinTexture.loadFromFile(gameState.m_textureFilenames[25], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[25] << "!\n";
		successfullyLoaded = false;
	}

	PLOG_INFO << "Successfiully loaded media.";
	return successfullyLoaded;
}

// Generate the tiles for the game map
bool generateTiles(std::vector<std::vector<Tile>>& tiles, GameState& gameState)
{
	bool successfullyGenerated{ false };

	for (int x{ 0 }; x < gameState.m_SCREEN_WIDTH_TILE_COUNT; ++x)
	{
		std::vector<Tile> tempVector{};
		for (int y{ 0 }; y < gameState.m_SCREEN_HEIGHT_TILE_COUNT; ++y)
		{
			tempVector.push_back(Tile{x * gameState.m_TILE_SIDE_LENGTH, y * gameState.m_TILE_SIDE_LENGTH});
		}
		tiles.push_back(tempVector);
	}

	successfullyGenerated = true;
	return successfullyGenerated;
}

// Create a Viewport object which stores the tile coordinates and sizes
bool generateViewportTiles(std::vector<SDL_Rect>& viewports, GameState& gameState)
{
	bool successfullyGenerated{ false };

	for (int x{ 0 }; x < gameState.m_SCREEN_WIDTH_TILE_COUNT; ++x)
	{
		for (int y{ 0 }; y < gameState.m_SCREEN_HEIGHT_TILE_COUNT; ++y)
		{
			viewports.push_back({ x * gameState.m_TILE_SIDE_LENGTH, y * gameState.m_TILE_SIDE_LENGTH, gameState.m_TILE_SIDE_LENGTH, gameState.m_TILE_SIDE_LENGTH });
		}
	}

	successfullyGenerated = true;
	return successfullyGenerated;
}

// Generate the tiles for the selection menu
bool generateSelectionTiles(std::vector<std::vector<SelectionTile>>& Selectiontiles, GameState& gameState)
{
	bool successfullyGenerated{ false };

	for (int x{ gameState.m_SCREEN_WIDTH_TILE_COUNT }; x < gameState.m_SCREEN_WIDTH_TILE_COUNT + gameState.s_SCREEN_WIDTH_PANEL_COUNT; ++x)
	{
		std::vector<SelectionTile> tempVector{};
		for (int y{ 0 }; y < gameState.s_SCREEN_HEIGHT_PANEL_COUNT; ++y)
		{
			tempVector.push_back(SelectionTile{ x * gameState.s_PANEL_TILE_SIDE_LENGTH, y * gameState.s_PANEL_TILE_SIDE_LENGTH });
		}
		Selectiontiles.push_back(tempVector);
	}

	successfullyGenerated = true;
	return successfullyGenerated;
}

// Create a Viewport object which stores the selection tile coordinates and sizes
bool generateSelectionViewportTiles(std::vector<SDL_Rect>& viewports, GameState& gameState)
{
	bool successfullyGenerated{ false };

	for (int x{ gameState.m_SCREEN_WIDTH_TILE_COUNT }; x < gameState.m_SCREEN_WIDTH_TILE_COUNT + gameState.s_SCREEN_WIDTH_PANEL_COUNT; ++x)
	{
		for (int y{ 0 }; y < gameState.s_SCREEN_HEIGHT_PANEL_COUNT; ++y)
		{
			viewports.push_back({ x * gameState.s_PANEL_TILE_SIDE_LENGTH, y * gameState.s_PANEL_TILE_SIDE_LENGTH, gameState.s_PANEL_TILE_SIDE_LENGTH, gameState.s_PANEL_TILE_SIDE_LENGTH });
		}
	}

	successfullyGenerated = true;
	return successfullyGenerated;
}




int main(int argc, char* args[])
{
	// Initialize the logger (both to the text file and the console)
	static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
	plog::init(plog::debug, "log.txt").addAppender(&consoleAppender);

	PLOG_INFO << "Starting app...";

	// Create pointers to objects representing the window, renderer and textures which will be passed to functions along the whole app's life
	SDL_Window* window{ NULL };
	SDL_Renderer* renderer{ NULL };

	// Initialize the gameState object which holds pointers to various app components and constants (such as window size)
	GameState gameState{ window, renderer };

	// Start up SDL and create window
	if (!init(gameState))
	{
		PLOG_ERROR << "Failed to initialize!\n";
	}
	else
	{
		// Initialize the texture objects

		// Old textures (deprecated)
		Texture groundTexture{};
		Texture characterTexture{};
		Texture towerTexture{};
		Texture enemyTexture{};
		
		// Selection UI textures
		Texture panelSelectionTexture{};
		Texture bottomTexture{};
		Texture rightTexture{};
		Texture selectionTile{};
		Texture upgradeSwordTexture{};

		// Player character texture
		Texture protagonistTexture{};

		// Icon textures
		Texture heartIconTexture{};
		Texture woodIconTexture{};
		Texture gemIconTexture{};
		Texture ironIconTexture{};
		Texture stoneIconTexture{};
		
		// Road textures
		Texture stoneRoadTexture{};
		Texture heartRoadTexture{};

		// Enemy textures
		Texture assasinTexture{};
		Texture goblinTexture{};
		Texture knightTexture{};
		Texture smallGoblinTexture{};

		// Tower textures
		Texture towerBaseArrowTexture{};
		Texture towerBaseLavaTexture{};
		Texture towerBaseMagicTexture{};

		// Text textures
		Texture towersText{};
		Texture uprgadesText{};
		Texture textTexture{};
		Texture timeTextTexture{};
		Texture woodTextTexture{};
		Texture stoneTextTexture{};
		Texture ironTextTexture{};
		Texture gemTextTexture{};
		Texture heartTextTexture{};
		Texture woodCostAmountTexture{};
		Texture stoneCostAmountTexture{};
		Texture ironCostAmountTexture{};
		Texture gemCostAmountTexture{};


		// Initialize the texture pointers for the player character, enemies and towers
		Texture* protagonistTexturePtr{ &protagonistTexture };
		Texture* enemyTexturePtr{ &enemyTexture };

		Texture* assasinTexturePtr{ &assasinTexture };
		Texture* goblinTexturePtr{ &goblinTexture };
		Texture* smallGoblinTexturePtr{ &smallGoblinTexture };
		Texture* knightTexturePtr{ &knightTexture };


		Texture* panelSelectionPtr{ &panelSelectionTexture };
		Texture* towerBaseArrowPtr{ &towerBaseArrowTexture };
		Texture* towerBaseLavaPtr{ &towerBaseLavaTexture };
		Texture* towerBaseMagicPtr{ &towerBaseMagicTexture };

		Texture* panelSelectionTexturePtr{ &panelSelectionTexture };
		Texture* towerBaseArrowTexturePtr{ &towerBaseArrowTexture };
		Texture* towerBaseLavaTexturePtr{ &towerBaseLavaTexture };
		Texture* towerBaseMagicTexturePtr{ &towerBaseMagicTexture };


		// Create the player object
		Player player{ protagonistTexturePtr, gameState.m_TILE_SIDE_LENGTH * 3, gameState.m_TILE_SIDE_LENGTH * 4 };

		// Create the vector containing enemies
		
		//assasinTexturePtr
		//goblinTexturePtr
		//smallGoblinTexturePtr
		//knightTexturePtr



		std::vector<Enemy> enemies;
		for (int i{ 0 }; i < gameState.enemyCount; ++i)
		{
			enemies.push_back(Enemy(smallGoblinTexturePtr, ((gameState.m_SCREEN_WIDTH_TILE_COUNT + 10) * gameState.m_TILE_SIDE_LENGTH), 0, 20, 2 * i + 2, 2));
		}

		// Create the vector containing placed towers
		std::vector<Tower> towers;


		// Create tower object templates
		//Tower tempArrowTower{ towerBaseArrowTexturePtr, 0, 0, 3, 2, 3 };
		//Tower tempLavaTower{ towerBaseLavaTexturePtr, 0, 0, 1, 10, 8 };
		//Tower tempMagicTower{ towerBaseMagicTexturePtr, 0, 0, 2, 5, 5 };


		//Player select{ panelSelectionTexturePtr, gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH, 0 };
		Player select{ panelSelectionTexturePtr, gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT,  gameState.s_PANEL_TILE_SIDE_LENGTH };

		std::vector<std::vector<Tile>> buildingTiles{};
		generateTiles(buildingTiles, gameState);

		//selection vector
		std::vector<std::vector<SelectionTile>> selections{};
		generateSelectionTiles(selections, gameState);

		//Load media
		if (!loadMedia(gameState, textTexture, groundTexture, characterTexture, towerTexture, panelSelectionTexture, selectionTile, enemyTexture, gemIconTexture, ironIconTexture, stoneIconTexture, goblinTexture, knightTexture, smallGoblinTexture, towerBaseArrowTexture, towerBaseLavaTexture, towerBaseMagicTexture, stoneRoadTexture, protagonistTexture, towersText, uprgadesText, upgradeSwordTexture, woodIconTexture, bottomTexture, rightTexture, heartRoadTexture, heartIconTexture, assasinTexture))
		{
			PLOG_ERROR << "Failed to load media!\n";
		}
		else
		{
			// Main loop flag
			bool quit{ false };

			//Event handler
			SDL_Event e;

			//Set text color as white
			SDL_Color textColor = { 255, 255, 255, 255 };

			gameState.m_Timer.start();

			int attacksMade{ 0 };

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						int xPosTemp{ player.xPos };
						int yPosTemp{ player.yPos };


						switch (e.key.keysym.sym)
						{
						//protagonist movement & actions
						case SDLK_w:
							player.yPos = std::max(player.yPos - gameState.m_TILE_SIDE_LENGTH, 0);
							break;
						case SDLK_s:
							player.yPos = std::min(player.yPos + gameState.m_TILE_SIDE_LENGTH, gameState.m_SCREEN_HEIGHT - gameState.m_TILE_SIDE_LENGTH);
							break;
						case SDLK_a:
							player.xPos = std::max(player.xPos - gameState.m_TILE_SIDE_LENGTH, 0);
							break;
						case SDLK_d:
							player.xPos = std::min(player.xPos + gameState.m_TILE_SIDE_LENGTH, gameState.m_SCREEN_WIDTH - gameState.m_TILE_SIDE_LENGTH);
							break;

						case SDLK_SPACE:
							//buildingTiles[player.xPos / 64][player.yPos / 64].tileTexture = &towerTexture;

							/*tempTower.xPos = player.xPos;
							tempTower.yPos = player.yPos;

							towers.push_back(tempTower);

							buildingTiles[player.xPos / 64][player.yPos / 64].hasBuilding = true;*/
							break;

						//selection "movement" & action
						case SDLK_UP:
							if (select.yPos - gameState.s_PANEL_TILE_SIDE_LENGTH == 3 * gameState.s_PANEL_TILE_SIDE_LENGTH) {
								select.yPos = select.yPos - 2 * gameState.s_PANEL_TILE_SIDE_LENGTH;
							}
							else {
								select.yPos = std::max(select.yPos - gameState.s_PANEL_TILE_SIDE_LENGTH, gameState.s_PANEL_TILE_SIDE_LENGTH);

							}
							break;
						case SDLK_DOWN:
							if (select.yPos + gameState.s_PANEL_TILE_SIDE_LENGTH == 3 * gameState.s_PANEL_TILE_SIDE_LENGTH) {
								select.yPos = select.yPos + 2 * gameState.s_PANEL_TILE_SIDE_LENGTH;
							}
							else {
								select.yPos = std::min(select.yPos + gameState.s_PANEL_TILE_SIDE_LENGTH, gameState.s_SCREEN_PANEL_HEIGHT - gameState.s_PANEL_TILE_SIDE_LENGTH);
							}
							break;
						case SDLK_LEFT:
							select.xPos = std::max(select.xPos - gameState.s_PANEL_TILE_SIDE_LENGTH, gameState.m_SCREEN_WIDTH);
							break;
						case SDLK_RIGHT:
							select.xPos = std::min(select.xPos + gameState.s_PANEL_TILE_SIDE_LENGTH, gameState.m_SCREEN_WIDTH + gameState.s_SCREEN_PANEL_WIDTH - gameState.s_PANEL_TILE_SIDE_LENGTH);
							break;
						//action
						
						case SDLK_r:
							// A roundabout method of checking the location of the selector and choosing the appropriate tower to place
							int tempX = (select.xPos - gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT)/64 + 1;
							int tempY = (select.yPos - gameState.s_PANEL_TILE_SIDE_LENGTH)/64 + 1;

							int tempVar = tempX * 10 + tempY;							

							switch (tempVar)
							{
							case 11:
							{
								// Place an arrow tower in the player's location
								if (!buildingTiles[player.xPos / 64][player.yPos / 64].hasBuilding && gameState.woodAmount >= std::get<0>(gameState.arrowTowerCost) && gameState.stoneAmount >= std::get<1>(gameState.arrowTowerCost) && gameState.gemAmount >= std::get<2>(gameState.arrowTowerCost) && gameState.ironAmount >= std::get<3>(gameState.arrowTowerCost))
								{
									Tower tempTower{ towerBaseArrowTexturePtr, player.xPos, player.yPos, 3, 2, 3 };
									towers.push_back(tempTower);

									buildingTiles[player.xPos / 64][player.yPos / 64].hasBuilding = true;
									gameState.woodAmount -= std::get<0>(gameState.arrowTowerCost);
									gameState.stoneAmount -= std::get<1>(gameState.arrowTowerCost);
									gameState.gemAmount -= std::get<2>(gameState.arrowTowerCost);
									gameState.ironAmount -= std::get<3>(gameState.arrowTowerCost);
								}
								break;
							}	
							case 21:
							{
								// Place a lava tower in the player's location
								if (!buildingTiles[player.xPos / 64][player.yPos / 64].hasBuilding && gameState.woodAmount >= std::get<0>(gameState.lavaTowerCost) && gameState.stoneAmount >= std::get<1>(gameState.lavaTowerCost) && gameState.gemAmount >= std::get<2>(gameState.lavaTowerCost) && gameState.ironAmount >= std::get<3>(gameState.lavaTowerCost))
								{
									Tower tempTower{ towerBaseLavaTexturePtr, player.xPos, player.yPos, 1, 10, 8 };
									towers.push_back(tempTower);

									buildingTiles[player.xPos / 64][player.yPos / 64].hasBuilding = true;
									gameState.woodAmount -= std::get<0>(gameState.lavaTowerCost);
									gameState.stoneAmount -= std::get<1>(gameState.lavaTowerCost);
									gameState.gemAmount -= std::get<2>(gameState.lavaTowerCost);
									gameState.ironAmount -= std::get<3>(gameState.lavaTowerCost);
								}
								break;
							}
							case 12:
							{
								// Place a magic tower in the player's location
								if (!buildingTiles[player.xPos / 64][player.yPos / 64].hasBuilding && gameState.woodAmount >= std::get<0>(gameState.magicTowerCost) && gameState.stoneAmount >= std::get<1>(gameState.magicTowerCost) && gameState.gemAmount >= std::get<2>(gameState.magicTowerCost) && gameState.ironAmount >= std::get<3>(gameState.magicTowerCost))
								{
									Tower tempTower{ towerBaseMagicTexturePtr, player.xPos, player.yPos, 2, 5, 5 };
									towers.push_back(tempTower);

									buildingTiles[player.xPos / 64][player.yPos / 64].hasBuilding = true;
									gameState.woodAmount -= std::get<0>(gameState.magicTowerCost);
									gameState.stoneAmount -= std::get<1>(gameState.magicTowerCost);
									gameState.gemAmount -= std::get<2>(gameState.magicTowerCost);
									gameState.ironAmount -= std::get<3>(gameState.magicTowerCost);
								}
								break;
							}
							case 14:
								//upg sword
								PLOG_INFO << "UPGRADE COMPLETED";
								break;

							}
						}



						//Start/stop
						if (e.key.keysym.sym == SDLK_o)
						{
							if (gameState.m_Timer.isStarted())
							{
								gameState.m_Timer.stop();
							}
							else
							{
								gameState.m_Timer.start();
							}
						}
						//Pause/unpause
						else if (e.key.keysym.sym == SDLK_p)
						{
							if (gameState.m_Timer.isPaused())
							{
								gameState.m_Timer.unpause();
							}
							else
							{
								gameState.m_Timer.pause();
							}
						}
					}
				}

				//Set text to be rendered
				gameState.m_TimeText.str("");
				gameState.m_TimeText << "Seconds since start time (s: start/stop, p: pause/unpause): " << (gameState.m_Timer.getTicks() / 1000.0f);

				gameState.s_WoodAmountText.str("");
				gameState.s_WoodAmountText << gameState.woodAmount;

				gameState.s_StoneAmountText.str("");
				gameState.s_StoneAmountText << gameState.stoneAmount;
				
				gameState.s_IronAmountText.str("");
				gameState.s_IronAmountText << gameState.ironAmount;

				gameState.s_GemAmountText.str("");
				gameState.s_GemAmountText << gameState.gemAmount;

				gameState.s_HealthAmountText.str("");
				gameState.s_HealthAmountText << gameState.health;



				//Render text
				if (!timeTextTexture.loadFromRenderedText(gameState.m_TimeText.str().c_str(), textColor, gameState))
				{
					PLOG_ERROR << "Unable to render time texture!\n";
				}

				if (!woodTextTexture.loadFromRenderedText(gameState.s_WoodAmountText.str().c_str(), textColor, gameState))
				{
					PLOG_ERROR << "Unable to render time texture!\n";
				}

				if (!stoneTextTexture.loadFromRenderedText(gameState.s_StoneAmountText.str().c_str(), textColor, gameState))
				{
					PLOG_ERROR << "Unable to render time texture!\n";
				}

				if (!ironTextTexture.loadFromRenderedText(gameState.s_IronAmountText.str().c_str(), textColor, gameState))
				{
					PLOG_ERROR << "Unable to render time texture!\n";
				}

				if (!gemTextTexture.loadFromRenderedText(gameState.s_GemAmountText.str().c_str(), textColor, gameState))
				{
					PLOG_ERROR << "Unable to render time texture!\n";
				}

				if (!heartTextTexture.loadFromRenderedText(gameState.s_HealthAmountText.str().c_str(), textColor, gameState))
				{
					PLOG_ERROR << "Unable to render time texture!\n";
				}
				

				//Clear screen
				SDL_SetRenderDrawColor(gameState.m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gameState.m_Renderer);

				//Create the viewport grid
				std::vector<SDL_Rect> groundViewportTiles{};
				generateViewportTiles(groundViewportTiles, gameState);

				for (SDL_Rect viewport : groundViewportTiles)
				{
					groundTexture.render(viewport.x, viewport.y, gameState);
				}

				//Create Selection viewport grid
				std::vector<SDL_Rect> selectionGroundViewportTiles{};
				generateSelectionViewportTiles(selectionGroundViewportTiles, gameState);

				for (SDL_Rect viewport : selectionGroundViewportTiles)
				{
					selectionTile.render(viewport.x, viewport.y, gameState);
				}
				//backgound rendering
				rightTexture.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH, gameState);
				bottomTexture.render(0, gameState.m_SCREEN_HEIGHT, gameState);
				


				//resources and health icon rendering
				woodIconTexture.render(40, gameState.m_SCREEN_HEIGHT + (textTexture.getHeight()) + 5,gameState);
				stoneIconTexture.render(40 + 100, gameState.m_SCREEN_HEIGHT + (textTexture.getHeight()) + 5, gameState);
				ironIconTexture.render(40 + 200, gameState.m_SCREEN_HEIGHT + (textTexture.getHeight()) + 5, gameState);
				gemIconTexture.render(40 + 300, gameState.m_SCREEN_HEIGHT + (textTexture.getHeight()) + 5, gameState);
				heartIconTexture.render(40 + 450, gameState.m_SCREEN_HEIGHT + (textTexture.getHeight()) + 5, gameState);

				//selection panel rendering
				towersText.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT, 0, gameState);
				uprgadesText.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT, gameState.s_PANEL_TILE_SIDE_LENGTH * 3, gameState);


				towerBaseArrowTexture.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT, gameState.s_PANEL_TILE_SIDE_LENGTH, gameState);
				towerBaseLavaTexture.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT + gameState.s_PANEL_TILE_SIDE_LENGTH, gameState.s_PANEL_TILE_SIDE_LENGTH, gameState);
				towerBaseMagicTexture.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT, 2 * gameState.s_PANEL_TILE_SIDE_LENGTH, gameState);

				upgradeSwordTexture.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT, 4 * gameState.s_PANEL_TILE_SIDE_LENGTH, gameState);

				//selection cost rendering
				int tempX = (select.xPos - gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT) / 64 + 1;
				int tempY = (select.yPos - gameState.s_PANEL_TILE_SIDE_LENGTH) / 64 + 1;

				int tempVar = tempX * 10 + tempY;

				gameState.s_WoodCostAmountText.str("");
				gameState.s_StoneCostAmountText.str("");
				gameState.s_IronCostAmountText.str("");
				gameState.s_GemCostAmountText.str("");

				switch (tempVar) {
				case 11:
					//icon render
					woodIconTexture.render(gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 10, gameState);
					stoneIconTexture.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 40, gameState);
					ironIconTexture.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 70, gameState);
					gemIconTexture.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 100, gameState);

					//cost render
					gameState.s_WoodCostAmountText << std::get<0>(gameState.arrowTowerCost);
					gameState.s_StoneCostAmountText << std::get<1>(gameState.arrowTowerCost);
					gameState.s_IronCostAmountText << std::get<2>(gameState.arrowTowerCost);
					gameState.s_GemCostAmountText << std::get<3>(gameState.arrowTowerCost);

					break;

				case 21:
					//icon render
					woodIconTexture.render(gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 10, gameState);
					stoneIconTexture.render(gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 40, gameState);
					ironIconTexture.render(gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 70, gameState);
					gemIconTexture.render(gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 100, gameState);

					//cost render
					gameState.s_WoodCostAmountText << std::get<0>(gameState.lavaTowerCost);
					gameState.s_StoneCostAmountText << std::get<1>(gameState.lavaTowerCost);
					gameState.s_IronCostAmountText << std::get<2>(gameState.lavaTowerCost);
					gameState.s_GemCostAmountText << std::get<3>(gameState.lavaTowerCost);

					break;

				case 12:
					//icon render
					woodIconTexture.render(gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 10, gameState);
					stoneIconTexture.render(gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 40, gameState);
					ironIconTexture.render(gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 70, gameState);
					gemIconTexture.render(gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 100, gameState);

					//cost render
					gameState.s_WoodCostAmountText << std::get<0>(gameState.magicTowerCost);
					gameState.s_StoneCostAmountText << std::get<1>(gameState.magicTowerCost);
					gameState.s_IronCostAmountText << std::get<2>(gameState.magicTowerCost);
					gameState.s_GemCostAmountText << std::get<3>(gameState.magicTowerCost);

					break;

				case 14:
					//icon render
					woodIconTexture.render(gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 10, gameState);
					stoneIconTexture.render(gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 40, gameState);
					ironIconTexture.render(gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 70, gameState);
					gemIconTexture.render(gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT + 20, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 100, gameState);

					//cost render
					gameState.s_WoodCostAmountText << std::get<0>(gameState.damageUpgradeCost);
					gameState.s_StoneCostAmountText << std::get<1>(gameState.damageUpgradeCost);
					gameState.s_IronCostAmountText << std::get<2>(gameState.damageUpgradeCost);
					gameState.s_GemCostAmountText << std::get<3>(gameState.damageUpgradeCost);
					
					break;

					
				}
				if (!woodCostAmountTexture.loadFromRenderedText(gameState.s_WoodCostAmountText.str().c_str(), textColor, gameState))
				{
					PLOG_ERROR << "Unable to render time texture!\n";
				}

				if (!stoneCostAmountTexture.loadFromRenderedText(gameState.s_StoneCostAmountText.str().c_str(), textColor, gameState))
				{
					PLOG_ERROR << "Unable to render time texture!\n";
				}

				if (!ironCostAmountTexture.loadFromRenderedText(gameState.s_IronCostAmountText.str().c_str(), textColor, gameState))
				{
					PLOG_ERROR << "Unable to render time texture!\n";
				}

				if (!gemCostAmountTexture.loadFromRenderedText(gameState.s_GemCostAmountText.str().c_str(), textColor, gameState))
				{
					PLOG_ERROR << "Unable to render time texture!\n";
				}
				

				woodCostAmountTexture.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT + 70, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 13, gameState);
				stoneCostAmountTexture.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT + 70, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 43, gameState);
				ironCostAmountTexture.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT + 70, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 73, gameState);
				gemCostAmountTexture.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT + 70, 5 * gameState.s_PANEL_TILE_SIDE_LENGTH + 103, gameState);


				// Render path for enemies
				for (std::tuple<int, int> pos : gameState.enemyPath)
				{
					stoneRoadTexture.render((std::get<0>(pos) * gameState.m_TILE_SIDE_LENGTH), (std::get<1>(pos) * gameState.m_TILE_SIDE_LENGTH), gameState);
					buildingTiles[std::get<0>(pos)][std::get<1>(pos)].hasBuilding = true;
				}


				// Render placed towers
				for (Tower &tower : towers)
				{
					tower.towerTexture->render(tower.xPos, tower.yPos, gameState);
				}

				// Deal damage with towers to enemies in range of them
				if (attacksMade == (int)(gameState.m_Timer.getTicks() / 1000.f))
				{
					for (Tower &tower : towers)
					{
						int attacksMade{ 0 };
						for (Enemy &enemy : enemies)
						{
							if (attacksMade < tower.attacksPerSec && !enemy.isDead)
							{
								tower.dealDamage(enemy, gameState);
								++attacksMade;
							}
							std::cout << "Enemy's health is " << enemy.getHp() << '\n';
						}
					}
					++attacksMade;
					std::cout << '\n';
				}


				//heartLocation render
				heartRoadTexture.render((std::get<0>(gameState.heartLocation)* gameState.m_TILE_SIDE_LENGTH), (std::get<1>(gameState.heartLocation)* gameState.m_TILE_SIDE_LENGTH), gameState);

				//heartLocation check if enemy reached
				for (Enemy &enemy : enemies)
				{
					if (enemy.xPos / 64 == std::get<0>(gameState.heartLocation) && enemy.yPos / 64 == std::get<1>(gameState.heartLocation) && !enemy.isDead) {
						std::cout << "enemy reached the heart";
						//killing the enemy
						enemy.isDead = true;
						//enemy.move(1920, 1920, gameState);

						//-- health
						--gameState.health;

					}
				}

				

				//selection render
				select.playerTexture->render(select.xPos, select.yPos, gameState);


				// Move each enemy to the next tile every few seconds
				for (int i{ 0 }; i < gameState.enemyCount; ++i)
				{
					if (!enemies[i].isDead)
					{
						for (int j{ 0 }; j < gameState.enemyPath.size(); ++j)
						{
							if (enemies[i].timeToMove <= gameState.m_Timer.getTicks() / 1000.f && gameState.m_Timer.getTicks() / 1000.f <= enemies[i].timeToMove + 1 && enemies[i].moveCount == j)
							{
								enemies[i].move(std::get<0>(gameState.enemyPath[j]) * 64, std::get<1>(gameState.enemyPath[j]) * 64, gameState);
								++enemies[i].moveCount;
								enemies[i].timeToMove += 2;
							}
						}
						enemies[i].enemyTexture->render(enemies[i].xPos, enemies[i].yPos, gameState);
					}
				}

				if (gameState.health <= 0) 
				{
					std::cout << "You have failed!";
				}

				//Render timer
				//timeTextTexture.render(0, gameState.m_SCREEN_HEIGHT + (textTexture.getHeight() / 2), gameState);

				//Render resources amounts
				woodTextTexture.render(80, gameState.m_SCREEN_HEIGHT + 10, gameState);
				stoneTextTexture.render(80 + 100, gameState.m_SCREEN_HEIGHT + 10, gameState);
				ironTextTexture.render(80 + 200, gameState.m_SCREEN_HEIGHT + 10, gameState);
				gemTextTexture.render(80 + 300, gameState.m_SCREEN_HEIGHT + 10, gameState);
				heartTextTexture.render(80 + 450, gameState.m_SCREEN_HEIGHT + 10, gameState);


				//characterTexture.render(gameState.m_TILE_SIDE_LENGTH * 2, gameState.m_TILE_SIDE_LENGTH * 3, gameState);
				player.playerTexture->render(player.xPos, player.yPos, gameState);


				//Update screen
				SDL_RenderPresent(gameState.m_Renderer);


			}
		}
	}

	PLOG_INFO << "Exiting app...\n";

	return 0;
}
