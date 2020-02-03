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

	SDL_Rect* GetHitbox();
	
	void Debug();

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
