#include "Entity.h"
#include "Player.h"
#include "Texture2D.h"

Player::Player(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int playerNum) 
	: Entity(renderer, imagePath, startPosition)
{
	mPlayerNumber = playerNum;
	mDirectionFacing = RIGHT;
	mMovementSpeed = 0.05;
	mSourceRect = new SDL_Rect{ 0, 32, 16, 27 };
	this->walkAnimation = new Animation(renderer, imagePath, mSourceRect, 3, 300);
}

Player::~Player()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
}

void Player::Render()
{
	switch (mDirectionFacing)
	{
		case RIGHT:
		{
			mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL, 0.0f, mSourceRect);
			break;
		}
		case LEFT:
		{
			mTexture->Render(mPosition, SDL_FLIP_NONE, 0.0f, mSourceRect);
			break;
		}
	}
}

void Player::Update(float deltaTime, SDL_Event e)
{
	

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
	}

	switch (e.type)
	{
		case SDL_KEYDOWN:
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_a:
				{
					mMovingLeft = true;
					break;
				}

				case SDLK_d:
				{
					mMovingRight = true;
					break;
				}
			}
			break;
		}

		case SDL_KEYUP:
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
			{
				mMovingLeft = false;
				break;
			}

			case SDLK_d:
			{
				mMovingRight = false;
				break;
			}
			}
			break;
		}
	}
}

void Player::MoveLeft(float deltaTime)
{
	mPosition.x -= mMovementSpeed;
	mDirectionFacing = LEFT;
	walkAnimation->Play(mPosition, SDL_FLIP_NONE, 0.0f);
	//AnimTick(deltaTime);
}

void Player::MoveRight(float deltaTime)
{
	mPosition.x += mMovementSpeed;
	mDirectionFacing = RIGHT;
	walkAnimation->Play(mPosition, SDL_FLIP_HORIZONTAL, 0.0f);
	//AnimTick(deltaTime);
}
