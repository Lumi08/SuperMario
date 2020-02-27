#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>

#include "Commons.h"
#include "GameScreen.h"
#include "Player.h"
#include "Brick.h"
#include "Mushroom.h"
#include "Constants.h"
#include "MapLoader.h"
//#include "Character.h"

class Texture2D;
//class Entity;
class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	Texture2D* mBackgroundTexture;
	Player* mPlayers[MAXPLAYERCOUNT];
	Brick* mBricks[MAXBRICKCOUNT];
	int mBrickCount,
		mPlayerCount;

	bool SetUpLevel();
	void BrickCollisionsWithPlayer();
	//debug:
	int debugType = 0;
	bool debug = false;
	bool f3Down = false, kp2Down = false;
	bool topHit;
};

#endif // !_GAMESCREENLEVEL1_H

