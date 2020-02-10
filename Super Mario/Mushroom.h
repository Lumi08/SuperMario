#ifndef _MUSHROOM_H_
#define _MUSHROOM_H_

#include <SDL.h>
#include <string>

#include "Entity.h"
#include "Commons.h"
#include "Animation.h"
#include "Constants.h"

class Mushroom : public Entity
{
public:
	Mushroom(SDL_Renderer* renderer, std::string imagePath, Vector2D spawnLocation, float renderScale, FACING startDirection);
	~Mushroom();
	
	void Render();
	void Update(float deltaTime, SDL_Event e);

	void SetOnPlatform(bool isOnPlatform) { mOnPlatform = isOnPlatform; }
	bool GetOnPlatform() { return mOnPlatform; }
private:
	SDL_Rect* mSourceRect;
	FACING mDirectionFacing;
	Animation* mMovingAnimation;
	bool mSpawning,
		mOnPlatform;
	int mStartY;
};


#endif // !_MUSHROOM_H_

