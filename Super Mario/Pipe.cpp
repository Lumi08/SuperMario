#include "Pipe.h"


Pipe::Pipe(SDL_Renderer* renderer, std::string imagePath, Vector2D position) : Entity(renderer, imagePath, position, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT)
{
	mSourceRect = new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT };
}

Pipe::~Pipe()
{
}

void Pipe::Render(SDL_Rect* camera)
{
	mTexture->Render(mPosition, SDL_FLIP_NONE, RENDERSCALE, camera, 0.0f, mSourceRect);
}

void Pipe::Update(float deltaTime, SDL_Event e)
{
	UpdateHitbox();
}
