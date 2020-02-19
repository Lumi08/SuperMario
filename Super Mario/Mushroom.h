#ifndef _MUSHROOM_H_
#define _MUSHROOM_H_

#include <SDL.h>
#include <string>

#include "PowerUp.h"
#include "Commons.h"
#include "Animation.h"
#include "Constants.h"

class Mushroom : public PowerUp
{
public:
	Mushroom(SDL_Renderer* renderer, std::string imagePath, Vector2D spawnLocation, float renderScale, FACING startDirection);
	~Mushroom();
	
	void Render();
	void Update(float deltaTime, SDL_Event e);

	
private:
	FACING mDirectionFacing;
	Animation* mMovingAnimation;
	int mStartY;
	float mMovementSpeed;
};


#endif // !_MUSHROOM_H_

