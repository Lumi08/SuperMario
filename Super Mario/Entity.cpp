#include "Entity.h"
#include "Texture2D.h"

Entity::Entity(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int width, int height, float renderScale)
{
	mRenderer = renderer;
	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	mWidth = width;
	mHeight = height;
	mRenderScale = renderScale;
	mHitbox = new SDL_Rect{ (int)mPosition.x, (int)mPosition.y, (int)(width * mRenderScale), (int)(height * mRenderScale) };
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

void Entity::Update()
{

}

void Entity::UpdateHitbox(Vector2D position, int width, int height)
{
	mHitbox->x = position.x;
	mHitbox->y = position.y;
	mHitbox->w = width * mRenderScale;
	mHitbox->h = height * mRenderScale;
}

SDL_Rect* Entity::GetHitbox()
{
	return mHitbox;
}

void Entity::Debug()
{
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(mRenderer, mHitbox);
}
