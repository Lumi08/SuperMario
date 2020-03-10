#ifndef _BRICK_H
#define	_BRICK_H

#include <SDL.h>
#include <string>

#include "Player.h"
#include "Entity.h"
#include "PowerUp.h"
#include "Mushroom.h"
#include "FireFlower.h"
#include "Commons.h"
#include "Constants.h"
#include "Animation.h"

class Brick : public Entity
{
public:
	Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position, BrickType brickType);
	Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position, BrickType brickType, PowerUp* itemInside);
	~Brick();

	void Destroy();
	void Hit(int playerHealth);

	void Update(float deltaTime, SDL_Event e, Player* players[], int playerCount);
	void Render();
	virtual void Debug(int type) override;

	BrickType GetBrickType() { return mBrickType; }
	SIDE GetSideHit() { return mSideHit; }
	void SetSideHit(SIDE side) { mSideHit = side; }
	PowerUp* GetItemInside() { return mItemInside; }
	void SetItemInside(PowerUp* itemInside) { mItemInside = itemInside; }
	bool GetItemInsideSpawned() { return mItemInsideSpawned; }
	void SetItemInsideSpawned(bool spawned) { mItemInsideSpawned = spawned; }
	bool GetDestroyed() { return mDestroyed; }
private:
	SDL_Rect* mSourceRect;
	PowerUp* mItemInside;
	BrickType mBrickType;
	SIDE mSideHit;
	Animation* mIdleAnimation = NULL;
	bool mItemInsideSpawned,
		mBeenHit,
		mDestroyed,
		mBouncing;
	float mDestroyFallForce,
		mDestroySeperation,
		mDestroyAngle;

	void ItemCollisions(Player* player);
};

#endif // !_BRICK_H


