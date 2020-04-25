#ifndef _POWERUP_H
#define _POWERUP_H

#include "Entity.h"
#include "Constants.h"

class PowerUp : public Entity
{
public: 
	PowerUp(SDL_Renderer* renderer, std::string imgPath, Vector2D spawnLocation, int width, int height, PowerUpType type);
	PowerUp();
	~PowerUp();

	/// Used to determine wether the powerup needs to have gravity applied to it
	void SetOnPlatform(bool isOnPlatform) { mOnPlatform = isOnPlatform; }
	bool GetOnPlatform() { return mOnPlatform; }

	void SetSpawning(bool spawning) { mSpawning = spawning; }
	bool GetSpawning() { return mSpawning; }

	PowerUpType GetType() { return mType; }

	/// Powerup main render function to render its texture and the correct anumations
	virtual void Render(SDL_Rect* camera);
	/// The power ups update function updates the correct hitpox and the position of the powerup
	virtual void Update(float deltaTime, SDL_Event e);

	void SetDirectionFacing(FACING direction) { mDirectionFacing = direction; }
	FACING GetDirectionFacing() { return mDirectionFacing; }
private:
	FACING mDirectionFacing;
	bool mSpawning,
		mOnPlatform;
	PowerUpType mType;
};

#endif // !_POWERUP_H

