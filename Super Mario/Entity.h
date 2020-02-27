#ifndef _ENTITY_H_
#define _ENTITY_H_


#include <SDL.h>
#include <string>

#include "Constants.h"
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
	void UpdateSensors();
	
	bool IsCollidingWith(Entity* entity);
	SIDE GetSideCollidingWithEntity(Entity* entity);

	virtual void Debug(int type);
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

	int mSensorSize;
	SDL_Rect* mSensorLeft;
	SDL_Rect* mSensorRight;
	SDL_Rect* mSensorTop;
	SDL_Rect* mSensorBottom;

	Texture2D* mTexture;
	Vector2D mPosition;
	int mWidth,
		mHeight,
		mRawWidth,
		mRawHeight;

	void InitSensors();
};

#endif // !_ENTITY_H_
