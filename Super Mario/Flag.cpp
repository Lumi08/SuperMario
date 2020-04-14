#include "Flag.h"

Flag::Flag(SDL_Renderer* renderer, std::string path, Vector2D position) : Entity(renderer, path, position, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT)
{
	mSourceRect = new  SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT };
}

Flag::~Flag()
{

}

void Flag::Render(SDL_Rect* camera)
{
	mSourceRect->x = 0;
	mTexture->Render(mPolePos[0], SDL_FLIP_NONE, RENDERSCALE, camera, 0, mSourceRect);

	mSourceRect->x = 16;

	for (int i = 1; i < mPolePos.size(); i++)
	{
		mTexture->Render(mPolePos[i], SDL_FLIP_NONE, RENDERSCALE, camera, 0, mSourceRect);
	}
}

void Flag::Update(float deltatime, SDL_Event e)
{
	mPosition = mPolePos[0];
	//UpdateHitbox();
}

void Flag::AddSection(int x, int y)
{
	mPolePos.push_back(Vector2D(x, y));
	mHitbox->h += 32;
}

void Flag::Clear()
{
	mPolePos.clear();
}
