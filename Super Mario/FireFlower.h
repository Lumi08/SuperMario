#ifndef _FIREFLOWER_H
#define _FIRFLOWER_H

#include <SDL.h>
#include "PowerUp.h"
#include "Animation.h"
#include "Constants.h"

class FireFlower : public PowerUp
{
public:
	FireFlower(SDL_Renderer* renderer, std::string imagePath, Vector2D spawnLocation, float renderScale);
	~FireFlower();

	/// used to render the fireflowers animation and texture
	void Render(SDL_Rect* camera) override;
	/// used to update the fire flowers position as it doesnt scroll with the camera
	void Update(float deltaTime, SDL_Event e) override;

private:
	Animation* mIdleAnimation;
	int mStartY;
};


#endif // !_FIREFLOWER_H

