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

	bool CanBeRemoved() { return mRemovable; }
	bool IsAlive() { return mAlive; }

	void SetDirectionFacing(FACING facing) { mFacing = facing; };
	void SetOnPlatform(bool onPlatform) { mOnPlatform = onPlatform; }
private:

	Animation* mWalkAnimation;
	SDL_Rect* mSourceRect;
	FACING mFacing;
	float mMovementSpeed;
	bool mAlive = true,
		mOnPlatform,
		mRemovable;
	int mKilledTimer;
	
};

#endif // !_ENEMY_H



