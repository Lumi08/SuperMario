#pragma once

//Screen dimensions
#define SCREEN_WIDTH	1280
#define SCREEN_HEIGHT	600

#define MAXPLAYERCOUNT 2

#define SMALLCHARACTERWIDTH 16
#define SMALLCHARACTERHEIGHT 16
#define BIGCHARACTERWIDTH 30
#define BIGCHARACTERHEIGHT 27
#define GRAVITY 100.0f

#define JUMP_FORCE_DECREMENT 600.0f
#define INITIAL_JUMP_FORCE 500.0f


/*
	TODO:
	Collisions function is very dependant on the int that is passed into it, maybe make a class with the different collisions for the entitys
*/
