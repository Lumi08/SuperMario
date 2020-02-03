#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL.h>
#include <string>
#include "Constants.h"
#include "Animation.h"
#include "Entity.h"

#define SMALLCHARACTERWIDTH 16
#define SMALLCHARACTERHEIGHT 16
#define BIGCHARACTERWIDTH 30
#define BIGCHARACTERHEIGHT 27
#define GRAVITY 100.0f

#define JUMP_FORCE_DECREMENT 600.0f
#define INITIAL_JUMP_FORCE 500.0f

class Player : public Entity
{
public:
	Player(SDL_Renderer* renderer, std::string imagepath, Vector2D startPosition, float renderScale, int playerNum);
	~Player();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void SetOnPlatform(bool isOnPlatform) { mOnPlatform = isOnPlatform; };
	bool GetOnPlatform() { return mOnPlatform; }
private:
	enum PlayerState
	{
		WALK = 0,
		JUMP,
		IDLE,
		SLEEP
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

	void MovementLogic(float deltaTime);
	void Jump();
};

#endif // !_PLAYER_H_


