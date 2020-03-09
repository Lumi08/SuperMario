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

class MapLoader
{
public:
	MapLoader(char* path, SDL_Renderer* renderer);
	~MapLoader();

	void LoadMapAssets(Player* players[], std::vector<Brick*>& bricks);

	int GetActualBrickCount() { return mBrickCount; }

private:
	SDL_Renderer* mRenderer;
	char mapArray[MAXMAPTILEHEIGHT][MAXMAPTILEWIDTH];
	int mBrickCount;
};

#endif // !_MAPLOADER_H


