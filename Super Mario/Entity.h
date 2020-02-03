#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SDL.h>
#include <string>

#include "Commons.h"

class Texture2D;
class Entity
{
public:
	Entity(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int width, int height, float renderScale);
	~Entity();

	virtual void Render();
	virtual void Update();
	void UpdateHitbox(Vector2D position, int width, int height);

	void Debug();
	
	SDL_Rect* GetHitbox() { return mHitbox; }
	float GetX() { return mPosition.x; }
	float GetY() { return mPosition.y; }
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

	void SetX(float x) { mPosition.x = x; }
	void SetY(float y) { mPosition.y = y; }
	void SetWidth(int width) { mWidth = width; }
	void SetHeight(int height) { mHeight = height; }

protected:
	SDL_Renderer* mRenderer;
	SDL_Rect* mHitbox;
	Texture2D* mTexture;
	Vector2D mPosition;
	float mRenderScale;
	int mWidth,
		mHeight;
};

#endif // !_ENTITY_H_
