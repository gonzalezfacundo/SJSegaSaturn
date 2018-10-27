	//--------------------------------------------------------------------------
	/// Graphics stuff
	///	@FacundoARG
	//--------------------------------------------------------------------------

#include 	"DEHUFF.H"
#include 	"stdlib.h"
#include 	<SEGA_CMP.H>
//#include 	"texture_list.h"
#include 	"texture_greenHill.h"
#include 	"texture_dialog.h"
#include 	"texture_cosmiczone.h"
#include 	"texture_jungle.h"
#include 	"texture_mountain.h"
#include 	"texture_mech.h"
#include 	"texture_blueSky.h"

Sint16 r=0,g=0,b=0;
	//--------------------------------------------------------------------------
	/// Inits the VideoDisplayProcessor 2
	//--------------------------------------------------------------------------
void init_VDP2()
{
// the address for background color in VRAM is taken from various examples,
// don't know why
// !!! beware, 1st try the bgcol was the only thing to see on real Saturn
// what exactly is the back_col_adr? maybe the color at this adress is 
// interpreted as background color and wheereever such color occurs,
// it's replaced by the given one
// !! all i see is the background color....
    slBack1ColSet((void *)BACK_CRAM, CD_Black);
    
    
// the debug text lib take the NBG0 scroll <- the only one with 24bits color depth
// priority = 0 -> scroll not displayed
// take farest away    
    slPriorityNbg0(7);
    slPriorityNbg1(6);
//    slPrioritySpr0-7(0);    

// we want bitmap scrolls
// only NBG0 and NBG1 can handle bitmap mode
// color modes:
//      palettet:           COL_TYPE_16, COL_TYPE_256, COL_TYPE_2048
//      rgb:                COL_TYPE_32768, COL_TYPE_1M
// bitmap sizes(BM_HxV):    BM_512x256, BM_512x512, BM_1024x256, BM_1024x512
    slBitMapNbg1(COL_TYPE_32768, BM_512x256, (void *)VDP2_VRAM_A0);
//    memset((void *)VDP2_VRAM_A0, CD_Black, 256*512*2);

// monitor position in scroll coordinate space
// sets the position of monitors topleft corner(fixed format)
//    slScrPosNbg1(toFIXED(-33.680/2.0), toFIXED(0.0));
    slScrPosNbg1(toFIXED(0.0), toFIXED(0.0));

// reduction setting: only NGB0 and NBG1 are able to RBG, too)
// modes:   ZOOM_1, ZOOM_HALF, ZOOM_QUATER      each untill x256
    slZoomModeNbg1(ZOOM_1);
    
// zoom
// fixed point reziprocal of scale ratio in x and y direction
    slZoomNbg1(toFIXED(1.0), toFIXED(1.0));            

// registeres scrolls
// call only after all scroll function settings
// returns 0 or -1(ERROR)
    slScrAutoDisp(NBG0ON | NBG1ON);
}



	//--------------------------------------------------------------------------
	/// Inits the VideoDisplayProcessor 2
	///@video Ram Memmory
	///@with of memmory
	///@pointer of image
	///@heigth of image
	///@width of img
	/// line-by-line transfer to vram
	//--------------------------------------------------------------------------

void img2VRAM(Uint16 *vram, Uint16 vram_width, Uint16 *img, Uint16 img_height, Uint16 img_width)
{
    int i;
    Uint32 oVRAM = 0;
    Uint32 oIMG = 0;
    
    for(i = 0; i < img_height; i++) {
        memcpy((void *)(vram + oVRAM), (void *)(img + oIMG), img_width*sizeof(Uint16));
        oVRAM += vram_width;
        oIMG += img_width;
    }    
} 

void set_colorkey(Uint16 *p, Uint32 n, Uint16 transColor, Uint8 correctBlack)
{
    int i;

	for(i = 0; i < n; i++, p++) {
	    if((correctBlack == 1) && (*p == 0x0000))
	      *p = 0x8000;
        else if(*p == transColor)
            *p = 0x0000;
    }
}
	//--------------------------------------------------------------------------
	/// load a bitMap with compression to video ram 
	///@name of file, max 8 chars
	///@size of file
	///@heigth of image
	///@width of img
	//--------------------------------------------------------------------------
	
void loadBitMap(char name[8], Uint32 size,Uint32 heigth, Uint32 weigth)
{
// load from CD into an allocated buffer, decompress and display the
// background image
	void *buffer = malloc(size);
	Uint8 *adr = (Uint8 *)0x200000;
	Sint32 load;

	load = GFS_Load(GFS_NameToId(name), 0, (Uint32 *)buffer, size);
	if(load <= 0)	{
		slPrint("Error loadBitMap: ", slLocate(2,20));
		slPrint(name, slLocate(2,21));
	}//display_Error("ERROR loading file LAVA.BIN!", 1);
	if(DeHuff(buffer, (void *)adr) != 0)
	{}//display_Error("ERROR decompressing file LAVA.BIN!", 1);
    slTVOff();
	img2VRAM((Uint16 *)VDP2_VRAM_A0, 512, (Uint16 *)(0x200000), heigth, weigth);
	slTVOn();

	free(buffer);
}

	//--------------------------------------------------------------------------
	/// set sprites to video ram 
	///@pointer of picture
	///@numbers of pictures
	///@pointer of texture
	//--------------------------------------------------------------------------

static void set_sprite(PICTURE *pcptr, Uint32 NbPicture, TEXTURE *texptr)
{
	TEXTURE *txptr;
 
	for(; NbPicture-- > 0; pcptr++){
		txptr = texptr + pcptr->texno;
		slDMACopy((void *)pcptr->pcsrc,
			(void *)(SpriteVRAM + ((txptr->CGadr) << 3)),
			(Uint32)((txptr->Hsize * txptr->Vsize * 4) >> (pcptr->cmode)));
	}
}

void setTextureList(Uint8 indexTable)
{
switch(indexTable)
    {
	   case 1  :   FormTbl=tex_greenHillTextureList;
	       break;
	   case 2  :   FormTbl=tex_blueSkyTextureList;
	       break;
	   case 3  :   FormTbl=tex_mechZoneTextureList;
	       break;
       case 4  :   FormTbl=tex_mountainTextureList;
	       break;
       case 5  :   FormTbl=tex_jungleZoneTextureList;
	       break;
       case 6  :   FormTbl=tex_cosmicZoneTextureList;
	       break;
	   case 8  :   FormTbl=tex_Dialog;
    }
    
}

	//--------------------------------------------------------------------------
	/// load sprites binary file, decompress and set to video ram 
	///@name of file, max 8 chars
	///@size of file
	///@number of pixels in bytes, pixels x 2
	//--------------------------------------------------------------------------


void loadSprites(char name[8], Uint32 fileSize, Uint32 nPixels)
{
void *buffer = malloc(fileSize);
	Uint8 *adr = (Uint8 *)0x200000;
	Sint32 load;
	
	load = GFS_Load(GFS_NameToId(name), 0, (Uint32 *)buffer, fileSize);
    if(load <= 0)   {
        slPrint("Error loadSprites: ", slLocate(2,20));
        slPrint(name, slLocate(2,21));
        }
    // I know it's word unit
    void *out = adr;
	if(CMP_DecRunlenWord(buffer, &out, 0x200000) != CMP_DEC_OK) 
        slPrint("ERROR decompressing Sprites",  slLocate(2,21));
    set_colorkey((Uint16 *)adr, nPixels/2, 0xc01f, 0);
    // this assumes consecutive character pattern order in VRAM
    // like 3DEditor usually generates it by default
	
    slDMACopy((void *)adr, (void *)(SpriteVRAM + CGADDRESS), (Uint32)nPixels);
free(buffer);
}
Uint16 spriteHsize(Uint8 index) {
    return FormTbl[index].Hsize;
}
Uint16 spriteVsize(Uint8 index) {
    return FormTbl[index].Vsize;
}

void initFade() {
    slColOffsetOn(NBG0ON|NBG1ON|NBG2ON|NBG3ON|RBG0ON|LNCLON|BACKON|SPRON);
    slColOffsetAUse(NBG0ON|NBG1ON|NBG2ON|NBG3ON|RBG0ON|LNCLON|BACKON|SPRON);
    slColOffsetBUse(NBG0ON|NBG1ON|NBG2ON|NBG3ON|RBG0ON|LNCLON|BACKON|SPRON);
}

Uint8 fadeOut() {
    
    if(r==-255 && g==-255 && b==-255) {
        return true;
    }

    r-=10; g-=10;b-=10;
    
    if(r<=-255) { 
        r=-255;
    }
    if(g<=-255) { 
        g=-255;
    }
    if(b<=-255) { 
        b=-255;
    }
    slColOffsetB(r,g,b);
    
   return false;
}

void fadeIn() {
    
    r=0; g=0;b=0;
    slColOffsetB(r,g,b);

}
