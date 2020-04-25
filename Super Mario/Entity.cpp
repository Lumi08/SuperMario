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

Entity::Entity()
{
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
	return RectContainsRect(this->GetHitbox(), entity->GetHitbox());
}

SIDE Entity::GetSideCollidingWithEntity(Entity* entity)
{
	if (IsCollidingWith(entity))
	{
		if (RectContainsRect(mSensorLeft, entity->GetHitbox()))
		{
			//std::cerr << "Left" << std::endl;
			return SIDE::LEFT;
		}
		if (RectContainsRect(mSensorRight, entity->GetHitbox()))
		{
			//std::cerr << "Right" << std::endl;
			return SIDE::RIGHT;
		}
		if (RectContainsRect(mSensorTop, entity->GetHitbox()))
		{
			//std::cerr << "Top" << std::endl;
			return SIDE::TOP;
		}
		if (RectContainsRect(mSensorBottom, entity->GetHitbox()))
		{
			//std::cerr << "Bottom" << std::endl;
			return SIDE::BOTTOM;
		}
	}

	return SIDE::NONE;
}

void Entity::Debug(SDL_Rect* camera, int type)
{
	SDL_Rect* mDebugHitbox = new SDL_Rect {mHitbox->x - camera->x, mHitbox->y, mHitbox->w, mHitbox->h};
	
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(mRenderer, mDebugHitbox);
	
	if (type == 2)
	{
		SDL_Rect* mDebugHitboxLeft = new SDL_Rect{ mSensorLeft->x - camera->x, mSensorLeft->y, mSensorLeft->w, mSensorLeft->h };
		SDL_Rect* mDebugHitboxRight = new SDL_Rect{ mSensorRight->x - camera->x, mSensorRight->y, mSensorRight->w, mSensorRight->h };
		SDL_Rect* mDebugHitboxTop = new SDL_Rect{ mSensorTop->x - camera->x, mSensorTop->y, mSensorTop->w, mSensorTop->h };
		SDL_Rect* mDebugHitboxBottom = new SDL_Rect{ mSensorBottom->x - camera->x, mSensorBottom->y, mSensorBottom->w, mSensorBottom->h };

		SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(mRenderer, mDebugHitboxLeft);
		SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(mRenderer, mDebugHitboxRight);
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
		SDL_RenderDrawRect(mRenderer, mDebugHitboxTop);
		SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 255);
		SDL_RenderDrawRect(mRenderer, mDebugHitboxBottom);

		delete mDebugHitboxLeft;
		delete mDebugHitboxRight;
		delete mDebugHitboxTop;
		delete mDebugHitboxBottom;
	}
	
	delete mDebugHitbox;
}

void Entity::InitSensors()
{
	mSensorLeft = new SDL_Rect{ (int)mPosition.x - mSensorSize, (int)mPosition.y + 1, mSensorSize, mHitbox->h -2};
	mSensorRight = new SDL_Rect{ (int)mPosition.x + mHitbox->w, (int)mPosition.y + 1, mSensorSize, mHitbox->h -2};
	mSensorTop = new SDL_Rect{ (int)mPosition.x + 2, (int)mPosition.y - mSensorSize, mHitbox->w - 4, mSensorSize };
	mSensorBottom = new SDL_Rect{ (int)mPosition.x + 2, (int)mPosition.y + mHitbox->h, mHitbox->w - 4, mSensorSize };
}

void Entity::UpdateSensors()
{
	mSensorLeft->x = mPosition.x - mSensorSize;
	mSensorLeft->y = mPosition.y + 1;
	mSensorRight->x = mPosition.x + mHitbox->w;
	mSensorRight->y = mPosition.y + 1;
	mSensorTop->x = mPosition.x + 2;
	mSensorTop->y = mPosition.y - mSensorSize;
	mSensorBottom->x = mPosition.x + 2;
	mSensorBottom->y = mPosition.y + mHitbox->h;
}

void Entity::FullUpdateSensors()
{
	mSensorLeft->x = mPosition.x - mSensorSize;
	mSensorLeft->y = mPosition.y + 1;
	mSensorLeft->h = mHitbox->h - 2;
	mSensorRight->x = mPosition.x + mHitbox->w;
	mSensorRight->y = mPosition.y + 1;
	mSensorRight->h = mHitbox->h - 2;
	mSensorTop->x = mPosition.x + 2;
	mSensorTop->y = mPosition.y - mSensorSize;
	mSensorTop->w = mHitbox->w - 4;
	mSensorBottom->x = mPosition.x + 2;
	mSensorBottom->y = mPosition.y + mHitbox->h;
	mSensorBottom->w = mHitbox->w - 4;
}
