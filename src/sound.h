	//--------------------------------------------------------------------------
	/// Sound Implementation
	/// PCM and CDDA
	///	@FacundoARG
	//--------------------------------------------------------------------------

#include    "soundheader.h"


Sounds snd_sfx[10];
PCM chn_0_m8 = {(_Mono | _PCM8Bit) , 3 , 127 , 0 , 0x0 , 0 , 0 , 0 , 0};
PCM chn_1_m8 = {(_Mono | _PCM8Bit) , 3 , 127 , 0 , 0x0 , 0 , 0 , 0 , 0};
PCM chn_2_m8 = {(_Mono | _PCM8Bit) , 2 , 127 , 0 , 0x0 , 0 , 0 , 0 , 0};
PCM chn_3_m8 = {(_Mono | _PCM8Bit) , 3 , 127 , 0 , 0x0 , 0 , 0 , 0 , 0};
#include <sddrvs.dat>

	//--------------------------------------------------------------------------
	/// Initialization of Audio SubSystem
	//--------------------------------------------------------------------------
void sndInit()
{
	char sound_map[] = {0xff , 0xff};
	slInitSound(sddrvstsk , sizeof(sddrvstsk) , (Uint8 *)sound_map , sizeof(sound_map));
};

	//--------------------------------------------------------------------------
	/// play a specific sound
	///	@param, index of PCM sound
	//--------------------------------------------------------------------------
	
void snd_play(Uint32 index)
{
    //slPrintHex(slPCMStat(&snd_sfx[index].type),slLocate(20,20));
   // if(slPCMStat(&snd_sfx[index].type)!=true) {
        slPCMOn(&snd_sfx[index].type, (char *)snd_sfx[index].p_Sound,snd_sfx[index].size);
   // }
    
}
	//--------------------------------------------------------------------------
	/// stop a specific sound
	///	@param, index of PCM sound
	//--------------------------------------------------------------------------
void snd_stop(Uint32 index)
{
//This stops the sound
// returns:
// TRUE on success
// FALSE command buffer full
    slPCMOff(&snd_sfx[index].type);
}
	//--------------------------------------------------------------------------
	/// Load all PCM sounds in workRam
	//--------------------------------------------------------------------------
void snd_loadSound_PCM()
{
    Uint8 *adr = (Uint8 *)0x200000;
    snd_sfx[SFX_CHECKPOINT].p_Sound = adr;
    
    Sint32 load = GFS_Load(GFS_NameToId("SFX.BIN"), 0, (Uint32 *)snd_sfx[SFX_CHECKPOINT].p_Sound , SFX_SIZE);
	   if(load <= 0)
    	   	slPrint("ERROR loading file SFX.BIN!", slLocate(2, 11));
    
    snd_sfx[SFX_CHECKPOINT].size = SFX_CHECKPOINT_SIZE; 
    snd_sfx[SFX_CHECKPOINT].type = chn_0_m8;
    
    snd_sfx[SFX_EXPLODE].p_Sound = (char *) snd_sfx[SFX_EXPLODE-1].p_Sound + snd_sfx[SFX_EXPLODE-1].size ;
    snd_sfx[SFX_EXPLODE].p_Sound++;
    
    snd_sfx[SFX_EXPLODE].size= SFX_EXPLODE_SIZE;
    snd_sfx[SFX_EXPLODE].type = chn_0_m8;
    
    snd_sfx[SFX_FINALCHECK].p_Sound = (char *) snd_sfx[SFX_FINALCHECK-1].p_Sound + snd_sfx[SFX_FINALCHECK-1].size ;
    snd_sfx[SFX_FINALCHECK].p_Sound++;
    
    snd_sfx[SFX_FINALCHECK].size= SFX_FINALCHECK_SIZE;
    snd_sfx[SFX_FINALCHECK].type = chn_1_m8;
	
	snd_sfx[SFX_JUMP].p_Sound = (char *) snd_sfx[SFX_JUMP-1].p_Sound + snd_sfx[SFX_JUMP-1].size ;
    snd_sfx[SFX_JUMP].p_Sound++;
    
    snd_sfx[SFX_JUMP].size= SFX_JUMP_SIZE;
    snd_sfx[SFX_JUMP].type = chn_1_m8;
	
	snd_sfx[SFX_JUMPER].p_Sound = (char *) snd_sfx[SFX_JUMPER-1].p_Sound + snd_sfx[SFX_JUMPER-1].size ;
    snd_sfx[SFX_JUMPER].p_Sound++;
    
    snd_sfx[SFX_JUMPER].size= SFX_JUMPER_SIZE;
    snd_sfx[SFX_JUMPER].type = chn_2_m8;
	
	snd_sfx[SFX_LOSE_RINGS].p_Sound = (char *) snd_sfx[SFX_LOSE_RINGS-1].p_Sound + snd_sfx[SFX_LOSE_RINGS-1].size ;
    snd_sfx[SFX_LOSE_RINGS].p_Sound++;
    
    snd_sfx[SFX_LOSE_RINGS].size= SFX_LOSE_RINGS_SIZE;
    snd_sfx[SFX_LOSE_RINGS].type = chn_2_m8;
	
	snd_sfx[SFX_RING].p_Sound = (char *) snd_sfx[SFX_RING-1].p_Sound + snd_sfx[SFX_RING-1].size ;
    snd_sfx[SFX_RING].p_Sound++;
    
    snd_sfx[SFX_RING].size= SFX_RING_SIZE;
    snd_sfx[SFX_RING].type = chn_3_m8;
	
	snd_sfx[SFX_TELETRANSPORT].p_Sound = (char *) snd_sfx[SFX_TELETRANSPORT-1].p_Sound + snd_sfx[SFX_TELETRANSPORT-1].size ;
    snd_sfx[SFX_TELETRANSPORT].p_Sound++;
    
    snd_sfx[SFX_TELETRANSPORT].size= SFX_TELETRANSPORT_SIZE;
    snd_sfx[SFX_TELETRANSPORT].type = chn_3_m8;
	
    
   
    
};

// taken form Rockin'-B's Saturn SoundPlayer
// look there for advanced PCM playing (compressed, from CD)
static CdcPly plywk;
static CdcPos poswk;
static CdcStat stat;
static Uint32 toc[102];
Uint8 cdtrack;

char *CD_status[] = {
    "BUSY",
    "PAUSE",
    "STANDBY",
    "PLAY",
    "SEEK",
    "SCAN",
    "OPEN",
    "NODISC",
    "RETRY",
    "ERROR",
    "FATAL",
    "UNKNOWN"
};

int CDDA_checkContinue()
{
    if(((CDC_STAT_STATUS(&stat) & 0xF) == CDC_ST_PAUSE) || ((CDC_STAT_STATUS(&stat) & 0xF) == CDC_ST_SCAN)) {
        // restart from current position
         /* set data */
         CDC_PLY_STYPE(&plywk) = CDC_PTYPE_NOCHG;
         CDC_PLY_ETYPE(&plywk) = CDC_PTYPE_NOCHG;
        // this needs to be investigated:
         CDC_PLY_PMODE(&plywk) = CDC_PM_NOCHG;
         /* start playing */
         CDC_CdPlay(&plywk);
         return 1;
    }
    return 0;
}

// Pause CD Play (No changed selection: seek current position) ......Pause               
void CDDA_pause()
{
    CDC_GetCurStat(&stat);
    if(((CDC_STAT_STATUS(&stat) & 0xF) == CDC_ST_PLAY) || ((CDC_STAT_STATUS(&stat) & 0xF) == CDC_ST_SCAN)) {
        CDC_POS_PTYPE(&poswk) = CDC_PTYPE_NOCHG;
        CDC_CdSeek(&poswk);
    } else CDDA_checkContinue();
}

void CDDA_play(Uint8 track)
{
    CDC_GetCurStat(&stat);
    if(((CDC_STAT_STATUS(&stat) & 0xF) == CDC_ST_PLAY) || ((CDC_STAT_STATUS(&stat) & 0xF) == CDC_ST_STANDBY) || ((CDC_STAT_STATUS(&stat) & 0xF) == CDC_ST_SEEK)) {
        // start playing track
         /* set data */
         CDC_PLY_STYPE(&plywk) = CDC_PTYPE_TNO;
         CDC_PLY_STNO(&plywk)  = track;
         CDC_PLY_SIDX(&plywk) = 0;
         CDC_PLY_ETYPE(&plywk) = CDC_PTYPE_TNO;
            // this should play all tracks up to the last one
            // if you just want one track, input same track as for CDC_PLY_STNO(&plywk):
         CDC_PLY_ETNO(&plywk)  = track;//(toc[100] & 0x00FF0000) >> 16;
         CDC_PLY_EIDX(&plywk) = 99;
        // this needs to be investigated:
         CDC_PLY_PMODE(&plywk) = CDC_PM_DFL + 10;    // 0 repeats
         /* start playing */
         CDC_CdPlay(&plywk);
    } else CDDA_checkContinue(); 
}

// stop CD, seek home position
void CDDA_stop()
{
    CDC_POS_PTYPE(&poswk) = CDC_PTYPE_DFL;
    CDC_CdSeek(&poswk);
    // this is not neccessary
    //slCDDAOff();
}

// start CD scan / fast forward
// or continue playing
void CDDA_fwd()
{
    CDC_GetCurStat(&stat);
    if((CDC_STAT_STATUS(&stat) & 0xF) == CDC_ST_PLAY) {
        CDC_CdScan(CDC_SCAN_FWD);
    } else CDDA_checkContinue(); 
}

// start CD scan / fast rewind/reverse
// or continue playing
void CDDA_rvs()
{
    CDC_GetCurStat(&stat);
    if((CDC_STAT_STATUS(&stat) & 0xF) == CDC_ST_PLAY) {
        CDC_CdScan(CDC_SCAN_RVS);
    } else CDDA_checkContinue(); 
}
	//--------------------------------------------------------------------------
	/// inits CDDA
	//--------------------------------------------------------------------------
void CDDA_init()
{
    CDC_TgetToc(toc);
    // set track
    cdtrack = (toc[99] & 0x00FF0000) >> 16;
    // avoid setting the data track,
    // select first audio instead
    if(cdtrack < ((toc[100] & 0x00FF0000) >> 16))
        cdtrack++;
		
	slCDDAOn(127, 127, 0, 0);
}

char *CDDA_getStatusName()
{
    int cdstatus;

    CDC_GetCurStat(&stat);
    cdstatus = CDC_STAT_STATUS(&stat) & 0xF;
    if(!((cdstatus >= 0) && (cdstatus <= CDC_ST_FATAL)))
        cdstatus = CDC_ST_FATAL + 1;
        
    return CD_status[cdstatus];
}

int CDDA_getStatus()
{
    int cdstatus;

    CDC_GetCurStat(&stat);
    cdstatus = CDC_STAT_STATUS(&stat) & 0xF;
    if(!((cdstatus >= 0) && (cdstatus <= CDC_ST_FATAL)))
        cdstatus = CDC_ST_FATAL + 1;
        
    return cdstatus;
}

