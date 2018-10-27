#include 	"hero.h"
#include	"hero_spr_attr.h"
#include	"global.h"
    
GameActor   Sonic;
Uint8       sonicStand[]={75,76,77};
Uint8       sonicJump[]={80,81,82};
Uint8       sonicFall[]={83,84,85};
Uint8       sonicBall[]={86,87,88};
Uint8       sonicSpecial[]={89,90,91,92,93,94,95,96};
Uint8       sonicHurt[]={97};
Uint8       sonicDie[]={98};

Uint8       sonicCollisionVec[]={0,0,0,0};  //up,down,attack,hurt



void heroStart() {       
        Sonic.SPR_GA.pos[S] =toFIXED( 1.0);
        Sonic.SPR_GA.orientation=0;
        Sonic.animIndex=0;
        Sonic.animEnd=6;
		Sonic.SPR_GA.cHeight=toFIXED(32.0);
		Sonic.SPR_GA.cWeight=toFIXED(24.0);
        Sonic.state=HERO_STATUS_STAND;
}

void heroMoveXR(){   
    Sonic.SPR_GA.orientation=0;
	if(Sonic.SPR_GA.pos[X]<=toFIXED(285.0)) {
        Sonic.SPR_GA.pos[X]=Sonic.SPR_GA.pos[X]+ toFIXED(DIF_X);
    }
    
}
void heroMoveYUp() {
    Sonic.SPR_GA.pos[Y]=Sonic.SPR_GA.pos[Y]- toFIXED(DIF_Y);
}
void heroMoveYDown() {
    Sonic.SPR_GA.pos[Y]=Sonic.SPR_GA.pos[Y]+ toFIXED(DIF_Y);
}

void heroChangeState( Uint8 heroState ) {
    Sonic.state = heroState;
    Sonic.secuence = 0;
}
void heroMoveXL() {
      Sonic.SPR_GA.orientation=1;    
	  if(Sonic.SPR_GA.pos[X]>=toFIXED(10.0))
      Sonic.SPR_GA.pos[X]=Sonic.SPR_GA.pos[X]- toFIXED(DIF_X);    
}

FIXED heroGetPosY() {
    return Sonic.SPR_GA.pos[Y];
}

void heroControl()  {
    
    switch(Sonic.state) {
        case  HERO_STATUS_DIE: 
            {

                if(Sonic.secuence<16) {
                    heroMoveYUp();
                }
                
                if(Sonic.secuence>16 && Sonic.secuence<36) {
                    heroMoveYDown();
                }
                
                if(Sonic.secuence>36) {
                    restarLevel();
                }
                Sonic.secuence++;
            }
            break;
         
            
        case  HERO_STATUS_STAND: 
                {   //slPrintFX(heroGetPosY(), slLocate(0,20));
                     if(Sonic.secuence>5)    {

                            heroChangeState( HERO_STATUS_JUMP );
                            snd_play( SFX_JUMP );
                        }
                    Sonic.secuence++;
                }
                break;
            
        case  HERO_STATUS_JUMP:
                {  
                    if(sonicCollisionVec[4]) {
                        //heroChangeState(HERO_STATUS_HURT); 
                    }
                    if(Sonic.secuence<16)    {
                            heroMoveYUp();
                    }
                    else   {
                            //Sonic.SPR_GA.pos[Y] = Sonic.SPR_GA.pos[Y] - toFIXED(8.0);
                    }

                    if(Sonic.secuence>=20)
                    {
                        heroChangeState( HERO_STATUS_FALL );
                    } 

                    Sonic.secuence++;
                    Sonic.SPR_GA.collide=false;
                    sonicCollisionVec[0]=0;
                    
                }
                break;
        case  HERO_STATUS_FALL:   {
                    
                        
                    if(sonicCollisionVec[0]== false){
                                           
                            heroMoveYDown();
                    
                    }  else if(sonicCollisionVec[0]==true) {
                                heroChangeState( HERO_STATUS_STAND );

                    }
                    Sonic.secuence++;
                  }
                
                break;

        case  HERO_STATUS_SUPERJUMP:
                {   

                    heroMoveYUp();
                    if(Sonic.secuence>=40) {
                        heroChangeState( HERO_STATUS_JUMP );

                    } 
                    Sonic.secuence++;
                }break;
        case  HERO_STATUS_SPRINGJUMP: 
                {   

                    heroMoveYUp();
                    if(Sonic.secuence>=22) {
                        heroChangeState( HERO_STATUS_JUMP );

                    } 
                    Sonic.secuence++;
                }break;
        case  HERO_STATUS_SATTACK:
                {   

                    if(Sonic.secuence<=6) {
                        Sonic.SPR_GA.collide=false;
                        Sonic.SPR_GA.pos[Y] = Sonic.SPR_GA.pos[Y] - toFIXED(6.0);
                    }
                    else {
                        Sonic.SPR_GA.pos[Y] = Sonic.SPR_GA.pos[Y] - toFIXED(3.0);
                    }

                    if(Sonic.secuence>6) {
                        heroChangeState( HERO_STATUS_FALL );

                    } 

                    Sonic.secuence++;
                    
                    
                }break;
        case    HERO_STATUS_HURT:
                {
                    ///Sonic.SPR_GA.pos[Y] = Sonic.SPR_GA.pos[Y] - toFIXED(8.0); 
                    heroMoveYUp();  
                    if(Sonic.secuence>10) {
                        Sonic.invinsible=false;
                        sonicCollisionVec[4]= false;
                        heroChangeState( HERO_STATUS_JUMP );                    
                    } 
                    Sonic.secuence++;
                }break;
                                   
                

    } 

    
}

void heroDraw()
{

 switch(Sonic.state)    {
        
        case    HERO_STATUS_DIE:
                    Sonic.SPR_GA.spriteID=sonicDie[0];
            break;
        
            
        case    HERO_STATUS_STAND:
                    Sonic.SPR_GA.spriteID=sonicStand[Sonic.animIndex];
                    Sonic.animIndex++;
                    if(Sonic.animIndex >=sizeof(sonicStand)/sizeof(Uint8))
                        { Sonic.animIndex=2;}   
                    
            break;
                
        case    HERO_STATUS_JUMP:

                    Sonic.SPR_GA.spriteID=sonicBall[Sonic.animIndex];
                    if(sonicCollisionVec[4]==true){
                        Sonic.SPR_GA.spriteID=sonicHurt[0];
                    }
                    
                    Sonic.animIndex++;
                    if(Sonic.animIndex >=sizeof(sonicBall)/sizeof(Uint8))
                        { Sonic.animIndex=0;}   
            break;
            
        case    HERO_STATUS_FALL:
                    Sonic.SPR_GA.spriteID=sonicFall[Sonic.animIndex];
                    Sonic.animIndex++;
                    if(Sonic.animIndex >=sizeof(sonicFall)/sizeof(Uint8))
                        { Sonic.animIndex=0;
                        }   
            break;
        case HERO_STATUS_SATTACK:
                    Sonic.SPR_GA.spriteID=sonicSpecial[Sonic.animIndex];
                    Sonic.animIndex++;
                    if(Sonic.animIndex >=sizeof(sonicSpecial)/sizeof(Uint8))
                        { Sonic.animIndex=0;
                        }
                    Sonic.SPR_GA.spriteID=sonicSpecial[Sonic.animIndex];

            break;
        case    HERO_STATUS_HURT:
             
                    Sonic.SPR_GA.spriteID=sonicHurt[0];
            
            
            break;
        case    HERO_STATUS_SPRINGJUMP:
            
                    Sonic.SPR_GA.spriteID=sonicBall[Sonic.animIndex];
                    Sonic.animIndex++;
                    if(Sonic.animIndex >=sizeof(sonicBall)/sizeof(Uint8))
                        { Sonic.animIndex=0;
                        }      
        case    HERO_STATUS_SUPERJUMP:
            
                    Sonic.SPR_GA.spriteID=sonicJump[Sonic.animIndex];
                    Sonic.animIndex++;
                    if(Sonic.animIndex >=sizeof(sonicJump)/sizeof(Uint8))
                        { Sonic.animIndex=0;
                        }  
            
            break;
    }



  if(Sonic.SPR_GA.orientation==0 && Sonic.state!=HERO_STATUS_WALK) {    
        attr_Sonic[0].texno=Sonic.SPR_GA.spriteID;   
        #ifdef NEW_CAMERA
		slPutSprite(Sonic.SPR_GA.pos, attr_Sonic, Sonic.SPR_GA.ang);
		#else
		slDispSprite(Sonic.SPR_GA.pos, attr_Sonic, Sonic.SPR_GA.ang);  
		#endif
    }
 else {
        attr_SonicInverted[0].texno=Sonic.SPR_GA.spriteID;
		#ifdef NEW_CAMERA
        slPutSprite(Sonic.SPR_GA.pos, attr_SonicInverted, Sonic.SPR_GA.ang);
		#else
		slDispSprite(Sonic.SPR_GA.pos, attr_SonicInverted, Sonic.SPR_GA.ang);
		#endif
    }

}

