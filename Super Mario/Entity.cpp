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
	mSensorSize = 5;
	mHitbox = new SDL_Rect{ (int)mPosition.x, (int)mPosition.y, (int)(mRawWidth * RENDERSCALE), (int)(mRawHeight * RENDERSCALE) };
	InitSensors();
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

bool Entity::IsCollidingWith(Entity* entity)
{
	if (mPosition.x + mHitbox->w > entity->GetX() &&
		mPosition.x < entity->GetX() + entity->GetWidth() &&
		mPosition.y + mHitbox->h > entity->GetY() &&
		mPosition.y < entity->GetY() + entity->GetHeight())
	{
		return true;
	}
	return false;
}

SIDE Entity::GetSideCollidingWithEntity(Entity* entity)
{
	if (RectIntersects(mSensorLeft, entity->GetHitbox()))
	{
		std::cerr << "Left" << std::endl;
		return SIDE::LEFT;
	}
	if (RectIntersects(mSensorRight, entity->GetHitbox()))
	{
		std::cerr << "Right" << std::endl;
		return SIDE::RIGHT;
	}
	if (RectIntersects(mSensorTop, entity->GetHitbox()))
	{
		std::cerr << "Top" << std::endl;
		return SIDE::TOP;
	}
	if (RectIntersects(mSensorBottom, entity->GetHitbox()))
	{
		std::cerr << "Bottom" << std::endl;
		return SIDE::BOTTOM;
	}
	return SIDE::NONE;
}

void Entity::Debug()
{
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(mRenderer, mHitbox);

	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(mRenderer, mSensorLeft);
	SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(mRenderer, mSensorRight);
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderDrawRect(mRenderer, mSensorTop);
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 255);
	SDL_RenderDrawRect(mRenderer, mSensorBottom);
}

void Entity::InitSensors()
{
	mSensorLeft = new SDL_Rect{ (int)mPosition.x - mSensorSize, (int)mPosition.y + 1, mSensorSize, mHitbox->h -2};
	mSensorRight = new SDL_Rect{ (int)mPosition.x + mHitbox->w, (int)mPosition.y + 1, mSensorSize, mHitbox->h -2};
	mSensorTop = new SDL_Rect{ (int)mPosition.x + 1, (int)mPosition.y - mSensorSize, mHitbox->w - 2, mSensorSize };
	mSensorBottom = new SDL_Rect{ (int)mPosition.x + 1, (int)mPosition.y + mHitbox->h, mHitbox->w - 2, mSensorSize };
}

void Entity::UpdateSensors()
{
	mSensorLeft->x = mPosition.x - mSensorSize;
	mSensorLeft->y = mPosition.y + 1;
	mSensorRight->x = mPosition.x + mHitbox->w;
	mSensorRight->y = mPosition.y + 1;
	mSensorTop->x = mPosition.x + 1;
	mSensorTop->y = mPosition.y - mSensorSize;
	mSensorBottom->x = mPosition.x + 1;
	mSensorBottom->y = mPosition.y + mHitbox->h;
}
