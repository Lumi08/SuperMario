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

	/// For when the brick has been destroyed by the player
	void Destroy();
	/// For when the player hits the bricks underside
	void Hit(int playerHealth);

	/// Updates all the logic for the brick
	void Update(float deltaTime, SDL_Event e, std::vector<Player*>& players, int & score, int & coinsCollected);
	/// Renders the images and the animations for the bricks
	void Render(SDL_Rect* camera);
	
	/// Used to debuig the bricks hitboxes
	virtual void Debug(SDL_Rect* camera, int type) override;

	/// Gets the type of brick, used to determine wether to spawn an item or to break ect.
	BrickType GetBrickType() { return mBrickType; }
	/// Used to set the brick type, for example when mario hits a block with an item in it becomes a solid brick and shouldnt react or break when hit
	void SetBrickType(BrickType type) { mBrickType = type; }
	/// Gets the side of the brick which has been hit
	SIDE GetSideHit() { return mSideHit; }
	/// Sets the side which has been hit
	void SetSideHit(SIDE side) { mSideHit = side; }
	/// Gets the item inside if there is one 
	PowerUp* GetItemInside() { return mItemInside; }
	/// Sets the item inside of the bricks
	void SetItemInside(PowerUp* itemInside) { mItemInside = itemInside; }
	/// Checks whether the item inside has been spawned
	bool GetItemInsideSpawned() { return mItemInsideSpawned; }
	/// Set if the item inside has been spawned
	void SetItemInsideSpawned(bool spawned) { mItemInsideSpawned = spawned; }
	/// Gets whether the brick has been destroyed, useful for deleting destroyed bricks
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


