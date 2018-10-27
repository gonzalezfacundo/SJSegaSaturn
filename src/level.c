
#include    "level.h"
#include    "load.h"
#include	"sgl.h"
#include	"global.h"
#include    "sega_gfs.h"
#include	"level_spr_attr.h"


#define     NUMBERS_SPRITE_OFFSET   65

FIXED   posTile[XYZ];
FIXED   baseBackground = toFIXED(0.0);
ANGLE	angTile;

extern GameActor    rings[], arrowJump[],
                    platforms[], spring[], endStage,
                    briefLine[],checkPoint[],bonusPoint[10];

Sprites BRIEF_CHARNAME,
        BRIEF_MSG_PASS,BRIEF_MSG_ACT,
        BRIEF_RING,BRIEF_BONUS,BRIEF_TIME;

Sprites BLUE_LABEL[7],
        WHITE_LABEL,
        SONIC_LABEL,
        NAME_LABEL[1];

extern Uint8 levelMapGreenHill[][];

Sint8 ringStarAnimation2[] = {60,61,62};

Player      player1;

extern GameActor   enemy[],explode,eggMan,bossWeapon;

GameLevel   level;
extern posCAM_Y,posCAM_YN;

extern Uint8 actualSecond, actualMinute;

Sprites SPR_BACK,SPR_HUD;

void drawGameDispSprite(Sprites *sprite) {
    attr_levelSprites[0].texno=sprite->spriteID;    
    slDispSprite(sprite->pos, attr_levelSprites, sprite->ang);
}

void drawLevelIntro(){
Uint8 i = 0;
    for(i=0; i<8; i++) {
        drawGameDispSprite(&BLUE_LABEL[i]);
    }
    drawGameDispSprite(&SONIC_LABEL);

    for(i=0; i<2; i++) {
        drawGameDispSprite(&NAME_LABEL[i]);
    }
    drawGameDispSprite(&WHITE_LABEL);
}

void animLevelIntro(){

Uint8 i = 0;

    if(level.levelIntroOutAnimCounter > 0) {
        
        for(i=0; i<8; i++) {
            BLUE_LABEL[i].pos[X] = BLUE_LABEL[i].pos[X] - toFIXED(4.0);
        }
        SONIC_LABEL.pos[X] = SONIC_LABEL.pos[X] - toFIXED(4.0);
    
        for(i=0; i<2; i++) {
            NAME_LABEL[i].pos[Y] = NAME_LABEL[i].pos[Y] + toFIXED(4.0);
        }
        WHITE_LABEL.pos[Y] = WHITE_LABEL.pos[Y] + toFIXED(4.0);
        level.levelIntroOutAnimCounter--;
    }

}

void drawScene(Uint8 levelMap[130][10]) 
{
    Uint8 i=0;
    Uint8 j=0;
    
    SPR_BACK.pos[X]= toFIXED(  15.0);
    SPR_BACK.pos[Y]= toFIXED(  0.0) + baseBackground;//toFIXED(  -1350.0);
    SPR_BACK.pos[Z]= toFIXED(  169.0);
    SPR_BACK.pos[S]= toFIXED(  1.0);

for(i=0;i<130;i++)
 { 
   for(j=0;j<10;j++)
   {     
      if(levelMap[i][j]>0)
      {  
            attr_levelSprites[0].texno = ((levelMap[i][j]) - 1 ) + TILE_START_INDEX;
			slPutSprite(SPR_BACK.pos,attr_levelSprites , SPR_BACK.ang);
             
        }
        SPR_BACK.pos[X]=SPR_BACK.pos[X]+toFIXED(32.0);
    }
    SPR_BACK.pos[X]=toFIXED(15.0);
    
   SPR_BACK.pos[Y]=SPR_BACK.pos[Y]+toFIXED(32.0); 
 }
                            
}
void drawGameActor(GameActor *temp, Uint32 spriteIndex, Uint8 centered)
{   
    Uint8 inverted=false;

    if(temp->lives>0) {
        
        if(temp->animIndex>temp->animEnd){
                temp->animIndex=0;
            }

        if(temp->animation[temp->animIndex]<0) {    
            inverted=true;
            if(centered) {
                attr_levelSpritesInverted[0].texno = _ZmCC;    
            }
            attr_levelSpritesInverted[0].texno=(temp->animation[temp->animIndex]*(-1));
            
        } else {
            if(centered) {
                attr_levelSpritesInverted[0].texno = _ZmCC;
            }
            attr_levelSprites[0].texno=temp->animation[temp->animIndex];// + spriteIndex;
        }

        if(!inverted){
            slPutSprite(temp->SPR_GA.pos, attr_levelSprites, temp->SPR_GA.ang);

        }else {
            slPutSprite(temp->SPR_GA.pos, attr_levelSpritesInverted, temp->SPR_GA.ang);
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

void drawArrowJump()
{   
    Uint8 i;

    for(i=0;i<level.ArrowJumpTotal;i++) {
        if(arrowJump[i].animIndex>arrowJump[i].animEnd){
                arrowJump[i].lives=0;
        }
        drawGameActor(&arrowJump[i],SUPER_JUMP_RING_START_INDEX,0);
    }
}
void drawRings() {
    Uint8 indice;

    for(indice=0;indice<level.ringTotal;indice++) {
        
        //The ring will show stars after collition
        if(rings[indice].state==1) {
            if(rings[indice].animIndex>rings[indice].animEnd) {
                rings[indice].lives=0;
                
            }
        }
        
        if(rings[indice].SPR_GA.collide == true && rings[indice].state==0) {
            rings[indice].SPR_GA.collide = false;
            rings[indice].animation=ringStarAnimation2;
            rings[indice].animIndex=0;
            rings[indice].animEnd=sizeof(ringStarAnimation2)/sizeof(Sint8)-1;
            rings[indice].state=1;
            
         
        }

            drawGameActor(&rings[indice],RING_START_INDEX,0);
    }
}
void gameActorMoveXR(GameActor *object){
    object->SPR_GA.pos[X] = object->SPR_GA.pos[X]+ toFIXED(2.0);
}

void gameActorMoveXL(GameActor *object){
    object->SPR_GA.pos[X] = object->SPR_GA.pos[X]- toFIXED(2.0);
}



	//--------------------------------------------------------------------------
	/// control the gameActor position and sprites.
	//--------------------------------------------------------------------------
void gameActorMoveIA(GameActor *object){      

    //if (object->lives >0)
       switch(object->state) {
            
          case  GAMEACTOR_STATUS_GO_LEFT: {
                   gameActorMoveXL(object);
                    if(object->secuence>=60){
                        object->state=GAMEACTOR_STATUS_GO_RIGHT;
                        object->secuence=0;
                    } 
                    object->secuence++;

                }
                break;
          case  GAMEACTOR_STATUS_GO_RIGHT: {
                   gameActorMoveXR(object);
                    if(object->secuence>=60) {
                        object->state=GAMEACTOR_STATUS_GO_LEFT;
                        object->secuence=0;
                    }
                    object->secuence++;
                }
                break;
    }
}

void controlPlatforms() {
    Uint8 indice=0;
    Uint8 type=1;
    Uint8 animSecuence=0;
    for(indice=0;indice<level.platformTotal ;indice++)
    {
    
        switch(platforms[indice].state)
        {
        case 1: //autoDestructible platform
              //  SPR_PLATFORM[indice].pos[Y] = SPR_PLATFORM[indice].pos[Y] + toFIXED(2.0);
            break;
        case 2: //autoMoveX platform
                //platforms[indice].SPR_GA.pos[Y] = platforms[indice].SPR_GA.pos[Y] + toFIXED(2.0);
				
				//platforms[indice]
				
            break;
        }
        
        if(platforms[indice].autoMoveX == 1) {
            gameActorMoveIA(&platforms[indice]);
        }
        
    }
    
    
}

void drawPlatforms() {
Uint8 index;
    for(index=0;index<level.platformTotal;index++) {
        
        
        
        switch(platforms[index].type) {
            case 1: drawGameActor(&platforms[index],0,0);
                break;
            case 2:                   
                    if(platforms[index].SPR_GA.collide == true) {
                        platforms[index].animEnabled = true;
                    }
                    drawGameActor(&platforms[index],0,0);
                break;
            case 3: 
                    drawGameActor(&platforms[index],0,0);                
                break;
            
        }
    }
}


void drawEndStage() {
    if(endStage.animIndex == endStage.animEnd) {
        endStage.animEnabled = false;
    }
    drawGameActor(&endStage,0,0);

}

void drawBonusPoint() {
    Uint8 i = 0;
    for(i=0;i<level.bonusPointTotal;i++) {
        if(bonusPoint[i].animIndex>bonusPoint[i].animEnd){
                bonusPoint[i].lives=0;
        }
        drawGameActor(&bonusPoint[i],0,0);
    }
}
void drawSpring() {
    Uint8 index = 0;
    for(index=0;index<level.springTotal;index++) {
        drawGameActor(&spring[index],0,0);
    }

}
void drawCheckPoint() {
    Uint8 index = 0;
    for(index=0;index<level.springTotal;index++) {
        if(checkPoint[0].state == 0 && checkPoint[0].animIndex>checkPoint[0].animEnd) {
            changeCheckPointAnimation(0);
        }
        drawGameActor(&checkPoint[0],0,0);
    }

}

void drawBoss(){

    if(level.bossTotal == 1) {
        controlEggMan();
        eggManIA();
        drawGameActor(&eggMan,0,1);
    }
}

void drawWeapon(){

    if(level.bossTotal == 1) {
        drawGameActor(&bossWeapon,0,1);
    }
}

void drawNumbers(char txt[], FIXED x, FIXED y) {

Sint8 frame,sFrame,i;
Sint8 sprDiag1,sprDiag2,crlf;
Sprites SPR_LETTER;

SPR_LETTER.pos[X]=x;
SPR_LETTER.pos[Y]=y;
SPR_LETTER.pos[Z]=toFIXED(169.0);
SPR_LETTER.pos[S]=toFIXED(1.0);
SPR_LETTER.ang=0;

 for(i=0;i<strlen(txt);i++) {   
        crlf=FALSE;
        frame=-1;
        sFrame=-1;  

        switch(txt[i])
        {
            case'0':frame=0; break;
            case'1':frame=1; break;
            case'2':frame=2; break;
            case'3':frame=3; break;
            case'4':frame=4; break;
            case'5':frame=5; break;
            case'6':frame=6; break;
            case'7':frame=7; break;
            case'8':frame=8; break;
            case'9':frame=9; break;
        }
        
        SPR_LETTER.pos[X]=SPR_LETTER.pos[X]+toFIXED(9.0);
        SPR_LETTER.spriteID = frame + NUMBERS_SPRITE_OFFSET;
        drawGameDispSprite(&SPR_LETTER);
    }
}

 /* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
     int i, sign;
      
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     
     reverse(s);   
     
}


void drawRingCounter(){

    char a[3]={0,0,0};
    itoa(player1.rings,a);
    drawNumbers(a,toFIXED(32.0),toFIXED(10.0));
}
void drawPointsCounter(){
    
    char a[10];
    itoa(player1.points,a);
    drawNumbers(a,toFIXED(32.0),toFIXED(30.0));
}

void drawLiveCounter()
{   char a[2];
    itoa(player1.lives,a);
    drawNumbers(a,toFIXED(25.0),toFIXED(210.0));
    
}

void drawTimerCounter()
{   char s[2];
    char m[2];
    char h[2];

    itoa(actualSecond,s);
    if(actualSecond<=9) {
        //s[1] = s[0];
        //s[0] = '0';
        drawNumbers("0",toFIXED(141.0),toFIXED(0.0));
    }
    
    
    itoa(actualMinute,m);
    drawNumbers(s,toFIXED(150.0),toFIXED(0.0));
    drawNumbers(m,toFIXED(100.0),toFIXED(0.0));
  //  drawNumbers(h,toFIXED(60.0),toFIXED(10.0));    

    
}

void drawBriefScreen(){

    drawGameDispSprite(&BRIEF_CHARNAME);    
    drawGameDispSprite(&BRIEF_MSG_PASS);
    drawGameDispSprite(&BRIEF_MSG_ACT);
    drawGameDispSprite(&BRIEF_RING);
    drawGameDispSprite(&BRIEF_BONUS);
    drawGameDispSprite(&BRIEF_TIME);
}

void drawHudInterface()
{   
    SPR_HUD.pos[X]=toFIXED(15.0);
    SPR_HUD.pos[Y]=toFIXED(10.0);
    SPR_HUD.pos[Z]=toFIXED(169.0);
    SPR_HUD.pos[S]=toFIXED(1.0);
    
    SPR_HUD.ang = DEGtoANG(0.0);
    
    SPR_HUD.spriteID = HUD_RINGS_START_INDEX;
    drawGameDispSprite(&SPR_HUD);
    SPR_HUD.pos[X]=toFIXED(15.0);
    SPR_HUD.pos[Y]=toFIXED(200.0);
    SPR_HUD.spriteID = HUD_LIVES_START_INDEX;
    drawGameDispSprite(&SPR_HUD);
    drawRingCounter();
    drawLiveCounter();
    drawPointsCounter();
    drawTimerCounter();
    
    //slPrintHex(slHex2Dec(actualSecond),slLocate(20,1));
    //slPrintHex(slHex2Dec(actualMinute),slLocate(20,2));
}

void addPoints( Uint32 points) {
    player1.points = player1.points + points;
}

void addRing() {
    player1.rings++;
}

Uint8 isEmptyOfLives() {
    if(player1.lives <= 0) {
        return true;
    }
    return false;
}

Uint8 isEmptyOfRings() {
    if(player1.rings <= 0) {
        return true;
    }
    return false;
}

void loseRing() {
    player1.rings= player1.rings - 15;
    if(isEmptyOfRings() == true) {
        player1.rings = 0;
    }
}

void loseLive() {
    player1.lives = player1.lives - 1;
    if(isEmptyOfLives() == true) {
        player1.lives = 0;
    }
}

void intialLives() {
    player1.lives = 3;
    player1.points = 0;
}

void restarLevel() {
    level.restarLevel = true;
}

void resetValues() {
    player1.rings = 0;
    //reset time values
}

void drawLevel()
{
    drawScene(levelMapGreenHill);
    drawPlatforms();
    drawRings();
    drawArrowJump();
    drawBonusPoint();
    drawSpring();
    drawEndStage();
    drawCheckPoint();
    drawBoss();
    drawWeapon();
}
