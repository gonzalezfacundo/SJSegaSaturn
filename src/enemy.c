#include 	"enemy.h"
#include	"enemy_spr_attr.h"
#include    "explode_spr_attr.h"

GameActor   enemy[20],explode,eggMan,bossWeapon;
Sint8 enemyAnimation[]={0,1};
Sint8 explodeAnimation[]={0,1,2,3};
Sint8 eggManAnimation[]={102,101,102,101,102,101,102,101};
Sint8 eggManHurtAnimation[]={101,102,101,102,101,102,101};
Sint8 weaponAnimation[]={103};

//eggMan IA
Uint8 eggManIA_POS1[]= {20,139,255};
Sint8 eggManIA_Secuence[] = {2,0,1,0,2,1,0};
Uint8 startAnim = 0;
Uint8 seqAnim = 0;
ANGLE ang=DEGtoANG(0.0);

extern GameLevel   level;

void setEnemyAnim()
{
    int i;
    for(i=0;i<level.enemyTotal;i++)
    {
        enemy[i].SPR_GA.orientation=0;
        enemy[i].state=ENEMY_STATUS_GO_RIGHT;
        enemy[i].SPR_GA.spriteID=0;
        enemy[i].SPR_GA.collide = false;
        enemy[i].lives=1;
    
        enemy[i].animation=enemyAnimation;
        enemy[i].animIndex=0;
        enemy[i].animEnd=1;
        enemy[i].animEnabled=true;
        enemy[i].animTimeCurrent=0;
        enemy[i].animTimeLength=3;
        enemy[i].secuence=0;
		enemy[i].SPR_GA.cWeight=toFIXED(32.0);
		enemy[i].SPR_GA.cHeight=toFIXED(28.0);

    }
}

void eggManAnim(){
    eggMan.lives=9;
	eggMan.state=0;
    eggMan.animation = eggManAnimation;
    eggMan.animEnabled = false;
    eggMan.animTimeCurrent=0;
    eggMan.animTimeLength=3;
    eggMan.animIndex=0;
    eggMan.animEnd=5;
    eggMan.SPR_GA.cHeight=toFIXED(40.0);
	eggMan.SPR_GA.cWeight=toFIXED(72.0);
    eggMan.SPR_GA.collide = false;
}



Uint8 isEggManEmptyOfLives() {
    if(eggMan.lives <= 1) {
        return true;
    }
    return false;
}
void eggManloseLive(){
    eggMan.lives = eggMan.lives - 1;
    if(isEggManEmptyOfLives() == true) {
        eggMan.lives = 1;
    }
}

void weaponAnim() {

    loadDefaultActor(&bossWeapon);
    bossWeapon.SPR_GA.pos[X] = eggMan.SPR_GA.pos[X];
    bossWeapon.SPR_GA.pos[Y] = eggMan.SPR_GA.pos[Y] + toFIXED(50.0);
    bossWeapon.SPR_GA.pos[Z] = eggMan.SPR_GA.pos[Z];
    bossWeapon.SPR_GA.pos[S] = eggMan.SPR_GA.pos[S];
    bossWeapon.SPR_GA.collide = false;
	bossWeapon.SPR_GA.cHeight=toFIXED(24.0);
	bossWeapon.SPR_GA.cWeight=toFIXED(48.0);
    
    bossWeapon.animation=weaponAnimation;
    bossWeapon.animEnabled=true;
    bossWeapon.animTimeCurrent=0;
    bossWeapon.animTimeLength=3;
    bossWeapon.animIndex=0;
    bossWeapon.animEnd=0;
    bossWeapon.lives=1;
     bossWeapon.SPR_GA.ang = DEGtoANG(0.0);
    ang = DEGtoANG(0.0);
    
}



void enemyStart()
{   
    explode.lives=1;
    explode.animation=explodeAnimation;
    explode.animEnabled=true;
    explode.animTimeCurrent=0;
    explode.animTimeLength=3;
    explode.animIndex=0;
    explode.animEnd=4;
    
    setEnemyAnim();
    eggManAnim();
    weaponAnim();
}

void updateWeapon() {
    //bossWeapon.SPR_GA.pos[X] = eggMan.SPR_GA.pos[X] + toFIXED(10.0);
    //bossWeapon.SPR_GA.pos[Y] = eggMan.SPR_GA.pos[Y] + toFIXED(10.0);
    
    bossWeapon.SPR_GA.pos[X] = slMulFX(toFIXED(100.0), slCos(ang));
    bossWeapon.SPR_GA.pos[Y] = slMulFX(toFIXED(100.0), slSin(ang));
    
    bossWeapon.SPR_GA.pos[X] = bossWeapon.SPR_GA.pos[X] + eggMan.SPR_GA.pos[X] + toFIXED(36.0) - toFIXED(24.0);
    bossWeapon.SPR_GA.pos[Y] = bossWeapon.SPR_GA.pos[Y] + eggMan.SPR_GA.pos[Y] + toFIXED(20.0) - toFIXED(12.0);

    //bossWeapon.SPR_GA.ang += DEGtoANG(5.0); 
    ang += DEGtoANG(1.0);
}

void updateWeapon2() {
    bossWeapon.SPR_GA.pos[X] = eggMan.SPR_GA.pos[X] + toFIXED(10.0);
    bossWeapon.SPR_GA.pos[Y] = eggMan.SPR_GA.pos[Y] + toFIXED(10.0);
    
    
    
    
}
void controlEggMan() {
    
    switch(eggMan.state){
     
     case 0: eggMan.SPR_GA.spriteID = 102;
             eggMan.animIndex = 0;
        break;
            
     case 1:
            eggMan.animEnabled = true;
            if(eggMan.animIndex > eggMan.animEnd){ 
                eggMan.animEnabled = false;
                eggMan.SPR_GA.collide = false;
                eggMan.state = 0;
            }   
        break;
    }
}


void eggManIA() {
    FIXED finalValue;
    finalValue = toFIXED(eggManIA_POS1[eggManIA_Secuence[startAnim]]);
    //finalValue = toFIXED(eggManIA_POS1[1]);
    
    if(startAnim>sizeof(eggManIA_Secuence)/sizeof(Uint8)-1) {
        startAnim=0;
    }

    if(abs(moveEggmanX(finalValue))>= toFIXED(4.0)) {
        if(moveEggmanX(finalValue)>0) {
            eggMan.SPR_GA.pos[X]+=toFIXED(4.0);

        } else {
            eggMan.SPR_GA.pos[X]-=toFIXED(4.0);
        }

    } else {
        
        seqAnim++;
    }
    
    if(seqAnim == 45) {
        startAnim++;
        seqAnim=0;
    }
    updateWeapon();
    //eggMan.SPR_GA.pos[X]+= moveEggmanX(finalValue);
        

    
}



	//--------------------------------------------------------------------------
	/// control the Enemy position and sprites.
	//--------------------------------------------------------------------------
void updateIA(int index)
{      
                  
    if (enemy[index].lives >0)
       switch(enemy[index].state)
        {
            
          case  ENEMY_STATUS_GO_LEFT:
                {   
                    
 
                   enemyMoveXL(index);
                    //if(SPR_ENEM.pos[Y]<=toFIXED(  -180.0)){STATE=HERO_STATUS_FALL;}

                    if(enemy[index].secuence>=20)
                    {enemy[index].state=ENEMY_STATUS_GO_RIGHT;
                     enemy[index].secuence=0;
                     
                    } 
                    enemy[index].secuence++;

                    
                }
                break;
          case  ENEMY_STATUS_GO_RIGHT:
                {	
					 
				  enemyMoveXR(index);
                  if(enemy[index].secuence>=20)
                    {enemy[index].state=ENEMY_STATUS_GO_LEFT;
                     enemy[index].secuence=0;
                    }  
					 
					  enemy[index].secuence++;
                }
                break;
          case  ENEMY_STATUS_DIE:
                {

                  
                }
                break;
            }    
    
}
void drawGameActorEnemy(GameActor *temp, Uint32 spriteIndex)
{   
    int inverted=false;

    if(temp->lives>0 && temp->animEnabled==true) {
        
        if(temp->animIndex>temp->animEnd){
                temp->animIndex=0;
            }
          inverted=temp->SPR_GA.orientation;
           
        if(inverted) {
            attr_EnemyInverted[0].texno=temp->animation[temp->animIndex]+ spriteIndex;
			slPutSprite(temp->SPR_GA.pos, attr_EnemyInverted, temp->SPR_GA.ang);
        } else {        
            attr_Enemy[0].texno=temp->animation[temp->animIndex] + spriteIndex;
            slPutSprite(temp->SPR_GA.pos, attr_Enemy, temp->SPR_GA.ang);

        }
        
        if( temp->animEnabled==true) {
            
            temp->animTimeCurrent++;
            if(temp->animTimeCurrent>temp->animTimeLength) {
                temp->animIndex++;
                temp->animTimeCurrent=0;
            }
        }

    }
}
	//--------------------------------------------------------------------------
	/// draw Enemy on screen
	//--------------------------------------------------------------------------
void enemyDraw(Uint8 index)
{   
    switch(enemy[index].state)
    {
        case ENEMY_STATUS_GO_LEFT:
        case ENEMY_STATUS_GO_RIGHT:
    
	   drawGameActorEnemy(&enemy[index], ENEMY_START_INDEX);
    break;                     
        case ENEMY_STATUS_DIE:
                    if(enemy[index].lives>0) {
                        explode.SPR_GA.pos[X]=enemy[index].SPR_GA.pos[X];
                        explode.SPR_GA.pos[Y]=enemy[index].SPR_GA.pos[Y];
                        explode.SPR_GA.pos[Z]=enemy[index].SPR_GA.pos[Z];
                        explode.SPR_GA.pos[S]=enemy[index].SPR_GA.pos[S];
                        
                        drawGameActorEnemy(&explode, EXPLODE_START_INDEX);
                        if(explode.animIndex >=explode.animEnd) {
                            enemy[index].lives=0;
                            explode.animIndex=0;
                            explode.animEnabled=true;
                            explode.SPR_GA.pos[Z]=toFIXED(1.0);
                        }
                    }
                    
                        
        break;
    }
}

FIXED moveEggmanX(FIXED numAprox) {
    return numAprox - eggMan.SPR_GA.pos[X];
}

	//--------------------------------------------------------------------------
	/// move Enemy to Rigth and check the limit screen
	//--------------------------------------------------------------------------
void enemyMoveXR(int index)
{   enemy[index].SPR_GA.orientation=0;
    enemy[index].SPR_GA.pos[X]=enemy[index].SPR_GA.pos[X]+ toFIXED(2.0);
}
	//--------------------------------------------------------------------------
	/// move Enemy to Left and check the limit screen
	//--------------------------------------------------------------------------
void enemyMoveXL(int index)
{
      enemy[index].SPR_GA.orientation=1;    
      enemy[index].SPR_GA.pos[X]=enemy[index].SPR_GA.pos[X]- toFIXED(2.0);    
}

FIXED enemyGetPosY(int index)
{
    return enemy[index].SPR_GA.pos[Y];
}

void controlEnemy(){
Uint8 index;
    for(index=0;index<level.enemyTotal;index++) {
        updateIA(index);
        enemyDraw(index);
    }
    
}
    
