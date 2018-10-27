#ifndef _HERO_H_
#define _HERO_H_

#include	"sgl.h"
	

#define HERO_MOVE_X 3
#define HERO_MOVE_Y 6

//-------------------------START Hero defines----------------------------------
 //-------------------------Status of HERO class
 enum heroStats{
 	HERO_STATUS_STAND,
 	HERO_STATUS_WALK,
 	HERO_STATUS_BALL,
 	HERO_STATUS_ATTACK,
	HERO_STATUS_SATTACK,
 	HERO_STATUS_JUMP,
 	HERO_STATUS_FALL,
 	HERO_STATUS_HURT,
 	HERO_STATUS_INVINSIBLE,
 	HERO_STATUS_DIE,
 	HERO_STATUS_CROUNCH,
	HERO_STATUS_SUPERJUMP,
	HERO_STATUS_SPRINGJUMP};


void heroStart();
void heroControl();
void heroDraw();
void heroMoveYUp();
void heroMoveXL();
void heroMoveXR();
FIXED heroGetPosY();
void heroChangeState ( Uint8 heroState );


#endif
