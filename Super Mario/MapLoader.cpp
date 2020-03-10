#include "MapLoader.h"

MapLoader::MapLoader(char* path, SDL_Renderer* renderer)
{
	mRenderer = renderer;

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
	map.close();
}

MapLoader::~MapLoader()
{
}

void MapLoader::LoadMapAssets(Player* players[], std::vector<Brick*>& bricks)
{
	for (int i = 0; i < MAXMAPTILEHEIGHT / RENDERSCALE; i++)
	{
		for (int j = 0; j < MAXMAPTILEWIDTH / RENDERSCALE; j++)
		{
			switch (mapArray[i][j])
			{
				case '@':
				{
					bricks.push_back(new Brick(mRenderer, "Images/Brick.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i), BREAKABLEBLOCK));
					break;
				}

				case '?':
				{
					bricks.push_back(new Brick(mRenderer, "Images/QuestionBlock.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i), QUESTIONBLOCK));
					break;
				}

				case '+':
				{
					bricks.push_back(new Brick(mRenderer, "Images/Brick.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i), SECRETBLOCK, 
						new Mushroom(mRenderer, "Images/RedMushroom.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i), RENDERSCALE, FACING_RIGHT)));
					break;
				}

				case '#':
				{
					bricks.push_back(new Brick(mRenderer, "Images/Floor.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i), FLOORBLOCK));
					break;
				}

				case 'M':
				{
					players[0]->SetX(DEFAULTTILEWIDTH * RENDERSCALE * j);
					players[0]->SetY(DEFAULTTILEHEIGHT * RENDERSCALE * i);
					break;
				}
			}
		}
	}
}