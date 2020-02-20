#include "MapLoader.h"

MapLoader::MapLoader(char* path, SDL_Renderer* renderer)
{
	mRenderer = renderer;
	mBrickCount = 0;

	std::string currentLine;
	std::ifstream map(path);
	int rowCount = 0;

	if (map.is_open())
	{
		while (getline(map, currentLine))
		{
			rowCount++;
			for (int i = 0; i < currentLine.length(); i++)
			{
				mapArray[rowCount - 1][i] = currentLine[i];
			}
		}
	}
}

MapLoader::~MapLoader()
{
}

void MapLoader::LoadMapAssets(Player* players[], Brick* bricks[])
{
	for (int i = 0; i < MAXMAPTILEHEIGHT / RENDERSCALE; i++)
	{
		for (int j = 0; j < MAXMAPTILEWIDTH / RENDERSCALE; j++)
		{
			switch (mapArray[i][j])
			{
				case 'b':
				{
					bricks[mBrickCount] = new Brick(mRenderer, "Images/Brick.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i));
					mBrickCount++;
					break;
				}
			}
		}
	}
}