#ifndef _ENEMY_H
#define _ENEMY_H

#include <SDL.h>
#include "Entity.h"
#include "Animation.h"

class Enemy : public Entity
{
public:
	Enemy(SDL_Renderer* renderer, std::string imgPath, Vector2D spawnLocation);
	~Enemy();

	void Render(SDL_Rect* camera);
	void Update(float deltaTime, SDL_Event e);
	void Killed();
private:

	Animation* mWalkAnimation;
	SDL_Rect* mSourceRect;
	FACING mFacing;
	float mMovementSpeed;
	bool mAlive = true;
	
};

#endif // !_ENEMY_H



