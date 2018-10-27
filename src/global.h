 /**
 *	Constant
 * @author GonzalezGolaFacundo
 */
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include	"defines.h"


typedef struct SPRITES
{   FIXED pos[XYZS];
    ANGLE ang;
    Uint32 spriteID;
	Uint8 collide;
	Uint8 orientation;
	FIXED cWeight;
	FIXED cHeight;
	FIXED colVecSize[4]; //h1,w1,h2,w2
} Sprites;

typedef struct GAMEACTOR
{   Sprites SPR_GA;
    Uint8   lives;
    Uint8   energy;
    Uint8   type;
    Uint8   invinsible;
    Uint8   state;
    Uint8   secuence;
    Uint8   autoMoveX;  //That's for auto move object-> like a zombie
    Uint8   animEnabled;
	Sint8   *animation;
	Uint8	animIndex;
	Uint8	animEnd;
	Uint8   animTimeCurrent;
	Uint8   animTimeLength;
	Uint8	collisionVector[4];
}GameActor;

typedef struct DIALOG
{   Sprites SPR;
    FIXED pos[XY];
	char *diag;
} dialog;

typedef	struct GAMEOBJECT
{	Sprites		SPR;
	Uint8		type;
}GameObject;

typedef	struct GAMELEVEL
{	
	Uint8		ringTotal;
    Uint8		platformTotal;
    Uint8		springTotal;
  	Uint8		enemyTotal;
	Uint8		ArrowJumpTotal;	
	Uint8		bonusPointTotal;
	Uint8		heroTotal;
	Uint8		checkPointTotal;
	Uint8		finalStageTotal; 
	Uint8		bossTotal;
    Uint8       hSize;
	Uint8		nTrack;
    char        name[8];
    Uint8       levelIntroOutAnimCounter; //It's for show ON screen
    Uint8       levelTimeShowInScreen;
    Uint8       timeOutToChangeLevel;
    Uint8       restarLevel;

}GameLevel;


typedef struct PLAYER
{   Uint8   rings;
    Uint32  points;
    Uint8   lives;
    
}Player;

typedef struct SOUNDS
{
char *p_Sound;
Uint32 size;
PCM type;
}Sounds;


#define SFX_CHECKPOINT 0
#define SFX_EXPLODE 1
#define SFX_FINALCHECK 2
#define SFX_JUMP 3
#define SFX_JUMPER 4
#define SFX_LOSE_RINGS 5
#define SFX_RING 6
#define SFX_TELETRANSPORT 7

typedef struct CAMERA {

Sint32 upperLimit;
Sint32 lowerLimit;

}Camera;

typedef struct cam{
	FIXED	pos[XYZ];
	FIXED	target[XYZ];
	ANGLE	ang[XYZ];
	Uint8   dx;
	Uint8   dy;
} CAMERA;


static CAMERA	cmbuf;

#endif
