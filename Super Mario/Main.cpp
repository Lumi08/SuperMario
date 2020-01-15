#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <iostream>
#include <string>

//Globals
SDL_Window*	gWindow	= NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

double gAngle = 0; 

//Prototypes
bool InitSDL();
bool Update();
void CloseSDL();
void Render();
SDL_Texture* LoadTextureFromFile(std::string path);
void FreeTexture();

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

		gTexture = LoadTextureFromFile("Images/test.bmp");
		if(gTexture == NULL)
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
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	SDL_Rect renderLocation = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_RenderCopyEx(gRenderer, gTexture, NULL, &renderLocation, gAngle, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(gRenderer);
}


void FreeTexture() 
{
	if (gTexture != NULL)
	{
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
	}
}

SDL_Texture* LoadTextureFromFile(string path)
{
	FreeTexture();

	SDL_Texture* pTexture = NULL;

	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		pTexture = SDL_CreateTextureFromSurface(gRenderer, pSurface);
		if (pTexture == NULL)
		{
			cout << "unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}

		SDL_FreeSurface(pSurface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError() << endl;
	}

	return pTexture;
}

void CloseSDL()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	FreeTexture();
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}