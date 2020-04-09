#include "Entity.h"
#include "Player.h"
#include "Texture2D.h"

Player::Player(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int playerNum) 
	: Entity(renderer, imagePath, startPosition, SMALLPLAYERWIDTH, SMALLPLAYERHEIGHT)
{
	mPlayerNumber = playerNum;
	mMovementSpeed = 0.25;
	mHealth = 1;
	mFadeTime = 0;
	mTimeIdle = 0;
	mPlayerState = IDLE;
	mSideHit = NONE;
	mDirectionFacing = FACING_RIGHT;
	mSourceRect = new SDL_Rect{ 0, 0, SMALLPLAYERWIDTH, SMALLPLAYERHEIGHT };
	mWalkAnimation = new Animation(renderer, mTexture, new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 2, 200, RENDERSCALE);
	mIdleAnimation = new Animation(renderer, mTexture, new SDL_Rect{ 0, 32, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 2, 2000, RENDERSCALE);
	mSleepAnimation = new Animation(renderer, mTexture, new SDL_Rect{ 0, 16, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 6, 1000, RENDERSCALE);
	mOnPlatform = true;
	//mScoreText = new Text(mRenderer, )
}

Player::~Player()
{
	delete mWalkAnimation;
	delete mIdleAnimation;
	delete mSleepAnimation;
}

void Player::Render(SDL_Rect* camera)
{
	switch (mPlayerState)
	{
		case WALK:
		{
			switch (mDirectionFacing)
			{
				case FACING_RIGHT:
				{
					mWalkAnimation->Play(mPosition, SDL_FLIP_HORIZONTAL, camera);
					break;
				}

				case FACING_LEFT:
				{
					mWalkAnimation->Play(mPosition, SDL_FLIP_NONE, camera);
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
					mIdleAnimation->Play(mPosition, SDL_FLIP_HORIZONTAL, camera);
					break;
				}
				case FACING_LEFT:
				{
					mIdleAnimation->Play(mPosition, SDL_FLIP_NONE, camera);
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
					mSleepAnimation->Play(mPosition, SDL_FLIP_HORIZONTAL, camera);
					break;
				}
				case FACING_LEFT:
				{
					mSleepAnimation->Play(mPosition, SDL_FLIP_NONE, camera);
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
					mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL, RENDERSCALE, camera, 0.0f, mSourceRect);
					break;
				}

				case FACING_LEFT:
				{	
					mTexture->Render(mPosition, SDL_FLIP_NONE, RENDERSCALE, camera, 0.0f, mSourceRect);
					break;
				}
			}
			break;
		}

		case DEAD:
		{
			mTexture->Render(mPosition, SDL_FLIP_NONE, RENDERSCALE, camera, 0.0f, mSourceRect);
		}
	}
}

void Player::Update(float deltaTime, SDL_Event e)
{
	if (mPlayerState != DEAD)
	{
		MovementLogic(deltaTime);
		FadeLogic();

		if (mJumping)
		{
			mPosition.y -= mJumpForce * deltaTime;
			mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;
		}

		if (!mOnPlatform)
		{
			//std::cerr << "adding gravity" << std::endl;
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
					case SDLK_y:
					{
						UpdateHealth(1);
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
	else
	{
		mPosition.y -= mJumpForce * deltaTime;
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;
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
	UpdateSensors();
}

void Player::Jump()
{
	if (!mJumping)
	{
		mOnPlatform = false;
		mPlayerState = JUMP;
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mSideHit = NONE;
	}
}

void Player::UpdateHealth(int changeInHealth)
{
	if (mHealth != 0)
	{
		mHealth = mHealth + changeInHealth;
	}

	switch (mHealth)
	{
		case 0:
		{
			mSourceRect->x = 112;
			mSourceRect->y = 0;
			mPlayerState = DEAD;
			mJumpForce = 500;
			break;
		}

		case 1:
		{
			mSourceRect->y = 0;
			mSourceRect->h = 16;
			mHitbox->h = DEFAULTTILEHEIGHT * RENDERSCALE;
			mFading = true; 
			mPosition.y += DEFAULTTILEHEIGHT * RENDERSCALE;
			mWalkAnimation = new Animation(mRenderer, mTexture, new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 2, 200, RENDERSCALE);
			mIdleAnimation = new Animation(mRenderer, mTexture, new SDL_Rect{ 0, 32, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 2, 5000, RENDERSCALE);
			mSleepAnimation = new Animation(mRenderer, mTexture, new SDL_Rect{ 0, 16, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 6, 1000, RENDERSCALE);
			FullUpdateSensors();
			break;
		}

		case 2:
		{
			mSourceRect->y = 64;
			mSourceRect->h = BIGPLAYERHEIGHT;
			mPosition.y -= DEFAULTTILEHEIGHT * RENDERSCALE;
			mWalkAnimation = new Animation(mRenderer, mTexture, new SDL_Rect{ 0, 64, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT * 2 }, 2, 200, RENDERSCALE);
			mIdleAnimation = new Animation(mRenderer, mTexture, new SDL_Rect{ 0, 96, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT * 2}, 2, 5000, RENDERSCALE);
			mSleepAnimation = new Animation(mRenderer, mTexture, new SDL_Rect{ 0, 16, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 6, 1000, RENDERSCALE);
			mHitbox->h = BIGPLAYERHEIGHT * RENDERSCALE;
			FullUpdateSensors();
			mFading = true;
			break;
		}

		case 3:
		{
			if (changeInHealth == 2)
			{
				mPosition.y -= DEFAULTTILEHEIGHT * RENDERSCALE;
			}
			mSourceRect->y = 128;
			mWalkAnimation = new Animation(mRenderer, mTexture, new SDL_Rect{ 0, 128, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT * 2 }, 2, 200, RENDERSCALE);
			mIdleAnimation = new Animation(mRenderer, mTexture, new SDL_Rect{ 0, 160, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT * 2 }, 2, 5000, RENDERSCALE);
			mSleepAnimation = new Animation(mRenderer, mTexture, new SDL_Rect{ 0, 16, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 6, 1000, RENDERSCALE);
			mFading = true;
			mSourceRect->h = BIGPLAYERHEIGHT;
			mHitbox->h = BIGPLAYERHEIGHT * RENDERSCALE;
			FullUpdateSensors();
			break;
			break;
		}
	}
}

void Player::FadeLogic()
{
	if (mFading)
	{
		float result = ((0.5 * cos(mFadeDegrees * 3.14159265 / 180.0)) + 0.5) * 255;
		mFadeDegrees += 0.3;

		if (mFadeTime > 2000 && mFadeDegrees >= 360)
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

void Player::DisplayText()
{

}

