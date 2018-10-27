//***********************************************************************************//
//																//
//				CD Implementation Header								//
//																//
//				For load data from CD									//
//																//
//																//	
//***********************************************************************************//
#include "SEGA_GFS.H"
#define   OPEN_MAX  (Sint32)15
#define   DIR_MAX   (Sint32)80   
// keep this info global
GfsDirTbl gfsDirTbl;
GfsDirName gfsDirName[DIR_MAX];
Uint32 gfsLibWork[GFS_WORK_SIZE(OPEN_MAX)/sizeof(Uint32)];     
// number of files in current directory
Sint32 gfsDirN;

void init_CD()
{
    GFS_DIRTBL_TYPE(&gfsDirTbl) = GFS_DIR_NAME;
    GFS_DIRTBL_DIRNAME(&gfsDirTbl) = gfsDirName;
    GFS_DIRTBL_NDIR(&gfsDirTbl) = DIR_MAX;
    gfsDirN = GFS_Init(OPEN_MAX, gfsLibWork, &gfsDirTbl);
};
