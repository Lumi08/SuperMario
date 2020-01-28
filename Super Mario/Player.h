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

private:
	int mPlayerNumber;
	float mMovementSpeed;
	bool mMovingLeft,
		mMovingRight;
	FACING mDirectionFacing;
	Animation* walkAnimation;
	SDL_Rect* mSourceRect;

	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
};

#endif // !_PLAYER_H_


