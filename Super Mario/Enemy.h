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

	/// Renders the enemy and the animations for the enemy 
	void Render(SDL_Rect* camera);
	/// Updates all the info for the enemy, pos hitbox ect.
	void Update(float deltaTime, SDL_Event e);

	/// Used for when the enemy has been killed by a player.
	void Killed();
	/// Checks if the enemy can be removed from the vector making the game that tad more efficient
	bool CanBeRemoved() { return mRemovable; }
	/// Returns wether the enemy is alive
	bool IsAlive() { return mAlive; }
	/// Sets the direction for the enemy ultimately determining the direction they will move
	void SetDirectionFacing(FACING facing) { mFacing = facing; };
	/// Sets if the enemy is on a platform meaning they will not take gravity and fall
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



