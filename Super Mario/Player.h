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

class Player : public Entity
{
public:
	Player(SDL_Renderer* renderer, std::string imagepath, Vector2D startPosition, int playerNum);
	~Player();

	void Render();
	void Update(float deltaTime, SDL_Event e);

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
	float mMovementSpeed;
	bool mMovingLeft,
		mMovingRight;
	FACING mDirectionFacing;
	Animation* mWalkAnimation;
	Animation* mSleepAnimation;
	Animation* mIdleAnimation;
	SDL_Rect* mSourceRect;
	PlayerState mPlayerState;

	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);

	
};

#endif // !_PLAYER_H_


