#ifndef _DEFINES_H_
#define _DEFINES_H_

#define NEW_CAMERA

#define false 0
#define true (!false)

#define GAME_STATE_LOGO 		0
#define GAME_STATE_PRESENTATION 1
#define GAME_STATE_MAINMENU 	2
#define GAME_STATE_GAMEPLAY 	3
#define PREPARE_LEVEL 			4
#define SHOW_DIALOG 			5
#define ENTER_LEVEL 			6
#define GAME_STATE_INTRO		7
#define GAME_STATE_FADEOUT		8
#define GAME_STATE_LOGO_RM 		9
#define GAME_STATE_GAMEOVER     10
#define GAME_STATE_ENDING       11

#define DIF_X		6
#define DIF_Y		6

#define CAMERA_OFFSET 86
#define CAMERA_LIMIT_X 319
#define CAMERA_LIMIT_Y 4000
#define CAMERA_LIMIT_Z 150


//Audio Tracks
#define	TRK_SPLASH	2
#define	TRK_DIALOG	3
#define	TRK_GHZ		4
#define	TRK_SKZ		5
#define	TRK_MCZ		6
#define	TRK_MNZ		7
#define	TRK_JGZ		8
#define	TRK_CSZ		9



//Levels
#define	GHZ1	1
#define	GHZ2	2
#define	GHZ3	3
#define	SKZ1	4
#define	SKZ2	5
#define	SKZ3	6
#define	MCZ1	7
#define	MCZ2	8
#define	MCZ3	9
#define	MNZ1	10
#define	MNZ2	11
#define	MNZ3	12
#define	JGZ1	13
#define	JGZ2	14
#define	JGZ3	15
#define	CSZ1	16
#define	CSZ2	17
#define	CSZ3	18

//Game Actor defines
#define GAMEACTOR_STATUS_GO_LEFT	1
#define GAMEACTOR_STATUS_GO_RIGHT   2


#define PLATFORM_TYPE_NORMAL        1
#define PLATFORM_TYPE_DESTRUCTIBLE  2
#define PLATFORM_TYPE_SPIKES        3

#endif
