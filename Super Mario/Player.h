#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL.h>
#include <string>
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

	void SetOnPlatform(bool isOnPlatform) { mOnPlatform = isOnPlatform; };
	void SetJumpForce(float jumpForce) { mJumpForce = jumpForce; }
	bool GetOnPlatform() { return mOnPlatform; }
private:
	enum PlayerState
	{
		WALK = 0,
		JUMP,
		IDLE,
		SLEEP
	};

	enum PlayerHealthState
	{
		DEAD = 0,
		SMALLMARIO,
		BIGMARIO,
		POWERUPMARIO
	};

	int mPlayerNumber,
		mTimeIdle = 0;
	float mMovementSpeed,
		mJumpForce;
	bool mMovingLeft,
		mMovingRight,
		mJumpKeyPressed,
		mJumping,
		mOnPlatform;
	FACING mDirectionFacing;
	Animation* mWalkAnimation;
	Animation* mSleepAnimation;
	Animation* mIdleAnimation;
	SDL_Rect* mSourceRect;
	PlayerState mPlayerState;
	PlayerHealthState mPlayerHealthState;

	void MovementLogic(float deltaTime);
	void Jump();
};

#endif // !_PLAYER_H_


