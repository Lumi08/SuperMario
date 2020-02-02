#include "Entity.h"
#include "Player.h"
#include "Brick.h"
#include "Texture2D.h"

Brick::Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position) : Entity(renderer, imagePath, position)
{
	mSourceRect = new SDL_Rect{ 0, 0, 16, 15 };
}

Brick::~Brick()
{
}

void Brick::Update(float deltaTime, SDL_Event e, Player* mario, Player* luigi)
{
	CollisionsWithPlayer(mario);
}

void Brick::Render()
{
	mTexture->Render(mPosition, SDL_FLIP_NONE, 0.0f, mSourceRect);
}

void Brick::CollisionsWithPlayer(Player* player)
{

}
