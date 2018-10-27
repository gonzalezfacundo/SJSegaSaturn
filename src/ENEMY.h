#ifndef _ENEMY_H_
#define _ENEMY_H_

#include	"sgl.h"
#include	"global.h"

#define ENEMY_STATUS_GO_LEFT    1
#define ENEMY_STATUS_GO_RIGHT   2
#define ENEMY_STATUS_DIE        3

void setEnemyAnim();
void enemyStart();
void updateIA(int index);
void drawGameActorEnemy(GameActor *temp, Uint32 spriteIndex);
void enemyDraw(Uint8 index);
void enemyMoveXR(int index);
void enemyMoveXL(int index);
FIXED enemyGetPosY(int index);
FIXED moveEggmanX(FIXED numAprox);

#endif
