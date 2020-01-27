#include "Character.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition)
{
	this->mRenderer = renderer;
	this->mTexture = new Texture2D(renderer);
	this->mTexture->LoadFromFile(imagePath);
}

Character::~Character()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
}

void Character::Render()
{
	mTexture->Render(mPosition, SDL_FLIP_NONE, 0.0f);
}

void Character::Update(float deltaTime, SDL_Event e)
{
	SDL_PollEvent(&e);

	switch (e.type)
	{
		case SDL_KEYDOWN:
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_a:
				{
					this->mPosition.x -= 1;
					break;
				}

				case SDLK_d:
				{
					this->mPosition.x += 1;
					break;
				}
			}
			break;
		}
	}
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}
