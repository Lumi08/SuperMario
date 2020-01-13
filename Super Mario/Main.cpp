#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <iostream>

//Globals
SDL_Window*	gWindow	= NULL;

//Prototypes
bool InitSDL();
bool Update();
void CloseSDL();

using namespace::std;

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		bool quit = false;

		while (!quit)
		{
			quit = Update();
		}
	}

	CloseSDL();
	return 0;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	} 
	else
	{
		gWindow = SDL_CreateWindow("Super Mario Bros",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			cout << "SDL did not initialise. Error: " << SDL_GetError();
			return false;
		}
	}
	return true;
}

bool Update()
{
	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type)
	{
		case SDL_QUIT:
		{
			return true;
			break;
		}

		case SDL_KEYUP:
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				{
					return true;
				}
			}
		}
	}

	return false;
}

void CloseSDL()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}