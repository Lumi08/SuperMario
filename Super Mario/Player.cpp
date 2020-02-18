#include "Entity.h"
#include "Player.h"
#include "Texture2D.h"

Player::Player(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int playerNum) 
	: Entity(renderer, imagePath, startPosition, SMALLPLAYERWIDTH, SMALLPLAYERHEIGHT)
{
	mPlayerNumber = playerNum;
	mMovementSpeed = 0.05;
	mHealth = 1;
	mFadeTime = 0;
	mTimeIdle = 0;
	mPlayerState = IDLE;
	mDirectionFacing = FACING_RIGHT;
	mSourceRect = new SDL_Rect{ 0, 0, SMALLPLAYERWIDTH, SMALLPLAYERHEIGHT };
	mWalkAnimation = new Animation(renderer, mTexture, new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 2, 500, RENDERSCALE);
	mIdleAnimation = new Animation(renderer, mTexture, new SDL_Rect{ 0, 32, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 2, 5000, RENDERSCALE);
	mSleepAnimation = new Animation(renderer, mTexture, new SDL_Rect{ 0, 16, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 6, 1000, RENDERSCALE);
	mOnPlatform = false;
	//mSleepAnimation->SetLoopStartSprite(4);
}

Player::~Player()
{
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
				case FACING_RIGHT:
				{
					mWalkAnimation->Play(mPosition, SDL_FLIP_HORIZONTAL);
					break;
				}

				case FACING_LEFT:
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
				case FACING_RIGHT:
				{
					mIdleAnimation->Play(mPosition, SDL_FLIP_HORIZONTAL);
					break;
				}
				case FACING_LEFT:
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
				case FACING_RIGHT:
				{
					mSleepAnimation->Play(mPosition, SDL_FLIP_HORIZONTAL);
					break;
				}
				case FACING_LEFT:
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
				case FACING_RIGHT:
				{
					mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL, RENDERSCALE, 0.0f, mSourceRect);
					break;
				}

				case FACING_LEFT:
				{	
					mTexture->Render(mPosition, SDL_FLIP_NONE, RENDERSCALE, 0.0f, mSourceRect);
					break;
				}
			}
			break;
		}
	}
}

void Player::Update(float deltaTime, SDL_Event e)
{
	/*if (mPlayerNumber == 1)
	{
		std::cout << "Mario X:" << mPosition.x << " Y:" << mPosition.y << std::endl;
	}*/
	MovementLogic(deltaTime);
	FadeLogic();
	
	if (mJumping)
	{
		mPosition.y -= mJumpForce * deltaTime;
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;
	}
	
	if (mPosition.y < SCREEN_HEIGHT - mHitbox->h && !mOnPlatform)
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
			case SDLK_u:
			{
				UpdateHealth(-1);
				break;
			}
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
		mDirectionFacing = FACING_LEFT;

		if (!mJumping)
		{
			mPlayerState = WALK;
		}
		mTimeIdle = 0;
	}
	else if (mMovingRight)
	{
		mPosition.x += mMovementSpeed;
		mDirectionFacing = FACING_RIGHT;
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
			mSourceRect->x = 80;
		}
		else
		{
			mSourceRect->x = 64;
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

	UpdateHitbox();
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

void Player::UpdateHealth(int changeInHealth)
{
	mHealth = mHealth + changeInHealth;

	switch (mHealth)
	{
		case 0:
		{
			break;
		}

		case 1:
		{
			mSourceRect->y = 0;
			mSourceRect->h = 16;
			mHitbox->h = 16 * RENDERSCALE;
			mFading = true;
			mPosition.y += 16 * RENDERSCALE;
			mWalkAnimation = new Animation(mRenderer, mTexture, new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 2, 500, RENDERSCALE);
			mIdleAnimation = new Animation(mRenderer, mTexture, new SDL_Rect{ 0, 32, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 2, 5000, RENDERSCALE);
			mSleepAnimation = new Animation(mRenderer, mTexture, new SDL_Rect{ 0, 16, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 6, 1000, RENDERSCALE);
			break;
		}

		case 2:
		{
			mSourceRect->y = 64;
			mSourceRect->h = 32;
			mPosition.y -= 16 * RENDERSCALE;
			mWalkAnimation = new Animation(mRenderer, mTexture, new SDL_Rect{ 0, 64, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT * 2 }, 2, 500, RENDERSCALE);
			mIdleAnimation = new Animation(mRenderer, mTexture, new SDL_Rect{ 0, 96, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT * 2}, 2, 5000, RENDERSCALE);
			mSleepAnimation = new Animation(mRenderer, mTexture, new SDL_Rect{ 0, 16, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 6, 1000, RENDERSCALE);
			mHitbox->h = 32 * RENDERSCALE;
			mFading = true;
			break;
		}
	}
}

void Player::FadeLogic()
{
	if (mFading)
	{
		float result = ((0.5 * cos(mFadeDegrees * 3.14159265 / 180.0)) + 0.5) * 255;
		mFadeDegrees += 0.15;

		if (mFadeTime > 5000 && mFadeDegrees >= 360)
		{
			mFading = false;
			mFadeTime = 0;
		}
		else
		{
			SDL_SetTextureAlphaMod(mTexture->GetTexture(), result);
			mFadeTime++;
		}

		if (mFadeDegrees >= 360.0)
		{
			mFadeDegrees = 0.0;
		}
	}
}

