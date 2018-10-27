
#include 	"C:\SaturnOrbit\SH_COFF\sh-coff\sh-coff\include\stdlib.h"
extern TEXTURE *FormTbl;
extern Camera gameCamera;
extern GameLevel level;
extern baseBackground;


#include 	"CD.h"
#include 	"hero.h"
#include 	"enemy.h"
#include  	"level.h"
#include	"graphics.h"
#include	"sound.h"
#include    "dialogs.h"
#include    "defines.h"




extern Sprites SPR_PLATFORM[];
extern GameActor Sonic,rings[],arrowJump[],platforms[];
extern GameActor enemy[], spring[], bonusPoint[], endStage, checkPoint[];
extern GameActor eggMan, bossWeapon;
extern Uint8 sonicCollisionVec[];
extern Player player1;

Uint8 actualLevel=GHZ1;
Uint8 actualTrack=1;
int indexDebugObject=0;
int counter;
int debugIndex=0;
Uint8 actualGameState=GAME_STATE_LOGO_RM;
Uint8 nextGameState;
Uint8 loadedState = false;
Uint8 loadedTrack = false;

Uint8 hora=0,minuto=0,segundo=0;

Uint8 showBriefScreen = false;

void initTimer() {
    hora=0;
    minuto=0;
    segundo=0;
}

void debugObject(GameActor ob) {
    slPrintFX(ob.SPR_GA.pos[X],slLocate(0,8));
    slPrintFX(ob.SPR_GA.pos[Y],slLocate(0,9));
    slPrintFX(ob.SPR_GA.pos[Z],slLocate(0,10));
    slPrintFX(ob.SPR_GA.pos[S],slLocate(0,11));
    slPrintHex(slHex2Dec(ob.lives),slLocate(0,12));
    
}


Uint8 collision(Sprites *SPR_A,Sprites *SPR_B, Uint16 indexB) {    
    FIXED w1,h1,w2,h2,x1,x2,y1,y2;
    w1=(SPR_A->cWeight); // ancho del sprite1
    h1=(SPR_A->cHeight); // altura del sprite1
    w2=(SPR_B->cWeight); // ancho del sprite2
    h2=(SPR_B->cHeight); // altura del sprite2
    
    
    
    x1=SPR_A->pos[X]; // pos. X del sprite1

    y1=SPR_A->pos[Y]; // pos. Y del sprite1

    x2=SPR_B->pos[X]; // pos. X del sprite2
    
    y2=SPR_B->pos[Y]; // pos. Y del sprite2
    
    if(indexB == 3) {
        w2=(SPR_B->colVecSize[3]); // ancho del sprite2
        h2=(SPR_B->colVecSize[2]);
        
        y2=SPR_B->pos[Y] + toFIXED(10.0);
    }
    



 
    if (((x1+w1)>x2) && ((y1+h1)>y2) && (((x2)+w2)>x1) && (((y2)+h2)>y1)) {
        return 1;
    } 

    return 0;
}

void changeGameState(nextState){
    
    actualGameState=GAME_STATE_FADEOUT; 
    nextGameState=nextState;
    loadedState = false;
    
}

void nextLevel() {
    actualLevel+=1;
    changeGameState(ENTER_LEVEL);
}

void blinkerString(int cont)
{
	

if(cont>15)
{  drawString("Press Start ", toFIXED(-60.0),toFIXED(0.0));
    }
 if(cont>30){
        cont=0;
    } 
  drawString("Demo", toFIXED(60.0),toFIXED(100.0));     
cont++;    
}

Uint8 controlCollision( ){
Uint8 i;
if(Sonic.SPR_GA.collide == false) {
    sonicCollisionVec[4] = false;
  for(i=0;i<level.platformTotal;i++) {
     
     if(Sonic.SPR_GA.collide == false && Sonic.state==HERO_STATUS_FALL) {
            if(Sonic.SPR_GA.pos[Y] > (cmbuf.target[Y] + toFIXED(120.0))) {

                heroChangeState(HERO_STATUS_DIE);
                loseLive();
                
            }
    }
     
     
     sonicCollisionVec[0]=collision(&Sonic.SPR_GA,&platforms[i].SPR_GA, 0);
     sonicCollisionVec[4]=collision(&Sonic.SPR_GA,&platforms[i].SPR_GA, 3);
     
     
     if(sonicCollisionVec[0]==true && Sonic.state==HERO_STATUS_FALL) {
            platforms[i].SPR_GA.collide = true;
            return 0;
            }  else {
                
                
                if(sonicCollisionVec[4] == true && platforms[i].type == 3) {
                    if(Sonic.state==HERO_STATUS_JUMP) {
                
                        snd_play(SFX_LOSE_RINGS);
                        Sonic.invinsible=true;
                        loseRing();
                        Sonic.SPR_GA.collide = true;
                        return 0;
                    }    

                }
            
            } 
    }
     
}
      
   for (i=0; i<level.enemyTotal;i++)  {
        if(enemy[i].lives>0 && enemy[i].SPR_GA.collide == false) {
        
            sonicCollisionVec[2]=collision(&Sonic.SPR_GA,&enemy[i].SPR_GA, enemy[i].animation[enemy[i].animIndex]);
            
            if(sonicCollisionVec[2]==true && (Sonic.state==HERO_STATUS_JUMP || Sonic.state==HERO_STATUS_SATTACK )) {
                enemy[i].state=ENEMY_STATUS_DIE;
                enemy[i].SPR_GA.collide = true;
                snd_play(SFX_EXPLODE);
                addPoints(100);
                //return 0;
            }
            if(Sonic.invinsible!=true) {
                
                if(sonicCollisionVec[2]==true && Sonic.state==HERO_STATUS_FALL && Sonic.state!=HERO_STATUS_HURT ) {
                    
                    heroChangeState(HERO_STATUS_HURT); 
                    snd_play(SFX_LOSE_RINGS);
                    Sonic.invinsible=true;
                    loseRing();
                    //return 0;
                }
            }
        }
           
            
    }        
    for (i=0; i<level.ringTotal;i++)
    {
        if(rings[i].state==0) {
                if( collision(&Sonic.SPR_GA,&rings[i].SPR_GA,rings[i].animation[rings[i].animIndex])==true) { 
                    rings[i].SPR_GA.collide=true;
                    snd_play(SFX_RING);
                    addRing();
                    return 0;
                }
			}
    }
    
    for (i=0; i<level.ArrowJumpTotal;i++)
    {
        if(arrowJump[i].SPR_GA.collide == false)
        {
            if(collision(&Sonic.SPR_GA,&arrowJump[i].SPR_GA,arrowJump[i].animation[arrowJump[i].animIndex])==1)
            {   
                heroChangeState(HERO_STATUS_SUPERJUMP);
                arrowJump[i].SPR_GA.collide = true;
                arrowJump[i].animEnabled = true;
                
                snd_play(SFX_JUMPER);
                return 0;
            }
        }
        
    }
    for (i=0; i<level.springTotal;i++)
    {
        if(spring[i].SPR_GA.collide == false && Sonic.state == HERO_STATUS_FALL)
        {
            if(collision(&Sonic.SPR_GA,&spring[i].SPR_GA,spring[i].animation[spring[i].animIndex])==1)
            {   
                heroChangeState(HERO_STATUS_SPRINGJUMP);
                spring[i].animEnabled = true;
                snd_play(SFX_JUMPER);
                return 0;
            }
        }
        
    }
    for (i=0; i<level.bonusPointTotal;i++)
    {
        if(bonusPoint[i].SPR_GA.collide == false)
        {
            if(collision(&Sonic.SPR_GA,&bonusPoint[i].SPR_GA,bonusPoint[i].animation[bonusPoint[i].animIndex])==true)
            {   
                bonusPoint[i].SPR_GA.collide=true;
                bonusPoint[i].animEnabled = true;
                addPoints(500);
                return 0;
            }
        }
        
    }
    
    if(endStage.SPR_GA.collide == false) {
        if(collision(&Sonic.SPR_GA,&endStage.SPR_GA,endStage.animation[endStage.animIndex])==true) {
            heroChangeState(HERO_STATUS_STAND);
            endStage.SPR_GA.collide = true;
            endStage.animEnabled = true;
            snd_play(SFX_FINALCHECK);
            showBriefScreen=true;
            //nextLevel();
            return 0;
        }
    }
    if(checkPoint[0].SPR_GA.collide == false) {
        if(collision(&Sonic.SPR_GA,&checkPoint[0].SPR_GA,checkPoint[0].animation[checkPoint[0].animIndex])==true) {
            checkPoint[0].SPR_GA.collide = true;
            checkPoint[0].animEnabled = true;
            snd_play(SFX_CHECKPOINT);
            return 0;
        }
    }
    if(level.bossTotal == 1) {
        
        if(eggMan.SPR_GA.collide == false) {
            if(collision(&Sonic.SPR_GA, &eggMan.SPR_GA, 0) == true) {
                if(Sonic.state==HERO_STATUS_JUMP || Sonic.state==HERO_STATUS_SATTACK ) {
                    eggMan.SPR_GA.collide = true;
                    eggMan.state = 1;
                    eggManloseLive();
                }
            }
        }

        if(bossWeapon.SPR_GA.collide == false) {
            if(collision(&Sonic.SPR_GA, &bossWeapon.SPR_GA, 0) == true) {
                heroChangeState(HERO_STATUS_HURT);
                snd_play(SFX_LOSE_RINGS);
                Sonic.invinsible=true;
                loseRing();
    
                
            }
        }
    }
}


void updateCamera() {

    if(cmbuf.target[Y] - toFIXED(DIF_Y*2) > Sonic.SPR_GA.pos[Y] && cmbuf.target[Y]>=toFIXED(124.0)) {
                
                if(cmbuf.dy>DIF_Y) {
                    cmbuf.dy=DIF_Y;
                }
                
                baseBackground -=toFIXED(1.0);
                
                cmbuf.target[Y] = cmbuf.target[Y] - toFIXED(cmbuf.dy);
                cmbuf.pos[Y] = cmbuf.pos[Y] - toFIXED(cmbuf.dy);
                cmbuf.dy++;
    }else {
        cmbuf.dy=1;
    }

}

void levelIntro() {
    
}

void showLogos() {
    
    if(loadedState == false) {
        loadBitMap("JE.BIN",23945 ,240,320);
        loadedState = true;
        CDDA_stop();
    }
    
    counter++;
    if(counter>120) {
                    changeGameState(GAME_STATE_PRESENTATION);
                    counter=0;    
    }
}

void showLogosRM() {
    
    if(loadedState == false) {
        loadBitMap("RM.BIN",33370 ,240,320);
        loadedState = true;
        CDDA_stop();
    }
    
    counter++;
    if(counter>120) {
                    changeGameState(GAME_STATE_LOGO);
                    counter=0;
    }
}

void controlGame() {
    if(loadedTrack==false) {
                fadeIn();
                loadedTrack=true;
                CDDA_stop();
                slSynch(); 
                CDDA_play(level.nTrack);
                slSynch();
    }
     
    
    if( (Smpc_Peripheral[joyIndex].data & PER_DGT_KR) == 0) {
                if(Sonic.state!=HERO_STATUS_STAND)  {
                    heroMoveXR();
                }
   
        }
        if( (Smpc_Peripheral[joyIndex].data & PER_DGT_KU) == 0) {
                 if(Sonic.state!=HERO_STATUS_STAND)  {
                        //heroMoveYUp();
                    }
        }
            
        if( (Smpc_Peripheral[joyIndex].data & PER_DGT_KD) == 0){
                    
                if(Sonic.state!=HERO_STATUS_STAND && Sonic.state!=HERO_STATUS_DIE)  {
                //heroMoveYDown(); 
                }   
        }    
                        
        if( (Smpc_Peripheral[joyIndex].data & PER_DGT_KL) == 0)
            {   
                if(Sonic.state!=HERO_STATUS_STAND && Sonic.state!=HERO_STATUS_DIE)  {
                    heroMoveXL();
                    }
                                   
            }
        if( (Smpc_Peripheral[joyIndex].data & PER_DGT_TA) == 0)
            { 
               
            }
        if( (Smpc_Peripheral[joyIndex].data & PER_DGT_TB) == 0)
            {
             if(Sonic.state == HERO_STATUS_JUMP) {
                    if(Sonic.state != HERO_STATUS_SATTACK && Sonic.state != HERO_STATUS_STAND) {
                        heroChangeState(HERO_STATUS_SATTACK);
                    }
                }
            
            }
        if( (Smpc_Peripheral[joyIndex].data & PER_DGT_TC) == 0) {
//            Sonic.state=HERO_STATUS_WALK;
            
            }    
        if( (Smpc_Peripheral[joyIndex].data & PER_DGT_TR) == 0) {

                nextLevel();
            }
       if( (Smpc_Peripheral[joyIndex].data & PER_DGT_TL) == 0)
            {

            }         
                   
                   
                   
       controlCollision();
       controlPlatforms();
       heroControl();
       controlEnemy();
       
       if(level.restarLevel == true) {
            changeGameState(ENTER_LEVEL);
        }
        if(isEmptyOfLives() == true) {
            changeGameState(GAME_STATE_GAMEOVER);
        }
        
        if((level.bossTotal == 1) && isEggManEmptyOfLives() == true) {
            changeGameState(GAME_STATE_ENDING);
        }

}

void drawGame() {

        drawLevel();
        #ifdef debugObject
            
                
                
            if( (Smpc_Peripheral[joyIndex].data & PER_DGT_TA) == 0) {
                indexDebugObject++;
                }
            if( (Smpc_Peripheral[joyIndex].data & PER_DGT_TB) == 0) {
                 indexDebugObject--;
                }
                slPrint("Enemy",slLocate(10,18));
                slPrintHex(indexDebugObject,slLocate(10,19));
                slPrintFX(enemy[indexDebugObject].SPR_GA.pos[X],slLocate(10,20));
                slPrintFX(enemy[indexDebugObject].SPR_GA.pos[Y],slLocate(10,21));
                
                slPrint("Spring",slLocate(20,18));
                slPrintHex(indexDebugObject,slLocate(20,19));
                slPrintFX(spring[indexDebugObject].SPR_GA.pos[X],slLocate(20,20));
                slPrintFX(spring[indexDebugObject].SPR_GA.pos[Y],slLocate(20,21));
                
            #endif
           
           heroDraw();
           updateCamera();
           slWindow(0, 0 , CAMERA_LIMIT_X , CAMERA_LIMIT_Y , CAMERA_LIMIT_Z ,0 , 0);
           drawHudInterface();
           
           if(level.levelTimeShowInScreen > 0) {
                drawLevelIntro();
                level.levelTimeShowInScreen--;
            }
            if(level.levelTimeShowInScreen <= 0) {
                animLevelIntro();
                drawLevelIntro();
            }

           if(showBriefScreen == true) {
                drawBriefScreen();
                if(level.timeOutToChangeLevel>= 1) {
                    level.timeOutToChangeLevel--;
                } else {
                    nextLevel();
                }
            }
           
    
}

void game() { 

    switch(actualGameState)
    {
        case GAME_STATE_LOGO_RM: 

            showLogosRM();
            fadeIn();
		    break;

		case GAME_STATE_LOGO: 
            showLogos();
            fadeIn();
		    break;

		case GAME_STATE_PRESENTATION: 
               
              if(loadedState == false) {
                    loadResourcesGameState(actualGameState);
                    fadeIn();
                    slSynch();
                    loadedState = true;
                }
               
               
               blinkerString(counter);
                
                
                if( (Smpc_Peripheral[joyIndex].data & PER_DGT_ST) == 0)
                {
                    changeGameState(SHOW_DIALOG);

                }

                counter++;
                if(counter>60){counter=0; }
                
        
			break;	  

        case GAME_STATE_MAINMENU:

			break;
		case GAME_STATE_FADEOUT:

            if(fadeOut()== true) {
                actualGameState=nextGameState;
            }

			break;

        case PREPARE_LEVEL:            
            
            actualGameState=SHOW_DIALOG;
			
            break;
		case SHOW_DIALOG:
            if(loadedState == false) {
                loadDialog();
                fadeIn();
                CDDA_stop();
                slSynch();
				CDDA_play(TRK_DIALOG);
                loadedState = true;
            }
            if(showDialog() == true) {
                    changeGameState(ENTER_LEVEL);
            }
            
            intialLives();
            
            break;
        case ENTER_LEVEL:
                 
                showBriefScreen = false;
                
                cmbuf.ang[X] = cmbuf.ang[Y] = cmbuf.ang[Z] = DEGtoANG(0.0);
                cmbuf.target[X] = toFIXED(160.0);
                cmbuf.target[Y] = toFIXED(4450.0);
            	cmbuf.target[Z] = toFIXED(1.0);
            	cmbuf.pos[X] = toFIXED(160.0);
            	cmbuf.pos[Y] = toFIXED(4450.0);
            	cmbuf.pos[Z] = toFIXED(0.0);
                
                setLevel(actualLevel);
                snd_loadSound_PCM();
                resetValues();
                

                actualGameState=GAME_STATE_GAMEPLAY; 
                //Initialize timer
                initTimer();
                t6 = 0;
                counter=180;
                loadedTrack=false;
            break;
            
		
		case GAME_STATE_GAMEPLAY:
            if(counter<=1){
                counter = 1;
                controlGame();
                drawGame();
            }
            counter--;
        break;
		case GAME_STATE_GAMEOVER:
            if(loadedState == false) {
                loadGameOver();
                fadeIn();
                loadedState = true;
            }
                
            if(counter>=180){
                counter = 1;
                changeGameState(GAME_STATE_LOGO_RM);
            }
            counter++;
        break;
        
        case GAME_STATE_ENDING:
            if(loadedState == false) {
                loadEnding();
                fadeIn();
                loadedState = true;
            }
                
            if(counter>=180){
                counter = 1;
                changeGameState(GAME_STATE_LOGO_RM);
            }
            counter++;
        break;
        
    }
}
