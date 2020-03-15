#include "Text.h"

Text::Text(SDL_Renderer* renderer, const std::string fontPath, SDL_Color color, int fontSize)
{
	mRenderer = renderer;
	mFont = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (mFont == NULL)
	{
		std::cerr << "Font didnt load corretcly" << std::endl;
	}
	mTextColour = color;
}

Text::~Text()
{
}



void Text::CreateTextureFromText(std::string message)
{
	Free();
	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
	mTextSurface = TTF_RenderText_Solid(mFont, message.c_str(), mTextColour);
	if (mTextSurface == nullptr) {
		TTF_CloseFont(mFont);
		std::cerr << "Surface didnt load correctly!" << std::endl;
		return;
	}
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mTextSurface);
	if (mTextTexture == nullptr) {
		std::cerr << "TextTexture didnt load correctly!" << std::endl;
	}
	mWidth = mTextSurface->w;
	mHeight = mTextSurface->h;
	//Clean up the surface
	SDL_FreeSurface(mTextSurface);
}

void Text::Free()
{
	if (mTextTexture != NULL)
	{
		SDL_DestroyTexture(mTextTexture);
		mTextTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Text::Render(Vector2D position, SDL_RendererFlip flip, float renderScale, SDL_Rect* camera, double angle = 0)
{
	SDL_Rect renderLocation = { (int)position.x , (int)position.y, mWidth, mHeight };
	//mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mTextSurface);
	SDL_RenderCopy(mRenderer, mTextTexture, NULL, &renderLocation);
}

void Text::Render(std::string message, Vector2D position, SDL_RendererFlip flip, float renderScale, SDL_Rect* camera, double angle = 0)
{
	
	//mTextSurface = TTF_RenderText_Solid(mFont, message.c_str(), mTextColour);
	//SDL_Rect renderLocation = { (int)position.x - camera->x, (int)position.y, mTextSurface->w, mTextSurface->h };

	//mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mTextSurface);

	//SDL_RenderCopyEx(mRenderer, mTextTexture, NULL, &renderLocation, angle, NULL, flip);

	//SDL_FreeSurface(mTextSurface);
}
