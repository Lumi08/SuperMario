#ifndef _MAPLOADER_H
#define _MAPLOADER_H

#include <SDL.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Constants.h"
#include "Player.h"
#include "Brick.h"
#include "Pipe.h"
#include "Coin.h"
#include "Enemy.h"

class MapLoader
{
public:
	MapLoader(char* path, SDL_Renderer* renderer);
	~MapLoader();

	void LoadMapAssets(std::vector<Player*>& players, std::vector<Brick*>& bricks, std::vector<Pipe*>& pipes, std::vector<Coin*>& coins, std::vector<Enemy*>& enemies);

	//void LoadMapAssets(Player* players[], std::vector<Brick*>& bricks, std::vector<Pipe*>& pipes, std::vector<Coin*>& coins);
	int GetTileWidth() { return mTileWidth; }
private:
	SDL_Renderer* mRenderer;
	char mapArray[MAXMAPTILEHEIGHT][MAXMAPTILEWIDTH];
	int mTileWidth;
	void FixPipeTexture(Pipe* pipe, int widthPos, int heightPos);
};

#endif // !_MAPLOADER_H


