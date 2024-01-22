#include "App.h"

#include "Texture.h"
#include "GameState.h"
#include "Player.h"
#include "Tile.h"
#include "SelectionTile.h"

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

bool loadMedia(GameState& gameState, Texture& textTexture, Texture& groundTexture, Texture& characterTexture, Texture& towerTexture, Texture& panelSelection, Texture& selectionTile)
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
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!textTexture.loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor, gameState))
		{
			PLOG_ERROR << "Failed to render text texture!\n";
			successfullyLoaded = false;
		}
	}

	PLOG_INFO << "Successfiully loaded media.";
	return successfullyLoaded;
}

//void close()
//{
//	//Free loaded image
//	SDL_DestroyTexture(g_GroundTexture);
//	g_GroundTexture = NULL;
//
//	//Destroy window
//	SDL_DestroyRenderer(g_Renderer);
//	SDL_DestroyWindow(g_Window);
//	g_Window = NULL;
//	g_Renderer = NULL;
//
//	//Quit SDL subsystems
//	IMG_Quit();
//	SDL_Quit();
//}

//SDL_Texture* loadTexture(std::string path, GameState& gameState)
//{
//	//The final texture
//	SDL_Texture* newTexture = NULL;
//
//	//Load image at specified path
//	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//	if (loadedSurface == NULL)
//	{
//		PLOG_ERROR << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << '\n';
//	}
//	else
//	{
//		//Create texture from surface pixels
//		newTexture = SDL_CreateTextureFromSurface(gameState.m_Renderer, loadedSurface);
//		if (newTexture == NULL)
//		{
//			PLOG_ERROR << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << '\n';
//		}
//
//		//Get rid of old loaded surface
//		SDL_FreeSurface(loadedSurface);
//	}
//
//	return newTexture;
//
//}

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
		Texture groundTexture{};
		Texture characterTexture{};
		Texture towerTexture{};

		Texture textTexture{};
		Texture timeTextTexture{};

		Texture* characterTexturePtr{ &characterTexture };


		/////////////////////
		Texture panelSelection{};
		Texture selectionTile{};

		Player player{ characterTexturePtr, gameState.m_TILE_SIDE_LENGTH * 3, gameState.m_TILE_SIDE_LENGTH * 4 };

		Player select{ characterTexturePtr, gameState.m_TILE_SIDE_LENGTH * 3, gameState.m_TILE_SIDE_LENGTH * 4 };

		std::vector<std::vector<Tile>> buildingTiles{};
		generateTiles(buildingTiles, gameState);

		//Load media
		if (!loadMedia(gameState, textTexture, groundTexture, characterTexture, towerTexture, panelSelection, selectionTile))
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
						case SDLK_UP:
							player.yPos = std::max(player.yPos - gameState.m_TILE_SIDE_LENGTH, 0);
							break;
						case SDLK_DOWN:
							player.yPos = std::min(player.yPos + gameState.m_TILE_SIDE_LENGTH, gameState.m_SCREEN_HEIGHT - gameState.m_TILE_SIDE_LENGTH);
							break;
						case SDLK_LEFT:
							player.xPos = std::max(player.xPos - gameState.m_TILE_SIDE_LENGTH, 0);
							break;
						case SDLK_RIGHT:
							player.xPos = std::min(player.xPos + gameState.m_TILE_SIDE_LENGTH, gameState.m_SCREEN_WIDTH - gameState.m_TILE_SIDE_LENGTH);
							break;
						case SDLK_SPACE:
							buildingTiles[player.xPos / 64][player.yPos / 64].tileTexture = &towerTexture;
							buildingTiles[player.xPos / 64][player.yPos / 64].hasBuilding = true;
							break;
						}

						//Start/stop
						if (e.key.keysym.sym == SDLK_s)
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


				//characterTexture.render(gameState.m_TILE_SIDE_LENGTH * 2, gameState.m_TILE_SIDE_LENGTH * 3, gameState);
				player.playerTexture->render(player.xPos, player.yPos, gameState);

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
