#include "App.h"

#include "Texture.h"
#include "GameState.h"
#include "Player.h"
#include "Tile.h"
#include "SelectionTile.h"
#include "Enemy.h"

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
	//Initialization flag
	bool successfullyInitialized{ true };

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		PLOG_ERROR << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
		successfullyInitialized = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			PLOG_WARNING << "Warning: Linear texture filtering not enabled!";
		}

		//Create window
		gameState.m_Window = SDL_CreateWindow("OperationTD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gameState.m_SCREEN_WIDTH + gameState.s_SCREEN_PANEL_WIDTH, gameState.m_SCREEN_HEIGHT + 50, SDL_WINDOW_SHOWN);
		if (gameState.m_Window == NULL)
		{
			PLOG_ERROR << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
			successfullyInitialized = false;
		}
		else
		{
			//Create renderer for window
			gameState.m_Renderer = SDL_CreateRenderer(gameState.m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gameState.m_Renderer == NULL)
			{
				PLOG_ERROR << "Renderer could not be created! SDL Error: " << SDL_GetError() << '\n';
				successfullyInitialized = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gameState.m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					PLOG_ERROR << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << '\n';
					successfullyInitialized = false;
				}

				//Initialize SDL_ttf
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

bool loadMedia(GameState& gameState, Texture& textTexture, Texture& groundTexture, Texture& characterTexture, Texture& towerTexture, Texture& panelSelection, Texture& selectionTile, Texture& enemyTexture, Texture& gem_icon, Texture& iron_icon, Texture& stone_icon, Texture& goblin, Texture& knight, Texture& smallGoblin, Texture& towerBaseArrow, Texture& towerBaseLava, Texture& towerBaseMagic, Texture& stoneRoad, Texture& protagonist, Texture& towersText)
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
	if (!panelSelection.loadFromFile(gameState.m_textureFilenames[3], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[3] << "!\n";
		successfullyLoaded = false;
	}

	if (!selectionTile.loadFromFile(gameState.m_textureFilenames[4], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[4] << "!\n";
		successfullyLoaded = false;
	}

	gameState.m_Font = TTF_OpenFont("fonts/Roboto-Black.ttf", gameState.m_FontSize);
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

	if (!gem_icon.loadFromFile(gameState.m_textureFilenames[6], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[6] << "!\n";
		successfullyLoaded = false;
	}

	if (!iron_icon.loadFromFile(gameState.m_textureFilenames[7], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[7] << "!\n";
		successfullyLoaded = false;
	}

	if (!stone_icon.loadFromFile(gameState.m_textureFilenames[8], gameState))
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

	if (!towerBaseArrow.loadFromFile(gameState.m_textureFilenames[12], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[12] << "!\n";
		successfullyLoaded = false;
	}

	if (!towerBaseLava.loadFromFile(gameState.m_textureFilenames[13], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[13] << "!\n";
		successfullyLoaded = false;
	}

	if (!towerBaseMagic.loadFromFile(gameState.m_textureFilenames[14], gameState))
	{
		PLOG_ERROR << "Failed to load texture image " << gameState.m_textureFilenames[14] << "!\n";
		successfullyLoaded = false;
	}

	if (!stoneRoad.loadFromFile(gameState.m_textureFilenames[15], gameState))
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


	PLOG_INFO << "Successfiully loaded media.";
	return successfullyLoaded;
}

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

//Selection tiles generating

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
	//Initialize the logger (both to the text file and the console)
	static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
	plog::init(plog::debug, "log.txt").addAppender(&consoleAppender);

	PLOG_INFO << "Starting app...";

	//Create pointers to objects representing the window, renderer and textures which will be passed to functions along the whole app's life
	SDL_Window* window{ NULL };
	SDL_Renderer* renderer{ NULL };

	//Initialize the gameState object which holds pointers to various app components and constants (such as window size)
	GameState gameState{ window, renderer };

	//Start up SDL and create window
	if (!init(gameState))
	{
		PLOG_ERROR << "Failed to initialize!\n";
	}
	else
	{
		// Initialize the texture objects
		Texture groundTexture{};
		Texture characterTexture{};
		Texture towerTexture{};
		Texture enemyTexture{};

		Texture panelSelection{};

		Texture selectionTile{};
		Texture protagonist{};

		Texture gem_icon{};
		Texture iron_icon{};
		Texture stone_icon{};
		Texture stoneRoad{};

		Texture goblin{};
		Texture knight{};
		Texture smallGoblin{};

		Texture towerBaseArrow{};
		Texture towerBaseLava{};
		Texture towerBaseMagic{};

		Texture towersText{};

		Texture textTexture{};
		Texture timeTextTexture{};

		// Initialize the texture pointers for the player character and enemies
		Texture* characterTexturePtr{ &characterTexture };
		Texture* enemyTexturePtr{ &enemyTexture };
		Texture* panelSelectionPtr{ &panelSelection };

		// Create the player and enemy objects
		Player player{ characterTexturePtr, gameState.m_TILE_SIDE_LENGTH * 3, gameState.m_TILE_SIDE_LENGTH * 4 };
		std::vector<Enemy> enemies;
		for (int i{ 0 }; i < gameState.enemyCount; ++i)
		{
			enemies.push_back(Enemy(enemyTexturePtr, ((gameState.m_SCREEN_WIDTH_TILE_COUNT - 1) * gameState.m_TILE_SIDE_LENGTH), ((gameState.m_SCREEN_HEIGHT_TILE_COUNT - 1) * gameState.m_TILE_SIDE_LENGTH), 20, 2 * i + 2));
		}

		//Player select{ panelSelectionPtr, gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH, 0 };
		Player select{ panelSelectionPtr, gameState.m_TILE_SIDE_LENGTH * gameState.m_SCREEN_WIDTH_TILE_COUNT,  gameState.s_PANEL_TILE_SIDE_LENGTH };

		std::vector<std::vector<Tile>> buildingTiles{};
		generateTiles(buildingTiles, gameState);

		//selection vector
		std::vector<std::vector<SelectionTile>> selections{};
		generateSelectionTiles(selections, gameState);

		//Load media
		if (!loadMedia(gameState, textTexture, groundTexture, characterTexture, towerTexture, panelSelection, selectionTile, enemyTexture, gem_icon, iron_icon, stone_icon, goblin, knight, smallGoblin, towerBaseArrow, towerBaseLava, towerBaseMagic, stoneRoad, protagonist,towersText))
		{
			PLOG_ERROR << "Failed to load media!\n";
		}
		else
		{
			// Main loop flag
			bool quit{ false };

			//Event handler
			SDL_Event e;

			//Set text color as black
			SDL_Color textColor = { 0, 0, 0, 255 };

			gameState.m_Timer.start();

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
							buildingTiles[player.xPos / 64][player.yPos / 64].tileTexture = &towerTexture;
							buildingTiles[player.xPos / 64][player.yPos / 64].hasBuilding = true;
							break;

						//selection "movement" & action
						case SDLK_UP:
							select.yPos = std::max(select.yPos - gameState.s_PANEL_TILE_SIDE_LENGTH, gameState.s_PANEL_TILE_SIDE_LENGTH);
							break;
						case SDLK_DOWN:
							select.yPos = std::min(select.yPos + gameState.s_PANEL_TILE_SIDE_LENGTH, gameState.s_SCREEN_PANEL_HEIGHT - gameState.s_PANEL_TILE_SIDE_LENGTH);
							break;
						case SDLK_LEFT:
							select.xPos = std::max(select.xPos - gameState.s_PANEL_TILE_SIDE_LENGTH, gameState.m_SCREEN_WIDTH);
							break;
						case SDLK_RIGHT:
							select.xPos = std::min(select.xPos + gameState.s_PANEL_TILE_SIDE_LENGTH, gameState.m_SCREEN_WIDTH + gameState.s_SCREEN_PANEL_WIDTH - gameState.s_PANEL_TILE_SIDE_LENGTH);
							break;
						

						
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

				//Render text
				if (!timeTextTexture.loadFromRenderedText(gameState.m_TimeText.str().c_str(), textColor, gameState))
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
				
				//selection panel rendering
				towersText.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT, 0, gameState);

				towerBaseArrow.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT, gameState.s_PANEL_TILE_SIDE_LENGTH, gameState);
				towerBaseLava.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT + gameState.s_PANEL_TILE_SIDE_LENGTH, gameState.s_PANEL_TILE_SIDE_LENGTH, gameState);
				towerBaseMagic.render(gameState.m_TILE_SIDE_LENGTH* gameState.m_SCREEN_WIDTH_TILE_COUNT, 2 * gameState.s_PANEL_TILE_SIDE_LENGTH, gameState);

				// Render path for enemies
				for (std::tuple<int, int> pos : gameState.enemyPath)
				{
					stoneRoad.render((std::get<0>(pos) * gameState.m_TILE_SIDE_LENGTH), (std::get<1>(pos) * gameState.m_TILE_SIDE_LENGTH), gameState);
				}

				//characterTexture.render(gameState.m_TILE_SIDE_LENGTH * 2, gameState.m_TILE_SIDE_LENGTH * 3, gameState);
				player.playerTexture->render(player.xPos, player.yPos, gameState);

				//selection render
				select.playerTexture->render(select.xPos, select.yPos, gameState);

				for (int x{ 0 }; x < gameState.m_SCREEN_WIDTH_TILE_COUNT; ++x)
				{
					for (int y{ 0 }; y < gameState.m_SCREEN_HEIGHT_TILE_COUNT; ++y)
					{
						if (buildingTiles[x][y].hasBuilding)
						{
							buildingTiles[x][y].tileTexture->render(buildingTiles[x][y].xPos, buildingTiles[x][y].yPos, gameState);
						}
					}
				}

				//for (int i{ 0 }; i < gameState.enemyCount; ++i)
				//{
				//	if (i * 2 + 1 <= gameState.m_Timer.getTicks() / 1000.f && gameState.m_Timer.getTicks() / 1000.f <= i * 2 + 3 && enemies[i].moveCount == i)
				//	{
				//		enemies[i].move(std::get<0>(gameState.enemyPath[i]) * 64, std::get<1>(gameState.enemyPath[i]) * 64, gameState);
				//		++enemies[i].moveCount;
				//		std::cout << enemies[i].xPos << ' ' << enemies[i].yPos << ' ' << enemies[i].moveCount << '\n';
				//	}
				//	enemies[i].enemyTexture->render(enemies[i].xPos, enemies[i].yPos, gameState);
				//}

				// Move each enemy to the next tile every few seconds
				for (int i{ 0 }; i < gameState.enemyCount; ++i)
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

				//Render timer
				timeTextTexture.render(0, gameState.m_SCREEN_HEIGHT + (textTexture.getHeight() / 2), gameState);

				//Update screen
				SDL_RenderPresent(gameState.m_Renderer);
			}
		}
	}

	PLOG_INFO << "Exiting app...\n";

	return 0;
}
