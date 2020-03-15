#ifndef _TEXT_H
#define _TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

#include "Commons.h"

class Text
{
public:
	Text(SDL_Renderer* renderer, const std::string fontPath, SDL_Color color, int fontSize);
	~Text();

	void CreateTextureFromText(std::string message);

	void Free();

	void Render(Vector2D position, SDL_RendererFlip flip, float renderScale, SDL_Rect* camera, double angle);

	static SDL_Texture* RenderText(const std::string& message, const std::string& fontFile, SDL_Color color, int fontSize, SDL_Renderer* renderer);

	void Render(std::string message, Vector2D position, SDL_RendererFlip flip, float renderScale, SDL_Rect* camera, double angle);

private:
	SDL_Renderer* mRenderer;
	SDL_Texture* mTextTexture;
	SDL_Surface* mTextSurface;
	TTF_Font* mFont;
	SDL_Color mTextColour;

	int mWidth, mHeight;
};

#endif // !_TEXT_H


