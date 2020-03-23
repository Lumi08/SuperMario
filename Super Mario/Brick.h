#ifndef _BRICK_H
#define	_BRICK_H

#include <SDL.h>
#include <string>
#include <vector>

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
	Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position, BrickType brickType, int coinsInside);
	~Brick();

	void Destroy();
	void Hit(int playerHealth);

	void Update(float deltaTime, SDL_Event e, std::vector<Player*>& players, int & score, int & coinsCollected);
	void Render(SDL_Rect* camera);
	
	virtual void Debug(SDL_Rect* camera, int type) override;

	BrickType GetBrickType() { return mBrickType; }
	void SetBrickType(BrickType type) { mBrickType = type; }
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
	Animation* mCoinReleased;
	bool mItemInsideSpawned,
		mBeenHit,
		mDestroyed,
		mBouncing,
		mBouncingUp,
		mCoinsInside;
	float mDestroyFallForce,
		mDestroySeperation,
		mDestroyAngle;
	int mBouncingStartY,
		mNumCoinsInside;

	void ItemCollisions(Player* player, int& score);
	void PerformBrickBounce();
};

#endif // !_BRICK_H


