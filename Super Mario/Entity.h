#ifndef _ENTITY_H_
#define _ENTITY_H_


#include <SDL.h>
#include <string>

#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"

class Texture2D;
class Entity
{
public:
	Entity(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int width, int height);
	Entity();
	virtual ~Entity();

	/// Renders the entitys textures and the animations for the entity 
	virtual void Render();
	/// update function is where all the logic for the enemy is updated
	virtual void Update(float deltaTime, SDL_Event e);
	/// Used to display the entitys hitboxes which is useful for debugging 
	virtual void Debug(SDL_Rect* camera, int type);
	
	/// updates the hitboxes pisitions to make sure collisions work perfectly
	void UpdateHitbox();
	/// update the sensor hitboxes which are used to determine which side has been hit on a entity
	void UpdateSensors();
	/// fully updates the sensors as this will take width and height into acount wile the standard update doesnt as most entitys will not change width and height
	void FullUpdateSensors();

	/// Check if a entity is colliding with another entity
	bool IsCollidingWith(Entity* entity);
	/// Gets the side which the entitys are colliding with
	SIDE GetSideCollidingWithEntity(Entity* entity);

	/// gets the entitys hitboxes making collisions work in external classes which use entitys
	SDL_Rect* GetHitbox() { return mHitbox; }
	float GetX() { return mPosition.x; }
	float GetY() { return mPosition.y; }
	int GetWidth() { return mRawWidth * RENDERSCALE; }
	int GetHeight() { return mRawHeight * RENDERSCALE; }

	void SetX(float x) { mPosition.x = x; }
	void SetY(float y) { mPosition.y = y; }
	void SetWidth(int width) { mWidth = width; }
	void SetHeight(int height) { mHeight = height; }
	
	SDL_Rect* GetBottomSensorBox() { return mSensorBottom; }
	SDL_Rect* GetTopSensorBox() { return mSensorTop; }

protected:
	SDL_Renderer* mRenderer;

	SDL_Rect* mHitbox;

	int mSensorSize;
	SDL_Rect* mSensorLeft;
	SDL_Rect* mSensorRight;
	SDL_Rect* mSensorTop;
	SDL_Rect* mSensorBottom;

	Texture2D* mTexture;
	Vector2D mPosition;
	int mWidth,
		mHeight,
		mRawWidth,
		mRawHeight;

	void InitSensors();
};

#endif // !_ENTITY_H_
