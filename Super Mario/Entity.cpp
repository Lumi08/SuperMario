#include "Entity.h"
#include "Texture2D.h"

Entity::Entity(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int rawWidth, int rawHeight)
{
	mRenderer = renderer;
	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	mRawHeight = rawHeight;
	mRawWidth = rawWidth;
	mHitbox = new SDL_Rect{ (int)mPosition.x, (int)mPosition.y, (int)(mRawWidth * RENDERSCALE), (int)(mRawHeight * RENDERSCALE) };
}

Entity::~Entity()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
}

void Entity::Render()
{

}

void Entity::Update(float deltaTime, SDL_Event)
{

}

void Entity::UpdateHitbox()
{
	mHitbox->x = mPosition.x;
	mHitbox->y = mPosition.y;
}

void Entity::Debug()
{
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(mRenderer, mHitbox);
}
