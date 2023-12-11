#include "App.h"
#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <SDL.h>
#include <iostream>

//The window we'll be rendering to
SDL_Window* g_Window = NULL;

//The surface contained by the window
SDL_Surface* g_ScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* g_HelloWorld = NULL;

bool init()
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
		//Create window
		g_Window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_Window == NULL)
		{
			PLOG_ERROR << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
			successfullyInitialized = false;
		}
		else
		{
			//Get window surface
			g_ScreenSurface = SDL_GetWindowSurface(g_Window);
		}
	}
	PLOG_INFO << "Successfully initialized.";
	return successfullyInitialized;
}

bool loadMedia()
{
	//Loading success flag
	bool successfullyLoaded = true;

	//Load splash image
	const char* imagePath{ "img/hello_world.bmp" };
	g_HelloWorld = SDL_LoadBMP(imagePath);
	if (g_HelloWorld == NULL)
	{
		PLOG_ERROR << "Unable to load image " << imagePath << "SDL Error: " << SDL_GetError() << '\n';
		successfullyLoaded = false;
	}

	PLOG_INFO << "Successfiully loaded.";
	return successfullyLoaded;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface(g_HelloWorld);
	g_HelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(g_Window);
	g_Window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Initialize the logger (both to the text file and the console)
	static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
	plog::init(plog::debug, "log.txt").addAppender(&consoleAppender);

	PLOG_INFO << "Starting app...";

	//Start up SDL and create window
	if (!init())
	{
		PLOG_ERROR << "Failed to initialize!\n";
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			PLOG_ERROR << "Failed to load media!\n";
		}
		else
		{
			//Apply the image
			SDL_BlitSurface(g_HelloWorld, NULL, g_ScreenSurface, NULL);

			//Update the surface
			SDL_UpdateWindowSurface(g_Window);

			//Hack to get window to stay up
			SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
		}
	}

	//Free resources and close SDL
	close();

	PLOG_INFO << "Exiting app...\n";

	return 0;
}
