
#include	"sgl.h"
#include	"global.h"
#include	"defines.h"


Sint8 ringAnimation[] = {55,56,57,58,59,-58,-57,-56};
Sint8 ringStarAnimation[] = {60,61,62};
Sint8 springAnimation[] = {53,52,54,53};
Sint8 bonusPointAnimation[] = {41,42,43};
Sint8 platformAnimation[] = {36};
Sint8 platformAnimationDestruct[] = {37,38,39};
Sint8 platformAnimationSpikes[] = {40};
Sint8 arrowJumpAnimation[] = {44,45,46};
Sint8 endStageAnimation[] = {112,113,116,114,115,-114,116,117,118};
Sint8 checkPointAnimation[] = {105,106,107,108,109,110,111};
Sint8 checkPointAnimation2[] = {105,111};

//Brief constants
Sint8 brief_sonicAnimation[] = {119};
Sint8 brief_msg_pass_Animation[] = {120};
Sint8 brief_bonusAnimation[] = {124};
Sint8 brief_ringAnimation[] = {125};
Sint8 brief_timeAnimation[] = {126};

Uint8 levelMapGreenHill[130][10];



extern GameActor Sonic, eggMan, bossWeapon, enemy[],explode;;
            
GameActor   rings[100], arrowJump[10], 
            platforms[100], spring[10], endStage, 
            briefLine[10],bonusPoint[10], checkPoint[1];

extern GameLevel   level;
extern baseBackground;

extern  Sprites BRIEF_CHARNAME,
        BRIEF_MSG_PASS,BRIEF_MSG_ACT,
        BRIEF_RING,BRIEF_BONUS,BRIEF_TIME;

extern  Sprites BLUE_LABEL[],
        WHITE_LABEL,
        SONIC_LABEL,
        NAME_LABEL[];

Sprites SPR_BACK,SPR_HUD;



void loadLevelIntro(Uint8 act) {
    Uint8 i = 0;
    for(i=0; i<8; i++) {
        BLUE_LABEL[i].spriteID = 128;
        BLUE_LABEL[i].pos[X]=toFIXED(0.0);
        BLUE_LABEL[i].pos[Y]=toFIXED(0.0);
        BLUE_LABEL[i].pos[Z]=toFIXED(169.0);
        BLUE_LABEL[i].pos[S]=toFIXED(1.0);
        BLUE_LABEL[i].ang=DEGtoANG(0.0);
    }
    BLUE_LABEL[0].pos[Y]=toFIXED(0.0);
    for (i=1; i<8; i++) {
        BLUE_LABEL[i].pos[Y]=BLUE_LABEL[i -1].pos[Y] + toFIXED(32.0);
    }
    
    for(i=0; i<2; i++) {
        NAME_LABEL[i].spriteID = 129;
        NAME_LABEL[0].pos[X]=toFIXED(0.0);
        NAME_LABEL[1].pos[X]=toFIXED(160.0);
        NAME_LABEL[i].pos[Y]=toFIXED(170.0);
        NAME_LABEL[i].pos[Z]=toFIXED(169.0);
        NAME_LABEL[i].pos[S]=toFIXED(1.0);
        NAME_LABEL[i].ang=DEGtoANG(0.0);

    }

    SONIC_LABEL.spriteID = 130;
    SONIC_LABEL.pos[X]=toFIXED(20.0);
    SONIC_LABEL.pos[Y]=toFIXED(0.0);
    SONIC_LABEL.pos[Z]=toFIXED(169.0);
    SONIC_LABEL.pos[S]=toFIXED(1.0);
    SONIC_LABEL.ang=DEGtoANG(0.0);
    
    WHITE_LABEL.spriteID = 121;

    switch(act) {
        case 1:
                WHITE_LABEL.spriteID = 121;
            break;
        case 2:
                WHITE_LABEL.spriteID = 122;
            break;
        case 3:
                WHITE_LABEL.spriteID = 123;
            break;        
    }

    WHITE_LABEL.pos[X]=toFIXED(260.0);
    WHITE_LABEL.pos[Y]=toFIXED(190.0);
    WHITE_LABEL.pos[Z]=toFIXED(169.0);
    WHITE_LABEL.pos[S]=toFIXED(1.0);
    WHITE_LABEL.ang=DEGtoANG(0.0);

}

void loadBriefScreen(Uint8 act) {
    
    BRIEF_CHARNAME.spriteID = brief_sonicAnimation[0];
    BRIEF_CHARNAME.pos[X]=toFIXED(30.0);
    BRIEF_CHARNAME.pos[Y]=toFIXED(60.0);
    BRIEF_CHARNAME.pos[Z]=toFIXED(169.0);
    BRIEF_CHARNAME.pos[S]=toFIXED(1.0);
    BRIEF_CHARNAME.ang=DEGtoANG(0.0);
    
    BRIEF_MSG_PASS.pos[X]=toFIXED(95.0);
    BRIEF_MSG_PASS.pos[Y]=toFIXED(68.0);
    BRIEF_MSG_PASS.pos[Z]=toFIXED(169.0);
    BRIEF_MSG_PASS.pos[S]=toFIXED(1.0);
    BRIEF_MSG_PASS.ang=DEGtoANG(0.0);    
    
    BRIEF_MSG_ACT.pos[X]=toFIXED(210.0);
    BRIEF_MSG_ACT.pos[Y]=toFIXED(68.0);
    BRIEF_MSG_ACT.pos[Z]=toFIXED(169.0);
    BRIEF_MSG_ACT.pos[S]=toFIXED(1.0);
    BRIEF_MSG_ACT.ang=DEGtoANG(0.0);    
    
    BRIEF_RING.pos[X]=toFIXED(95.0);
    BRIEF_RING.pos[Y]=toFIXED(100.0);
    BRIEF_RING.pos[Z]=toFIXED(169.0);
    BRIEF_RING.pos[S]=toFIXED(1.0);
    BRIEF_RING.ang=DEGtoANG(0.0);  
        
    BRIEF_BONUS.pos[X]=toFIXED(95.0);
    BRIEF_BONUS.pos[Y]=toFIXED(130.0);
    BRIEF_BONUS.pos[Z]=toFIXED(169.0);
    BRIEF_BONUS.pos[S]=toFIXED(1.0);
    BRIEF_BONUS.ang=DEGtoANG(0.0);  
        
    BRIEF_TIME.pos[X]=toFIXED(95.0);
    BRIEF_TIME.pos[Y]=toFIXED(160.0);
    BRIEF_TIME.pos[Z]=toFIXED(169.0);
    BRIEF_TIME.pos[S]=toFIXED(1.0);    
    BRIEF_TIME.ang=DEGtoANG(0.0);  
    
    BRIEF_MSG_PASS.spriteID = brief_msg_pass_Animation[0];
    
    BRIEF_MSG_ACT.spriteID = 121;
        switch(act) {
        case 1:
                BRIEF_MSG_ACT.spriteID = 121;
            break;
        case 2:
                BRIEF_MSG_ACT.spriteID = 122;
            break;
        case 3:
                BRIEF_MSG_ACT.spriteID = 123;
            break;        
    }
    
    BRIEF_BONUS.spriteID = brief_bonusAnimation[0];
    BRIEF_RING.spriteID = brief_ringAnimation[0];
    BRIEF_TIME.spriteID = brief_timeAnimation[0];
}

void platformAnim()
{   Uint8 i;
    for(i=0;i<level.platformTotal;i++)
    {
       platforms[i].animation=platformAnimation;
       platforms[i].animIndex=0;
       platforms[i].animEnd=sizeof(platformAnimation)/sizeof(Uint8)-1;
       
       //checking type from fist load examplo 21, is Type2 and autoMoveX 1
       //platforms[i].type=PLATFORM_TYPE_NORMAL;
       
       switch(platforms[i].type) {
            case 10 :   platforms[i].type = PLATFORM_TYPE_NORMAL;
                        platforms[i].autoMoveX=0;
                break;
            case 20 :   platforms[i].type = PLATFORM_TYPE_DESTRUCTIBLE;
                        platforms[i].autoMoveX=0;
                break;
            case 30 :   platforms[i].type = PLATFORM_TYPE_SPIKES;
                        platforms[i].autoMoveX=0;
                break;
        }
       
       
       platforms[i].lives=1;
       platforms[i].state=GAMEACTOR_STATUS_GO_LEFT;

       
       if(platforms[i].type == PLATFORM_TYPE_DESTRUCTIBLE) {
            platforms[i].animation=platformAnimationDestruct;
            platforms[i].animEnd=sizeof(platformAnimationDestruct)/sizeof(Uint8)-1;
        }
       if(platforms[i].type == PLATFORM_TYPE_SPIKES) {
            platforms[i].animation=platformAnimationSpikes;
            platforms[i].animEnd=sizeof(platformAnimationSpikes)/sizeof(Uint8)-1;
        }
       
       platforms[i].animTimeCurrent=0;
       platforms[i].animTimeLength=5;
	   platforms[i].SPR_GA.cHeight=toFIXED(2.0);
	   platforms[i].SPR_GA.cWeight=toFIXED(48.0*0.9);
	   platforms[i].SPR_GA.colVecSize[0] = toFIXED(2.0);
   	   platforms[i].SPR_GA.colVecSize[1] = toFIXED(48.0*0.9);
  	   platforms[i].SPR_GA.colVecSize[2] = toFIXED(4.0);
   	   platforms[i].SPR_GA.colVecSize[3] = toFIXED(48.0*0.9);
	   

    }
    
}
void bonusPointAnim() {
    Uint8 i;
    for(i=0;i<level.bonusPointTotal;i++) {
       bonusPoint[i].animation=bonusPointAnimation;
       bonusPoint[i].animIndex=0;
       bonusPoint[i].animEnd=sizeof(bonusPointAnimation)/sizeof(Uint8)-1;
       bonusPoint[i].animTimeCurrent=0;
       bonusPoint[i].animTimeLength=5;
       bonusPoint[i].animEnabled = false;
       bonusPoint[i].SPR_GA.collide= false;
	   bonusPoint[i].SPR_GA.cHeight=toFIXED(24.0);
	   bonusPoint[i].SPR_GA.cWeight=toFIXED(72.0);
    }
    
}

void springAnim() {
    Uint8 i;
    for(i=0;i<level.springTotal;i++) {
       spring[i].animation=springAnimation;
       spring[i].animIndex=0;
       spring[i].animEnd=sizeof(springAnimation)/sizeof(Uint8)-1;
       spring[i].animTimeCurrent=0;
       spring[i].animTimeLength=2;
       spring[i].SPR_GA.collide = false;
       spring[i].animEnabled = false;
	   spring[i].SPR_GA.cHeight=toFIXED(18.0);
	   spring[i].SPR_GA.cWeight=toFIXED(48.0);

    }
    
}


void loadRings() {   
    Uint8 i;
    for(i=0;i<level.ringTotal;i++) {  
       rings[i].animation=ringAnimation;
       rings[i].animIndex=0;
       rings[i].animEnd=sizeof(ringAnimation)/sizeof(Uint8)-1;
       rings[i].animTimeCurrent=0;
       rings[i].animTimeLength=3;
       rings[i].lives=1;
       rings[i].state=0;
       rings[i].animEnabled= true;
       rings[i].SPR_GA.collide=false;
	   rings[i].SPR_GA.cHeight=toFIXED(16.0);
	   rings[i].SPR_GA.cWeight=toFIXED(16.0);
    }
    
}
//ArrowJump config
void loadArrowJump() {   
    Uint8 i;
    
    for(i=0;i<level.ArrowJumpTotal;i++) {

        arrowJump[i].animation=arrowJumpAnimation;
        arrowJump[i].animIndex=0;
        arrowJump[i].animEnd=sizeof(arrowJumpAnimation)/sizeof(Uint8)-1;
        arrowJump[i].animTimeCurrent=0;
        arrowJump[i].animTimeLength=2;
        arrowJump[i].SPR_GA.collide = false;
        arrowJump[i].animEnabled = false;
        arrowJump[i].SPR_GA.cHeight=toFIXED(24.0);
        arrowJump[i].SPR_GA.cWeight=toFIXED(72.0);

    }
    
}

void loadEndStage() {   
    endStage.animation=endStageAnimation;
    endStage.animIndex=0;
    endStage.animEnd=sizeof(endStageAnimation)/sizeof(Uint8)-1;
    endStage.animTimeCurrent=0;
    endStage.animTimeLength=2;
    endStage.SPR_GA.collide=false;
    endStage.SPR_GA.cHeight=toFIXED(40.0);
	endStage.SPR_GA.cWeight=toFIXED(48.0);
    
}
void loadCheckPoint() {   
    checkPoint[0].animation=checkPointAnimation;
    checkPoint[0].animIndex=0;
    checkPoint[0].animEnd=sizeof(checkPointAnimation)/sizeof(Uint8)-1;
    checkPoint[0].animTimeCurrent=0;
    checkPoint[0].animTimeLength=10;
    checkPoint[0].SPR_GA.collide=false;
    checkPoint[0].SPR_GA.cHeight=toFIXED(48.0);
	checkPoint[0].SPR_GA.cWeight=toFIXED(16.0);
    checkPoint[0].state = 0;    
}

void loadDefaultActor(GameActor *temp){
    temp->animIndex=0;
    temp->animTimeCurrent=0;
    temp->animTimeLength=5;
    temp->SPR_GA.collide=false;
    temp->autoMoveX = 0;
    temp->SPR_GA.pos[Z] = toFIXED(169.0);
}

void loadBrief() {
   
    
    loadDefaultActor(&briefLine[0]);
    briefLine[0].animIndex = 119;
    briefLine[1].animIndex = 120;
    briefLine[2].animIndex = 121;
    briefLine[3].animIndex = 122;
    briefLine[4].animIndex = 123;
    briefLine[5].animIndex = 124;
    briefLine[6].animIndex = 125;
    briefLine[7].animIndex = 126;
    
    
}

void changeCheckPointAnimation(Uint8 index) {
    checkPoint[index].animation=checkPointAnimation2;
    checkPoint[index].animIndex=0;
    checkPoint[index].animEnd=sizeof(checkPointAnimation2)/sizeof(Uint8)-1;
    checkPoint[index].animTimeLength=20;
    checkPoint[index].state = 1;
    checkPoint[index].animEnabled = true;
}


void levelAttributes(char str[50]) {
    
    Uint8 index=0,indexBuffer=0,token=0;
    GameActor temp;

    char bufferToken1[5];
    do{
        bufferToken1[indexBuffer]=str[index];
        indexBuffer++;
         #ifdef DEBUG
         slPrint("                                                               ",slLocate(0,12));
         slPrint(str,slLocate(0,12));
         #endif
        if(str[index]==',' || str[index]==';' ) {
            token++;
            switch(token) {
                case 1:
                    level.ringTotal=atoi(bufferToken1); 
                    #ifdef DEBUG 
                    slPrintHex(slHex2Dec(level.ringTotal),slLocate(5,token));
                    slPrint("Rings:",slLocate(0,token));
                    #endif
                break;
                case 2:
                    level.platformTotal=atoi(bufferToken1);
                    #ifdef DEBUG 
                    slPrintHex(slHex2Dec(level.platformTotal),slLocate(5,token));
                    slPrint("Platf:",slLocate(0,token));
                    #endif
                    break;
                case 3:
                    level.springTotal=atoi(bufferToken1);
                    #ifdef DEBUG 
                    slPrintHex(slHex2Dec(level.springTotal),slLocate(5,token));
                    slPrint("Sprin:",slLocate(0,token));
                    #endif
                    break;
                case 4:
                    level.enemyTotal=atoi(bufferToken1);
                    #ifdef DEBUG 
                    slPrintHex(slHex2Dec(level.enemyTotal),slLocate(5,token));
                    slPrint("Enemy:",slLocate(0,token));
                    #endif
                    break;
                case 5:
                    level.ArrowJumpTotal=atoi(bufferToken1); 
                    #ifdef DEBUG 
                    slPrintHex(slHex2Dec(level.ArrowJumpTotal),slLocate(5,token));
                    slPrint("ArroJ:",slLocate(0,token));
                    #endif
                    break;
                case 6:
                    level.bonusPointTotal=atoi(bufferToken1);
                    #ifdef DEBUG 
                    slPrintHex(level.bonusPointTotal,slLocate(5,token));
                    slPrint("BonP:",slLocate(0,token));
                    #endif
                    break;
                case 7:
                    level.heroTotal=atoi(bufferToken1);
                    #ifdef DEBUG 
                    slPrintHex(level.heroTotal,slLocate(5,token));
                    slPrint("Hero:",slLocate(0,token));
                    #endif
                    break;
                case 8:
                    level.checkPointTotal=atoi(bufferToken1);
                    #ifdef DEBUG 
                    slPrintHex(level.checkPointTotal,slLocate(5,token));
                    slPrint("ChkP:",slLocate(0,token));
                    #endif
                    break;
                case 9:
                    level.finalStageTotal=atoi(bufferToken1);
                    #ifdef DEBUG 
                    slPrintHex(level.finalStageTotal,slLocate(5,token));
                    slPrint("goals:",slLocate(0,token));
                    #endif
                    break;
                case 10:
                    level.bossTotal=atoi(bufferToken1);
                    #ifdef DEBUG 
                    slPrintHex(level.bossTotal,slLocate(5,token));
                    slPrint("Boss:",slLocate(0,token));
                    #endif
                break;
                
                }
            indexBuffer=0;
        }
        index++; 
    }while(str[index]!=';');
}
GameActor trasnlateLine(char str[15] ){ 
    Uint8 index=0,indexBuffer=0,token=0;
    GameActor temp;

    char bufferToken1[10];

do{
    bufferToken1[indexBuffer]=str[index];
    indexBuffer++;
    
    if(str[index]==',' || str[index]==';' ) {
        token++;
        
        switch(token)
        {
            case 1: 
                temp.SPR_GA.pos[X]=toFIXED(atoi(bufferToken1)); 
            break;
            case 2:
                temp.SPR_GA.pos[Y]=toFIXED(atoi(bufferToken1));
            break;
            case 3: 
                temp.type=atoi(bufferToken1); 
            break;
        }
        indexBuffer=0;
        
        
    }
    index++;
    

 
}while(str[index]!=';');
     
     temp.SPR_GA.pos[Z]=toFIXED(160.0);
     temp.SPR_GA.pos[S]=toFIXED(1.0);
     temp.SPR_GA.ang=DEGtoANG(0.0);  
   
     return temp; 
}

void trasnlateLineBG(char str[40],Uint8 matrixIndex){ 
    Uint8 index=0,indexBuffer=0,token=0;

    char strBuffer[40];

    do{
        strBuffer[indexBuffer]=str[index];
        indexBuffer++;

        if(str[index]==',' || str[index]==';' ) {

            levelMapGreenHill[matrixIndex][token] = atoi(strBuffer);

            token++;
            indexBuffer=0;
        }
        index++;
    }while(str[index]!=';');

}

void loadBackgroundMap(char fileName[10]) {

    Uint32 i=0;
    Uint8 j=0;
    Uint8 number=0;
    char   *txt[6000];
    char   txt2[6000];
    Uint8 parser[40];
    Sint32 loadTxt;
    
    Uint8 totalTokens = 0;
    Uint8 matrixIndex = 0;
    
    loadTxt = GFS_Load(GFS_NameToId(fileName), 0x0, txt, 6000);
    if(loadTxt<=0) {
        slPrint(fileName,slLocate(0,28));
    }
    memcpy(txt2,txt,6000);
    
    for(i=0;i<=strlen(txt2);i++) {
        parser[j]=txt2[i];
		j++;
		if(txt2[i]== ';') {
            slPrint(parser,slLocate(10,10));
            trasnlateLineBG(parser,matrixIndex);
            matrixIndex++;
		j=0;

		}
		
    }
    
}

void loadingMap(char fileName[10]) { 

    Uint32 i=0;
    Uint8 j=0;
    Uint8 number=0;
    char   *txt[4000];
    char   txt2[4000];
    Uint8 parser[20];
    Sint32 loadTxt;
    Uint8 loadState = 0;
    
    
    Uint8 totalTokens = 0;
    
    loadTxt = GFS_Load(GFS_NameToId(fileName), 0x0, txt, 4000);
    if(loadTxt<=0) {
        slPrint(fileName,slLocate(0,28));
    }
    memcpy(txt2,txt,4000);
    
    #ifdef DEBUG
        slPrint("Level:",slLocate(0,0));
        slPrint(fileName,slLocate(6,0));
    #endif
    for(i=0;i<=strlen(txt2);i++) {
        parser[j]=txt2[i];
        j++;
        if(txt2[i]== ';') {
            
            totalTokens++;
            j=0;
            switch(loadState) {
                case 0: 
                        levelAttributes(parser);
                        loadState = 1;
                        number = 0;
                        strcpy(parser, "");
                        break;
                        
                case 1: 
                        rings[number]=trasnlateLine(parser);
                        rings[number].lives=1;
                        number++;
                        if(number == level.ringTotal){ 
        					number=0;
                            loadState = 2;
                        }  
                        
                        break;
                case 2: 
                        platforms[number]=trasnlateLine(parser);
                        platforms[number].lives=1;
                        
                        #ifdef DEBUG 
                        //slPrintFX(platforms[number].SPR_GA.pos[Y],slLocate(20,number));
                        #endif 
                        number++;
                        if(number == level.platformTotal ) {
                            
        					number=0;
                            loadState = 3;
                        }
                        break;
                case 3: 
                        spring[number]=trasnlateLine(parser);
                        spring[number].lives=1;
                        number++;
                        if(number ==level.springTotal ) {
                            number=0;
                            loadState = 4;

                        }
                        break;
                case 4: 
                        enemy[number]=trasnlateLine(parser);
                        enemy[number].lives=1;
                        number++;
                        if(number ==level.enemyTotal ) {
                            number=0;
                            loadState = 5;
                            
                        }
                        strcpy(parser, "");
                        break;
                case 5: 

                        arrowJump[number]=trasnlateLine(parser);
                        arrowJump[number].lives=1;
                        number++;

                        if(number ==level.ArrowJumpTotal ) {
                            number=0;
                            loadState = 6;
                            
                        }
                        strcpy(parser, "");
                        break;
                case 6: 
                        bonusPoint[number]=trasnlateLine(parser);
                        bonusPoint[number].lives=1;
                        number++;
                        if(number ==level.bonusPointTotal ) {
                            number=0;
                            loadState = 7;

                        }
                        break;
				case 7: 
                        
                        Sonic=trasnlateLine(parser);
                        Sonic.lives=1;
                        number++;
                        
                        if(number ==level.heroTotal ) {
                            number=0;
                            loadState = 8;

                        }
                        break;
                case 8: 
                        checkPoint[number]=trasnlateLine(parser);
                        checkPoint[number].lives=1;
                        number++;
                        if(number ==level.checkPointTotal ) {
                            number=0;
                            loadState = 9;

                        }
                        if(level.heroTotal == 0) {
                            loadState = 9;
                        }
                        break;
                case 9: 
                        endStage=trasnlateLine(parser);
                        endStage.lives=1;
                        number++;
                        if(number ==level.finalStageTotal ) {
                            number=0;
                            loadState = 10;

                        }
                        
                       
                        break;
                case 10: 
                        eggMan=trasnlateLine(parser);
                        eggMan.lives=1;
                        number++;
                        if(number == level.bossTotal ) {
                            number=0;
                            loadState = 11;

                        }
                        
                       
                        break;
                        
                        
            }
         }
        
    }
}

void loadLevel(Uint8 stage)
{
    switch(stage)
	{
		case 1:    
			loadBitMap("BG1.BIN",26286,320,150);
            loadBackgroundMap("GH_BM.BIN");
			loadSprites("GHS.BIN",139782, 264592);
			setTextureList(1);

		break;
		case 2:
			loadBitMap("BG2.BIN",32732,240,320);
            loadBackgroundMap("SK_BM.BIN");
			loadSprites("SKS.BIN", 124950, 264400);
			setTextureList(2);
		break;
        case 3:    
            loadBitMap("BG3.BIN",57638,320,150);
            loadBackgroundMap("MC_BM.BIN");
            loadSprites("MCS.BIN", 132878, 266288);
            setTextureList(3);
		break;
		case 4:
			loadBitMap("BG4.BIN",25784,320,150);
            loadBackgroundMap("MN_BM.BIN");
			loadSprites("MNS.BIN", 157882, 264048);
            setTextureList(4);
		break;
		case 5:
			loadBitMap("BG5.BIN",32021,320,150);
			loadSprites("JGS.BIN",134932,261616);
            setTextureList(5);
		break;
		case 6:
			loadBitMap("BG5.BIN",32021,320,150);
			loadSprites("CZS.BIN",133082,262512);
            setTextureList(6);
		break;
		case 7:
		break;
		
	
	}
   slSynch(); 
}


void loadResourcesGameState(Uint8 gameState) {
    switch(gameState) {
        
        case GAME_STATE_PRESENTATION: 
             loadBitMap("SPLASH.BIN",74654,240,320);
             loadSpriteDialog();
             fadeIn();
             CDDA_stop();
             slSynch();
             CDDA_play(2);
             slSynch();
        break;
    }
}

void loadGameOver() {
    loadBitMap("GAMEOVER.BIN",19953,240,320);
}

void loadEnding() {
    loadBitMap("THANKS.BIN",22560,240,320);
}

void setLevel(Uint8 stage) {
    baseBackground = toFIXED(450.0);
    Uint8 act = 1;
    
    switch(stage) {
        case GHZ1:
                loadLevel(1);
                loadingMap("GH1.BIN");
                level.nTrack=TRK_GHZ;
                act = 1;
                
        break;
        case GHZ2:
                loadLevel(1);
                loadingMap("GH2.BIN");
                level.nTrack=TRK_GHZ;
                act = 2;
                
        break;
        case GHZ3:
                loadLevel(1);
                loadingMap("GH3.BIN");
                level.nTrack=TRK_GHZ;
                act = 3;
                
        break;
        case SKZ1:
                loadLevel(2);
                loadingMap("SK1.BIN");
                level.nTrack=TRK_SKZ;
                act = 1;
        break;
        case SKZ2:
                loadLevel(2);
                loadingMap("SK2.BIN");
                level.nTrack=TRK_SKZ;
                act = 2;
        break;
        case SKZ3:
                loadLevel(2);
                loadingMap("SK3.BIN");
                level.nTrack=TRK_SKZ;
                act = 3;
        break;
        case MCZ1:
                loadLevel(3);
                loadingMap("SK1.BIN");
                level.nTrack=TRK_MCZ;
                act = 1;
        break;
        case MCZ2:
                loadLevel(3);
                loadingMap("MC2.BIN");
                level.nTrack=TRK_MCZ;
                act = 2;
        break;
        case MCZ3:
                loadLevel(3);
                loadingMap("MC3.BIN");
                level.nTrack=TRK_MCZ;
                act = 3;
        break;
        case MNZ1:
                loadLevel(4);
                loadingMap("MN1.BIN");
                level.nTrack=TRK_MNZ;
                act = 1;
        break;
        case MNZ2:
                loadLevel(4);
                loadingMap("MN2.BIN");
                level.nTrack=TRK_MNZ;
                act = 2;
        break;
        case MNZ3:
                loadLevel(4);
                loadingMap("MN3.BIN");
                level.nTrack=TRK_MNZ;
                act = 3;
        break;
        case JGZ1:
                loadLevel(5);
                loadingMap("JG1.BIN");
                level.nTrack=TRK_JGZ;
                act = 1;
        break;
        case JGZ2:
                loadLevel(5);
                loadingMap("JG2.BIN");
                level.nTrack=TRK_JGZ;
                act = 2;
        break;
        case JGZ3:
                loadLevel(5);
                loadingMap("JG3.BIN");
                level.nTrack=TRK_JGZ;
                act = 3;
        break;
        case CSZ1:
                loadLevel(6);
                loadingMap("CS1.BIN");
                level.nTrack=TRK_CSZ;
                act = 1;
        break;
        case CSZ2:
                loadLevel(6);
                loadingMap("CS2.BIN");
                level.nTrack=TRK_CSZ;
                act = 2;
        break;
        case CSZ3:
                loadLevel(6);
                loadingMap("CS3.BIN");
                level.nTrack=TRK_CSZ;
                act = 3;
        break;
    }
    
    level.levelIntroOutAnimCounter = 20;
    level.levelTimeShowInScreen = 90;
    level.timeOutToChangeLevel = 180;
    level.restarLevel = false;
    
	heroStart();
    platformAnim();
    loadRings();
	enemyStart();
	loadArrowJump();
	springAnim();
	bonusPointAnim();
	loadEndStage();
	loadCheckPoint();
    loadBriefScreen(act);	
	loadLevelIntro(act);
}
