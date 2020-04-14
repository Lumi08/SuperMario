#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>

#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Player.h"
#include "Brick.h"
#include "Mushroom.h"
#include "Constants.h"
#include "MapLoader.h"
#include "Text.h"
#include "Coin.h"
#include "Enemy.h"
#include "Flag.h"
//#include "Character.h"

class Texture2D;
//class Entity;
class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer, GameScreenManager* manager, int numOfPlayers);
	~GameScreenLevel1();

	/// Render function which is used to render all the assets on the gamescrenlevel1
	void Render();
	/// update function which is used to update all the assets on the gamescrenlevel1
	void Update(float deltaTime, SDL_Event e);
private:
	GameScreenManager* mManager;
	Texture2D* mBackgroundTexture;
	Texture2D* mMarioFace;
	Texture2D* mLuigiFace;
	Vector2D mBackgroundPosition;
	SDL_Rect* mCamera;
	Text* mScoreText;
	Text* mDebugText;
	Text* mDeathScreenText;
	Flag* mFlag;

	std::vector<Player*> mPlayers;
	std::vector<Pipe*> mPipes;
	std::vector<Brick*> mBricks;
	std::vector<Coin*> mCoins;
	std::vector<Enemy*> mEnemys;

	int mScore,
		mCoinsCollected,
		mMapTileWidth,
		mLives,
		mPlayerCount,
		mCurrentLevel;

	int mPreviousHealth[2];

	bool mResetingLevel;

	/// used to load in all the assets for the level
	bool SetUpLevel(int numOfPlayers);
	/// used to delete all necisary assets for the 
	void ClearLevel();
	/// used to call all assets debug functions
	void Debug();
	void BrickCollisionsWithPlayer(Player* player, bool& botCollided);
	void PipeCollisionsWithPlayer(Player* player, bool& botCollided);
	void CoinCollisionsWithPlayer(Player* player);
	void EnemyCollisionsWithPlayer(Player* player);
	void EnemyCollisionsWithBlocks(Enemy* enemy);
	void RemoveDestroyedBricks(Brick* brick, int brickNum);
	void RemoveDeadEnemies(Enemy* enemy, int enemyNum);
	void SpawnedItemSolidBlockCollisions(PowerUp* powerup);
	void CameraMovementLogic();
	bool FlagCollisionsWithPlayer(Player* player);

	//debug:
	int mDebugType = 0;
	bool debug = false;
	bool f3Down = false, kp2Down = false;
	bool topHit;
};

#endif // !_GAMESCREENLEVEL1_H

