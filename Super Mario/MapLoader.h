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

	/// Used to load all the correct assets for the selected map and set their locations to the correct times which is also determined by the txt file
	void LoadMapAssets(int numOfPlayers, std::vector<Player*>& players, std::vector<Brick*>& bricks, std::vector<Pipe*>& pipes, std::vector<Coin*>& coins, std::vector<Enemy*>& enemies);

	int GetTileWidth() { return mTileWidth; }
private:
	SDL_Renderer* mRenderer;
	char mapArray[MAXMAPTILEHEIGHT][MAXMAPTILEWIDTH];
	int mTileWidth;

	/// Fixes the pipes textures to be the correct texture so pipes look correct when rendered
	void FixPipeTexture(Pipe* pipe, int widthPos, int heightPos);
};

#endif // !_MAPLOADER_H


