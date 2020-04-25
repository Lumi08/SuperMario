#ifndef _GAMEOVER_H
#define _GAMEOVER_H

#include <SDL.h>
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Ui.h"
#include "Texture2D.h"
#include "Text.h"
#include "SoundEffect.h"

class GameOver : GameScreen
{
public:
	GameOver(SDL_Renderer* renderer, GameScreenManager* manager, int finalScore);
	~GameOver();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	GameScreenManager* mManager;
	Texture2D* mGameOverTexture;
	Texture2D* mBackgroundTexture;
	Texture2D* mTextBackgroundTexture;
	Vector2D mGameOverTexturePosition;
	Vector2D mTextPosition;
	Button* mMainMenuButton;
	Text* mText;
	SoundEffect* mMusic;
};

#endif // !_GAMEOVER_H