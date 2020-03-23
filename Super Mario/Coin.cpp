#include "Coin.h"

Coin::Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D position) : Entity(renderer, imagePath, position, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT)
{
	mSourceRect = new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT };
	mAnimation = new Animation(mRenderer, mTexture, mSourceRect, 6, 100, RENDERSCALE);
}

Coin::~Coin()
{
	delete mAnimation;
}

void Coin::Render(SDL_Rect* camera)
{
	mAnimation->Play(mPosition, SDL_FLIP_NONE, camera);
}

void Coin::Update(float deltaTime, SDL_Event e, int& score)
{
	
}
