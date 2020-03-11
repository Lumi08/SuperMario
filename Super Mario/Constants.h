#pragma once

//Screen dimensions
#define SCREEN_WIDTH					1024
#define SCREEN_HEIGHT					768

#define RENDERSCALE						2

#define MAXPLAYERCOUNT					2
#define MAXBRICKCOUNT					400

//Raw Image sizes
#define DEFAULTTILEWIDTH				16
#define DEFAULTTILEHEIGHT				16
#define SMALLPLAYERWIDTH				16
#define SMALLPLAYERHEIGHT				16
#define BIGPLAYERWIDTH					16
#define BIGPLAYERHEIGHT					32


#define GRAVITY							100.0f
#define JUMP_FORCE_DECREMENT			600.0f
#define INITIAL_JUMP_FORCE				500.0f

#define MAXMAPTILEHEIGHT				48
#define MAXMAPTILEWIDTH					800


/*
	TODO:
	Collisions function is very dependant on the int that is passed into it, maybe make a class with the different collisions for the entitys
	bug when the character spawns a powerup the other player takes it and it breaks
*/
