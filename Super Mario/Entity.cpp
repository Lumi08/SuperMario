#include "Entity.h"
#include "Texture2D.h"

Entity::Entity(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int width, int height, float renderScale)
{
	mRenderer = renderer;
	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	mRenderScale = renderScale;
	mWidth = width * mRenderScale;
	mHeight = height * mRenderScale;
	mHitbox = new SDL_Rect{ (int)mPosition.x, (int)mPosition.y, (int)(mWidth), (int)(mHeight) };
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
	mHitbox->w = width;
	mHitbox->h = height;
}

void Entity::Debug()
{
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(mRenderer, mHitbox);
}
