#include "Entity.h"
#include "Player.h"
#include "Texture2D.h"

Player::Player(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, float renderScale, int playerNum) 
	: Entity(renderer, imagePath, startPosition, SMALLCHARACTERHEIGHT, SMALLCHARACTERWIDTH, renderScale)
{
	mPlayerNumber = playerNum;
	mMovementSpeed = 0.05;
	mPlayerState = IDLE;
	mDirectionFacing = RIGHT;
	mSourceRect = new SDL_Rect{ 0, 0, 16, 16 };
	mWalkAnimation = new Animation(renderer, mTexture, new SDL_Rect{ 0, 0, 16, 16 }, 2, 500, mRenderScale);
	mIdleAnimation = new Animation(renderer, mTexture, new SDL_Rect{ 0, 32, 16, 16 }, 2, 5000, mRenderScale);
	mSleepAnimation = new Animation(renderer, mTexture, new SDL_Rect{ 0, 16, 16, 16 }, 6, 1000, mRenderScale);
	mOnPlatform = false;
	//mSleepAnimation->SetLoopStartSprite(4);
}

Player::~Player()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	delete mWalkAnimation;
	delete mIdleAnimation;
	delete mSleepAnimation;
}

void Player::Render()
{
	
	switch (mPlayerState)
	{
		case WALK:
		{
			switch (mDirectionFacing)
			{
				case RIGHT:
				{
					mWalkAnimation->Play(mPosition, SDL_FLIP_HORIZONTAL);
					break;
				}

				case LEFT:
				{
					mWalkAnimation->Play(mPosition, SDL_FLIP_NONE);
					break;
				}
			}
			break;
		}

		case IDLE:
		{
			switch (mDirectionFacing)
			{
				case RIGHT:
				{
					mIdleAnimation->Play(mPosition, SDL_FLIP_HORIZONTAL);
					break;
				}
				case LEFT:
				{
					mIdleAnimation->Play(mPosition, SDL_FLIP_NONE);
					break;
				}
			}
			break;
		}

		case SLEEP:
		{
			switch (mDirectionFacing)
			{
				case RIGHT:
				{
					mSleepAnimation->Play(mPosition, SDL_FLIP_HORIZONTAL);
					break;
				}
				case LEFT:
				{
					mSleepAnimation->Play(mPosition, SDL_FLIP_NONE);
					break;
				}
			}
			break;
		}

		case JUMP:
		{
			switch (mDirectionFacing)
			{
				case RIGHT:
				{
					mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL, mRenderScale, 0.0f, mSourceRect);
					break;
				}

				case LEFT:
				{	
					mTexture->Render(mPosition, SDL_FLIP_NONE, mRenderScale, 0.0f, mSourceRect);
					break;
				}
			}
			break;
		}
	}
}

void Player::Update(float deltaTime, SDL_Event e)
{
	/*if (mPlayerNumber == 2)
	{
		std::cout << "Luigi : " << mPlayerState << std::endl;
	}*/
	MovementLogic(deltaTime);
	
	if (mJumping)
	{
		mPosition.y -= mJumpForce * deltaTime;
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;
	}
	
	if (mPosition.y < SCREEN_HEIGHT - mHeight && !mOnPlatform)
	{
		mJumping = true;
		mPosition.y += GRAVITY * deltaTime;
	}
	else 
	{
		mJumping = false;
	}
	
	switch (e.type)
	{
		case SDL_KEYDOWN:
		{
			switch (e.key.keysym.sym)
			{
				
				case SDLK_a:
				{
					if (mPlayerNumber == 1)
					{
						mMovingLeft = true;
					}
					break;
				}

				case SDLK_d:
				{
					if (mPlayerNumber == 1)
					{
						mMovingRight = true;
					}
					break;
				}

				case SDLK_w:
				{
					if (mPlayerNumber == 1)
					{
						mJumpKeyPressed = true;
					}
					break;
				}
				
				case SDLK_LEFT:
				{
					if (mPlayerNumber == 2)
					{
						mMovingLeft = true;
					}
					break;
				}

				case SDLK_RIGHT:
				{
					if (mPlayerNumber == 2)
					{
						mMovingRight = true;
					}
					break;
				}
				
				case SDLK_UP:
				{
					if (mPlayerNumber == 2)
					{
						mJumpKeyPressed = true;
					}
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
					if (mPlayerNumber == 1)
					{
						mMovingLeft = false;
					}
					break;
				}

				case SDLK_d:
				{
					if (mPlayerNumber == 1)
					{
						mMovingRight = false;
					}
					break;
				}
				
				case SDLK_w:
				{
					if (mPlayerNumber == 1)
					{
						mJumpKeyPressed = false;
					}
					break;
				}
				
				
				case SDLK_LEFT:
				{
					if (mPlayerNumber == 2)
					{
						mMovingLeft = false;
					}
					break;
				}

				case SDLK_RIGHT:
				{
					if (mPlayerNumber == 2)
					{
						mMovingRight = false;
					}
					break;
				}	

				case SDLK_UP:
				{
					if (mPlayerNumber == 2)
					{
						mJumpKeyPressed = false;
					}
					break;
				}
			}
			break;
		}
	}
}

void Player::MovementLogic(float deltaTime)
{
	if (mJumpKeyPressed || mJumping)
	{
		Jump();
		mTimeIdle = 0;
	}
	if (mMovingLeft)
	{
		mPosition.x -= mMovementSpeed;
		mDirectionFacing = LEFT;

		if (!mJumping)
		{
			mPlayerState = WALK;
		}
		mTimeIdle = 0;
	}
	else if (mMovingRight)
	{
		mPosition.x += mMovementSpeed;
		mDirectionFacing = RIGHT;
		if (!mJumping)
		{
			mPlayerState = WALK;
		}
		mTimeIdle = 0;
	}
	else
	{
		if (!mJumping)
		{
			mTimeIdle++;
			mPlayerState = IDLE;
		}
	}

	if (mJumping)
	{
		if (mJumpForce < 100)
		{
			mSourceRect->x = 64;
		}
		else
		{
			mSourceRect->x = 48;
		}
	}
	else
	{
		mSourceRect->x = 0;
	}

	if (mTimeIdle > 100000)
	{
		mPlayerState = SLEEP;
	}

	UpdateHitbox(mPosition, mWidth, mHeight);
}

void Player::Jump()
{
	if (!mJumping)
	{
		mOnPlatform = false;
		mPlayerState = JUMP;
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
	}
}

