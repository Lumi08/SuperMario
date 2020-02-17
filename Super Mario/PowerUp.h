#ifndef _POWERUP_H
#define _POWERUP_H

#include "Entity.h"
#include "Constants.h"

class PowerUp : public Entity
{
public: 
	PowerUp(SDL_Renderer* renderer, std::string imgPath, Vector2D spawnLocation, int width, int height);
	~PowerUp();

	void SetOnPlatform(bool isOnPlatform) { mOnPlatform = isOnPlatform; }
	bool GetOnPlatform() { return mOnPlatform; }

	void SetSpawning(bool spawning) { mSpawning = spawning; }
	bool GetSpawning() { return mSpawning; }

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	bool mSpawning,
		mOnPlatform;
};

#endif // !_POWERUP_H

