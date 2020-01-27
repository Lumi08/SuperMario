#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <SDL.h>
#include <iostream>

#include "Commons.h"

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
	Vector2D mPosition;
	Texture2D* mTexture;
	FACING mFacingDirection;

	bool mMovingLeft, 
		mMovingRight;
	float mSpeed;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
};

#endif // !_CHARACTER_H
