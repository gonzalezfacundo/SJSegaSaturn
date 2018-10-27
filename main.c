#include	"SGL.H"
#include	"SEGA_TIM.H"
#include    "STDLIB.H"
#include	"src\global.h"

Uint8 joyIndex;
Uint16 previouscount;
Uint16 t1,t2,t3,t4,t5,t6,t7;
Uint8 actualMinute=0,actualSecond=0;
#include    "src\ss_game.h"

#define TVSTAT      (*(Uint16 *)0x25F80004)

#define Zlimit		150

Uint32 frame=0,i=0;

Camera gameCamera;

Uint32 initMilisec,finMilisec,frameTime=0;

void init_Timer() {
    TIM_FRT_INIT(TIM_CKS_32);
    TIM_FRT_SET_16(0);
}

Uint16 SDL_GetTicks(void){

previouscount += TIM_FRT_CNT_TO_MCR(TIM_FRT_GET_16()) / 1000; 

        TIM_FRT_SET_16(0); 

        return previouscount;

}
Uint32 resetTime() {
    initMilisec = SDL_GetTicks();
}


Uint32 currentTime() {
    finMilisec = SDL_GetTicks();
    return finMilisec - initMilisec;
    
}

void wait_vblank(void)
{
     while((TVSTAT & 8) == 0);
     while((TVSTAT & 8) == 8);
     
}

void wait_hblank(void)
{
    while((TVSTAT & 4) == 0);
    while((TVSTAT & 4) == 4);
}




void ss_main(void)
{
	Uint8 execGame=true;
	
	Uint8 fCount=0;
	t4=0;t1=0;t2=0;t3=0;t5=0;t6=0;t7=0;
	FormTbl=tex_blueSkyTextureList;
	slInitSystem(TV_320x240, FormTbl , 1);
    
    init_CD();
    init_VDP2();
    initFade();
    sndInit();
    CDDA_init();    
    slSlaveOn();
    

    
	while(execGame==true){
        resetTime();
        t1=SDL_GetTicks();
       
        slUnitMatrix(CURRENT);
        slLookAt(cmbuf.pos , cmbuf.target , cmbuf.ang[Z]);           
	    slPushMatrix();
        {
            game();
       
		}
        slPopMatrix();
        
        if(CDDA_getStatus()==6) {
            execGame=false;
        }
        
        t2=SDL_GetTicks();
//        t6=t2;
        fCount++;        
        t3 = t2 - t1;
        
        slSynch();

        if(t6 >= 59999) {
                t6=0;
                actualMinute = actualMinute + 1;            
        }

        while (t3<35) { 
 
            slUnitMatrix(CURRENT);
            slLookAt(cmbuf.pos , cmbuf.target , cmbuf.ang[Z]);

    	    slPushMatrix();
            {
                game();
       
		    }
            slPopMatrix();
            t2=SDL_GetTicks();
            t3 = t2 - t1;
            t4 = t4 + t3;
            slSynch();
        }
        
        t6 = t6 + t3;
        t7 = t7+ t3;
        
        actualSecond = t6/1000;

	}
	SYS_Exit(0);
}

