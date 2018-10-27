#include	"dialogs.h"
#include	"font_spr_attr.h"
#include	"global.h"

#define OFFSET 8
Uint8 joyIndex;
Sprites SPR_LETTER;
Sprites SPR_SPCHAR;
Sprites SPR_DIAG1,SPR_DIAG2;
Uint8 dialogIndex=0;
Uint8 dialogDelay=0;

char *dialogIntro[]= {"¡RÍNG! ¡RING!",   
"\03SONIC: ¿QUIÉN DEMONIOS \nLLAMARÁ TAN TEMPRANO?", 
"\02SONIC: ¿DIGA?",
"\31TAILS: HOLA, SONIC.",
"\01SONIC: AH TAILS, ERES TÚ...\n¿QUÉ OCURRE? JA, JA, NO ME DIGAS \nQUE OTRO DE TUS EXPERIMENTOS \nHA FALLADO OTRA VEZ.",
"\31TAILS: ¡NO!..... ¡ES EGGMAN!",
"\02SONIC: ¿EGGMAN? \n¿QUÉ HA HECHO AHORA?",
"\31TAILS: POR CASUALIDAD... \nCAPTÉ UNA SEÑAL...\nLA ESMERALDA DEL CAOS...",
"\02SONIC: ESPERA, \n¿LA ESMERALDA DEL CAOS? \nNO TE OIGO, \nSE VA LA CONEXIÓN.",
"\30TAILS: ... TIENES QUE VENIR... \nA MI LABORATORIO YA MISMO... \nSI NO...",
"¡CLIC! BIIIIIIP... \nBIIIIIIP... \nBIIIIIIP...",
"\01SONIC: BUENO, \nMÁS VALE QUE HAGA ALGO. \nYA ME ESTABA ABURRIENDO, \nASÍ QUE...",
 };
 
 char *dialogGhlvl3[]= {"SONIC: 'Â¿QUÉ HACE ESE ROBOT?'",
"TAILS: 'Â¡Â¡SOCORRO!! Â¡Â¡SONIC!!'",
">EGGMAN: 'Â¡TÚ OTRA VEZ! Â¡SIEMPRE TIENES QUE ESTAR EN MEDIO!'",
"DSONIC: 'Â¡EGGMAN! TÚ... Â¿A DÓNDE TE CREES QUE TE LLEVAS A TAILS?'",
"<EGGMAN: JA JA JA. Â¡VOY A DARTE UNA BUENA LECCIÓN, CHAVAL!",
"ZSONIC: 'MMM... Â¿DE VERDAD CREES QUE TE PUEDES DESHACER DE MI HUYENDO EN UN HELICÓPTERO?'",
 };
 
 char *dialogSkylvl3[]={"!SONIC: 'Â¿DÓNDE ESTÁ EGGMAN?'",
"WSONIC: 'Â¿PERO QUÉ...? Â¿UNA FORTALEZA VOLANTE? EGGMAN DEBE DE ESTAR AHÍ DENTRO...'",
 };
 


void drawString(char txt[], FIXED x, FIXED y) {

Sint8 frame,sFrame,i;
Sint8 sprDiag1,sprDiag2,crlf;

SPR_LETTER.pos[X]=x;
SPR_LETTER.pos[Y]=y;
SPR_LETTER.pos[Z]=toFIXED(169.0);
SPR_LETTER.pos[S]=toFIXED(1.0);
SPR_LETTER.ang=DEGtoANG(0.0);

SPR_SPCHAR = SPR_LETTER;

SPR_SPCHAR.pos[Y]=SPR_SPCHAR.pos[Y]-toFIXED(5.0);


    SPR_DIAG1.pos[X]=toFIXED(-110.0);
    SPR_DIAG2.pos[X]=toFIXED(90.0);
    SPR_DIAG1.pos[Y]=toFIXED(20.0);
    SPR_DIAG2.pos[Y]=toFIXED(20.0);
    SPR_DIAG1.pos[Z]=SPR_DIAG2.pos[Z]=toFIXED(169.0);
    SPR_DIAG1.pos[S]=SPR_DIAG2.pos[S]=toFIXED(1.0);
    SPR_DIAG1.ang = SPR_DIAG2.ang = DEGtoANG(0.0);
    


 for(i=0;i<strlen(txt);i++)
    {   crlf=FALSE;
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
            
            case 'á':
            case 'Á':sFrame=7;
            case 'a':
            case 'A':frame=0+OFFSET; break;
                
            case 'b':
            case 'B':frame=1+OFFSET; break;
            
            case 'c':
            case 'C':frame=2+OFFSET; break;
            
            case 'd':
            case 'D':frame=3+OFFSET; break;
            
            case 'é':
            case 'É':sFrame=7;
            case 'e':
            case 'E':frame=4+OFFSET; break;
            
            case 'f':
            case 'F':frame=5+OFFSET; break;
            
            case 'g':
            case 'G':frame=6+OFFSET; break;
            
            case 'h':
            case 'H':frame=7+OFFSET; break;
            
            case 'í':
            case 'Í':sFrame=7;
            case 'i':
            case 'I':frame=8+OFFSET; break;
            
            case 'j':
            case 'J':frame=9+OFFSET; break;
            
            case 'k':
            case 'K':frame=10+OFFSET; break;
            
            case 'l':
            case 'L':frame=11+OFFSET; break;
            
            case 'm':
            case 'M':frame=12+OFFSET; break;
            
            case 'n':
            case 'N':frame=13+OFFSET; break;
            
            case 'ó':
            case 'Ó':sFrame=7;
            case 'o':
            case 'O':frame=14+OFFSET; break;
            
            case 'p':
            case 'P':frame=15+OFFSET; break;
            
            case 'q':
            case 'Q':frame=16+OFFSET; break;
            
            case 'r':
            case 'R':frame=17+OFFSET; break;
            
            case 's':
            case 'S':frame=18+OFFSET; break;
            
            case 't':
            case 'T':frame=19+OFFSET; break;
            
            case 'ú':
            case 'Ú':sFrame=7;
            case 'u':
            case 'U':frame=20+OFFSET; break;
            
            case 'v':
            case 'V':frame=21+OFFSET; break;
            
            case 'w':
            case 'W':frame=22+OFFSET; break;
            
            case 'x':
            case 'X':frame=23+OFFSET; break;
            
            case 'y':
            case 'Y':frame=24+OFFSET; break;
            
            case 'z':
            case 'Z':frame=25+OFFSET; break;
            
            case 'ñ':
            case 'Ñ':frame=13+OFFSET;sFrame=6; break;
            case '¿':frame=2; break;
            case '?':frame=3; break;
            case '!':frame=0; break;
            case '¡':frame=1; break;
            case ',':frame=4; break;
            case '.':frame=5; break;
            case ':':frame=5;sFrame=5; break;
            
            case ' ': frame=-1;break;
           
            case '\n': crlf= 1;break;
            
            case '\01': 
                        sprDiag1=TRUE;
                        SPR_DIAG1.spriteID=38;
                        break;
            case '\02': 
                        sprDiag1=true;
                        SPR_DIAG1.spriteID=39;
                        break;
            case '\03': 
                        sprDiag1=true;
                        SPR_DIAG1.spriteID=40;
                        break;
            case '\04': 
                        sprDiag1=true;
                        SPR_DIAG1.spriteID=41;
                        break;                                  
            case '\30': 
                        sprDiag2=true;
                        SPR_DIAG2.spriteID=42;
                        break;                                  
            case '\31': 
                        sprDiag2=true;
                        SPR_DIAG2.spriteID=43;
                        break;                                  
            case '\32': 
                        sprDiag2=true;
                        SPR_DIAG2.spriteID=44;
                        break;                                  
            case '\20': 
                        sprDiag2=true;
                        SPR_DIAG2.spriteID=35;
                        break;                                  
            case '\21': 
                        sprDiag2=true;
                        SPR_DIAG2.spriteID=36;
                        break;                                  
            case '\22': 
                        sprDiag2=true;
                        SPR_DIAG2.spriteID=37;
                        break;                                  


            

        }
        
        
        if(crlf==true) {
      		 SPR_LETTER.pos[Y]=SPR_LETTER.pos[Y]+toFIXED(15.0);
      		 SPR_SPCHAR.pos[Y]=SPR_SPCHAR.pos[Y]+toFIXED(15.0);
      		 SPR_LETTER.pos[X]=x;
        } else {
            if(sprDiag1==true ||sprDiag2==true) {
                }else {
                    SPR_LETTER.pos[X]=SPR_LETTER.pos[X]+toFIXED(9.0);
                    SPR_SPCHAR.pos[X]=SPR_LETTER.pos[X];
                }
             
        }
    
    
	        if(sprDiag1==true || sprDiag2==true){
                if(sprDiag1==true){
                    attr_Font[0].texno=SPR_DIAG1.spriteID;
                    SPR_DIAG1.pos[Y] = SPR_DIAG1.pos[Y] - toFIXED(spriteVsize(SPR_DIAG1.spriteID)  );
                    slDispSprite(SPR_DIAG1.pos, attr_Font , SPR_DIAG1.ang);
                    sprDiag1=FALSE;
                }else {
                    attr_Font[0].texno=SPR_DIAG2.spriteID;
                    SPR_DIAG2.pos[Y] = SPR_DIAG2.pos[Y] - toFIXED(spriteVsize(SPR_DIAG2.spriteID)  );
                    sprDiag2=FALSE;
                    slDispSprite(SPR_DIAG2.pos, attr_Font , SPR_DIAG2.ang);                
                }

                
                
                
            } else if(frame>=0) {
                    attr_Font[0].texno=frame;
                    slDispSprite(SPR_LETTER.pos, attr_Font , SPR_LETTER.ang);
                }
            if(sFrame>0) {
                    attr_Font[0].texno=sFrame;
                    slDispSprite(SPR_SPCHAR.pos, attr_Font , SPR_SPCHAR.ang);
                    sFrame=-1;
            }
            
            
            

	}
}    

void loadDialog() {
    
    loadBitMap("STREET.BIN",29814,240,320);

}

void loadSpriteDialog() {
    loadSprites("DIALOGS.BIN",64240,119168);
    setTextureList(8);
}

Uint8 showDialog() {
    

    
    drawString(dialogIntro[dialogIndex], toFIXED(-150.0), toFIXED(40.0));
   
    if( ((Smpc_Peripheral[joyIndex].pull & PER_DGT_TA) == 0) || 
        ((Smpc_Peripheral[joyIndex].pull & PER_DGT_TB) == 0) ||
        ((Smpc_Peripheral[joyIndex].pull & PER_DGT_TC) == 0) ) {
            dialogIndex++;
            if(dialogIndex>11) {
                dialogIndex = 0;
                return true;
            } 
    }
    if( (Smpc_Peripheral[joyIndex].pull & PER_DGT_ST) == 0 ) {
        return true;
    } 

    return false;
    
}
