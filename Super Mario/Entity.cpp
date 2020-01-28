#include "Entity.h"
#include "Texture2D.h"

Entity::Entity(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition)
{
	mRenderer = renderer;
	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
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
