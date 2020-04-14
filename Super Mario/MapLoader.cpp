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

	mTileWidth = currentLine.length();
	map.close();
}

MapLoader::~MapLoader()
{
}

void MapLoader::LoadMapAssets(int numOfPlayers, std::vector<Player*>& players, std::vector<Brick*>& bricks, std::vector<Pipe*>& pipes, std::vector<Coin*>& coins, std::vector<Enemy*>& enemies, Flag* & flag)
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

				case '&':
				{
					bricks.push_back(new Brick(mRenderer, "Images/Brick2.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i), SOLIDBLOCK));
					break;
				}

				case '>':
				{
					bricks.push_back(new Brick(mRenderer, "Images/QuestionBlock.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i), QUESTIONBLOCK));
					break;
				}

				case '?':
				{
					bricks.push_back(new Brick(mRenderer, "Images/QuestionBlock.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i), QUESTIONBLOCK, 3));
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
					bricks.push_back(new Brick(mRenderer, "Images/Floor.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i), SOLIDBLOCK));
					break;
				}

				case 'P':
				{
					pipes.push_back(new Pipe(mRenderer, "Images/Pipe.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i)));
					FixPipeTexture(pipes[pipes.size() - 1], j, i);
					break;
				}

				case 'O':
				{
					coins.push_back(new Coin(mRenderer, "Images/Coin.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i)));
					break;
				}

				case 'G':
				{
					enemies.push_back(new Enemy(mRenderer, "Images/Goomba.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i)));
					break;
				}

				case 'M':
				{
					players.push_back(new Player(mRenderer, "Images/Mario.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i), 1));
					break;
				}

				case 'L':
				{
					if (numOfPlayers > 1)
					{
						players.push_back(new Player(mRenderer, "Images/Luigi.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i), 2));
					}
					break;
				}

				case 'F':
				{
					if (flag == NULL)
					{
						flag = new Flag(mRenderer, "Images/Flag.png", Vector2D(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i));
					}

					flag->AddSection(DEFAULTTILEWIDTH * RENDERSCALE * j, DEFAULTTILEHEIGHT * RENDERSCALE * i);
					break;
				}
			}
		}
	}
}

void MapLoader::FixPipeTexture(Pipe* pipe, int widthPos, int heightPos)
{
	bool pipeAbove = false,
		pipeBelow = false,
		pipeLeft = false,
		pipeRight = false;

	if (mapArray[heightPos - 1][widthPos] == 'P')
	{
		pipeAbove = true;
	}
	if (mapArray[heightPos + 1][widthPos] == 'P')
	{
		pipeBelow = true;
	}
	if (mapArray[heightPos][widthPos - 1] == 'P')
	{
		pipeLeft = true;
	}
	if (mapArray[heightPos][widthPos + 1] == 'P')
	{
		pipeRight = true;
	}
	
	if (pipeAbove)
	{
		pipe->SetSourceRectPosY(16);
	}
	
	if (pipeLeft)
	{
		pipe->SetSourceRectPosX(16);
	}
}
