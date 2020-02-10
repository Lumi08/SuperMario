#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>

#include "Commons.h"
#include "GameScreen.h"
#include "Player.h"
#include "Brick.h"
#include "Mushroom.h"
#include "Constants.h"
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
	Player* mMario;
	Player*	mLuigi;
	Player* mPlayers[MAXPLAYERCOUNT];
	Brick* mBrick;
	Brick* mBrick2;

	bool SetUpLevel();
	//debug:
	bool debug = false;
};

#endif // !_GAMESCREENLEVEL1_H

