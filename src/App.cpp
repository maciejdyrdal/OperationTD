#include "App.h"

#include "Texture.h"
#include "GameState.h"

#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <SDL.h>
#include <SDL_image.h>

#include <array>
#include <iostream>
#include <map>


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
		gameState.m_Window = SDL_CreateWindow("OperationTD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gameState.m_SCREEN_WIDTH, gameState.m_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gameState.m_Window == NULL)
		{
			PLOG_ERROR << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
			successfullyInitialized = false;
		}
		else
		{
			//Create renderer for window
			gameState.m_Renderer = SDL_CreateRenderer(gameState.m_Window, -1, SDL_RENDERER_ACCELERATED);
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
			}
		}
	}
	PLOG_INFO << "Successfully initialized.";
	return successfullyInitialized;
}

bool loadMedia(GameState& gameState, Texture& groundTexture, Texture& characterTexture)
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

	////Load PNG texture
	//gameState.m_GroundTexture = loadTexture("img/ground.png", gameState);
	//if (gameState.m_GroundTexture == NULL)
	//{
	//	PLOG_ERROR << "Failed to load PNG image!\n";
	//	successfullyLoaded = false;
	//}

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

bool generateViewportTiles(std::vector<SDL_Rect>& viewports, GameState& gameState)
{
	bool successfullyGenerated{ false };

	for (int x{ 0 }; x < gameState.m_SCREEN_WIDTH_TILE_COUNT; ++x)
	{
		for (int y{ 0 }; y < gameState.m_SCREEN_HEIGHT_TILE_COUNT; ++y)
		{
			viewports.push_back({x * gameState.m_TILE_SIDE_LENGTH, y * gameState.m_TILE_SIDE_LENGTH, gameState.m_TILE_SIDE_LENGTH, gameState.m_TILE_SIDE_LENGTH});
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
		//Filenames of textures to be loaded
		//constexpr std::array<std::string, 2> textureFilenames { "img/ground.png", "img/character.png" };
		//std::array<Texture, textureFilenames.size()> texturesArray;

		//const char* textureFilenames[] = { "img/ground.png", "img/character.png" };
		//const int arraySize{ sizeof(textureFilenames) / sizeof(textureFilenames[0]) };
		//Texture texturesArray[arraySize];

		Texture groundTexture{};
		Texture characterTexture{};

		//Load media
		if (!loadMedia(gameState, groundTexture, characterTexture))
		{
			PLOG_ERROR << "Failed to load media!\n";
		}
		else
		{
			// Main loop flag
			bool quit{ false };

			//Event handler
			SDL_Event e;

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
				}

				//Clear screen
				SDL_SetRenderDrawColor(gameState.m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gameState.m_Renderer);

				//Create the viewport grid
				std::vector<SDL_Rect> groundViewportTiles{};
				generateViewportTiles(groundViewportTiles, gameState);

				//std::string textureNames[] = { "img/ground.png", "img/character.png" };
				//Texture textures[sizeof(textureNames) / sizeof(textureNames[0])];
				//textures[0].loadFromFile(textureNames[0], gameState);
				//textures[1].loadFromFile(textureNames[1], gameState);

				//Texture groundTexture{};
				//groundTexture.loadFromFile("img/ground.png", gameState);
				//Texture characterTexture{};
				//characterTexture.loadFromFile("img/character.png", gameState);

				for (SDL_Rect viewport : groundViewportTiles)
				{
					//SDL_RenderSetViewport(gameState.m_Renderer, &viewport);
					//gameState.m_texturesList.at("ground.png").render(viewport.x, viewport.y, gameState);
					//groundTexture.render(viewport.x, viewport.y, gameState);
					//SDL_RenderCopy(gameState.m_Renderer, gameState.m_GroundTexture, NULL, NULL);

					groundTexture.render(viewport.x, viewport.y, gameState);
					//gameState.m_texturesArray[0].render(viewport.x, viewport.y, gameState);
					//textures[0].render(viewport.x, viewport.y, gameState);

					//texturesMap.at("ground.png").render(viewport.x, viewport.y, gameState);
				}

				characterTexture.render(gameState.m_TILE_SIDE_LENGTH * 2, gameState.m_TILE_SIDE_LENGTH * 3, gameState);
				//characterTexture.render(gameState.m_TILE_SIDE_LENGTH * 2, gameState.m_TILE_SIDE_LENGTH * 3, gameState);

				//Update screen
				SDL_RenderPresent(gameState.m_Renderer);
			}
		}
	}

	//Free resources and close SDL
	//close();

	PLOG_INFO << "Exiting app...\n";

	return 0;
}
