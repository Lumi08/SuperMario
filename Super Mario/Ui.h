#ifndef _UI_H
#define _UI_H

#include <SDL.h>
#include "Texture2D.h"
#include "Animation.h"
#include "Constants.h"

struct Button
{
	SDL_Renderer* renderer;
	Texture2D* textTexture;
	Texture2D* hoveringImage;
	Animation* hoveringAnimation;
	SDL_Rect* hitbox;
	bool hovering;

	Button(SDL_Renderer* renderer, int x, int y, int width, int height, std::string path)
	{
		this->renderer = renderer;
		hitbox = new SDL_Rect{ x, y, width, height };
		textTexture = new Texture2D(renderer);
		textTexture->LoadFromFile(path.c_str());
		hoveringImage = new Texture2D(renderer);
		if (!hoveringImage->LoadFromFile("Images/Mario.png"))
		{
			std::cout << "Error: Failed to load background texture!" << std::endl;
		}
		hoveringAnimation = new Animation(renderer, hoveringImage, new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 2, 1000, RENDERSCALE);
		hovering = false;
	}

	~Button()
	{
		//.delete textTexture;
	}

	// Renders the button and the selection images when needed
	void Render(float scale)
	{
		textTexture->Render(Vector2D(hitbox->x, hitbox->y), SDL_FLIP_NONE, scale);

		// If the mouse is hovering over the button then render the selection images
		if (hovering)
		{
			hoveringAnimation->Play(Vector2D(hitbox->x - 50, hitbox->y + 8), SDL_FLIP_HORIZONTAL, 0.0f);
			hoveringAnimation->Play(Vector2D(hitbox->x + hitbox->w + 50 - 32, hitbox->y + 8), SDL_FLIP_NONE, 0.0f);
		}
	}

	// Checks if the mouse is on the button
	void Update(int mouseX, int mouseY)
	{
		if (RectContainsVector(Vector2D(mouseX, mouseY), hitbox))
		{
			hovering = true;
		}
		else
		{
			hovering = false;
		}
	}

	// used to chec the hitbox for the button
	void Debug()
	{
		SDL_RenderDrawRect(renderer, hitbox);
	}
};

#endif // !_UI_H