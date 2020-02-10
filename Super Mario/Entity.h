#ifndef _ENTITY_H_
#define _ENTITY_H_

#define RENDERSCALE 2

#include <SDL.h>
#include <string>

#include "Commons.h"
#include "Texture2D.h"

class Texture2D;
class Entity
{
public:
	Entity(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int width, int height);
	virtual ~Entity();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void UpdateHitbox();

	virtual void Debug();
	
	SDL_Rect* GetHitbox() { return mHitbox; }
	float GetX() { return mPosition.x; }
	float GetY() { return mPosition.y; }
	int GetWidth() { return mRawWidth * RENDERSCALE; }
	int GetHeight() { return mRawHeight * RENDERSCALE; }

	void SetX(float x) { mPosition.x = x; }
	void SetY(float y) { mPosition.y = y; }
	void SetWidth(int width) { mWidth = width; }
	void SetHeight(int height) { mHeight = height; }
	

protected:
	SDL_Renderer* mRenderer;
	SDL_Rect* mHitbox;
	Texture2D* mTexture;
	Vector2D mPosition;
	SIDE mSideColliding;
	int mWidth,
		mHeight,
		mRawWidth,
		mRawHeight;
};

#endif // !_ENTITY_H_
