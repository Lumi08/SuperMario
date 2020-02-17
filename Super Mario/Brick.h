#ifndef _BRICK_H
#define	_BRICK_H

#include <SDL.h>
#include <string>

#include "Player.h"
#include "Entity.h"
#include "PowerUp.h"
#include "Mushroom.h"
#include "Commons.h"
#include "Constants.h"

class Brick : public Entity
{
public:
	Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position);
	~Brick();
	
	void Update(float deltaTime, SDL_Event e, Player* players[]);
	void Render();
	virtual void Debug() override;
private:
	void PlayerCollisions(Player* player, int playerNum);
	void ItemCollisions();
	SDL_Rect* mSourceRect;
	PowerUp* mItemInside;
	bool mItemInsideSpawned;
	SIDE mSidePlayerHit[MAXPLAYERCOUNT];
};

#endif // !_BRICK_H


