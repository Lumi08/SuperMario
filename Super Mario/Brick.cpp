#include "Brick.h"
#include "Texture2D.h"

Brick::Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position, float renderScale) : Entity(renderer, imagePath, position, 16, 16, renderScale)
{
	mSourceRect = new SDL_Rect{ 0, 0, 16, 16 };
}

Brick::~Brick()
{
	delete mSourceRect;
}

void Brick::Update(float deltaTime, SDL_Event e, Player* player, int numOfPlayers)
{
	PlayerCollisions(player);
	/*for (int i = 0; i < numOfPlayers; i++)
	{
	}*/
}

void Brick::Render()
{
	mTexture->Render(mPosition, SDL_FLIP_NONE, mRenderScale, 0.0f, mSourceRect);
}

void Brick::PlayerCollisions(Player* player)
{
	int sideHit;
	
}


