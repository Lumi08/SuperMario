#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <SDL.h>
#include <iostream>

#include "Commons.h"
#include "Animation.h"

class Texture2D;
class Character
{
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

protected:
	SDL_Renderer* mRenderer;
	SDL_Rect* mSourceRect;
	Vector2D mPosition;
	Texture2D* mTexture;
	Animation* walkAnimation;
	FACING mFacingDirection;

	bool mMovingLeft, 
		mMovingRight;
	float mSpeed;
	int mWalkingFrameCount;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	void AnimTick(float deltaTime);
};

#endif // !_CHARACTER_H
