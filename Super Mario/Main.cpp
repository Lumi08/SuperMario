#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>

#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"

//Globals
SDL_Window*	gWindow	= NULL;
SDL_Renderer* gRenderer = NULL;

Texture2D* gTexture = NULL;

double gAngle = 0; 

//Prototypes
bool InitSDL();
bool Update();
void CloseSDL();
void Render();


using namespace::std;

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		bool quit = false;

		while (!quit)
		{
			Render();
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

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		if (gRenderer != NULL)
		{
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

		gTexture = new Texture2D(gRenderer);
		if (!gTexture->LoadFromFile("Images/test.bmp"))
		{
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

		case SDL_KEYDOWN:
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_w:
				{
					gAngle += 1;
					break;
				}

				case SDLK_s:
				{
					gAngle -= 1;
					break;
				}
			}
		}
	}

	return false;
}

void Render()
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	gTexture->Render(Vector2D(), SDL_FLIP_NONE, gAngle);

	SDL_RenderPresent(gRenderer);
}


void CloseSDL()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	delete gTexture;
	gTexture = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}