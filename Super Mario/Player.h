#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL.h>
#include <string>
#include <math.h>
#include "Constants.h"
#include "Animation.h"
#include "Entity.h"

class Player : public Entity
{
public:
	Player(SDL_Renderer* renderer, std::string imagepath, Vector2D startPosition, int playerNum);
	~Player();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void UpdateHealth(int changeInHealth);
	void SetOnPlatform(bool isOnPlatform) { mOnPlatform = isOnPlatform; };
	void SetJumpForce(float jumpForce) { mJumpForce = jumpForce; }
	void SetJumping(bool jumping) { mJumping = jumping; }

	int GetHealth() { return mHealth; }
	bool GetOnPlatform() { return mOnPlatform; }

	SIDE GetSideHit() { return mSideHit; }
	void SetSideHit(SIDE side) { mSideHit = side; }
private:
	enum PlayerState
	{
		WALK = 0,
		JUMP,
		IDLE,
		SLEEP
	};

	int mPlayerNumber,
		mTimeIdle,
		mHealth,
		mFadeTime;
	float mMovementSpeed,
		mJumpForce,
		mFadeDegrees;
	bool mMovingLeft,
		mMovingRight,
		mJumpKeyPressed,
		mJumping,
		mOnPlatform,
		mFading;
	FACING mDirectionFacing;
	Animation* mWalkAnimation;
	Animation* mSleepAnimation;
	Animation* mIdleAnimation;
	SDL_Rect* mSourceRect;
	PlayerState mPlayerState;
	SIDE mSideHit;

	void FadeLogic();
	void MovementLogic(float deltaTime);
	void Jump();
};

#endif // !_PLAYER_H_


