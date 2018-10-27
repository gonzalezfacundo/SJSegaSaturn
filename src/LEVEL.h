#ifndef _LEVEL_H_
#define _LEVEL_H_

#define	OBJECT_LVL_RING 				4
#define	OBJECT_LVL_RINGJUMP 			5
#define	OBJECT_LVL_RINGPOINTS			6

 enum objectType{
	OBJECT_PLATFORM_SIMPLE,
	OBJECT_PLATFORM_DESTRUCTIVE,
	OBJECT_PLATFORM_MOVELR,
	OBJECT_PLATFORM_SPIKES
	};

extern void levelDraw();
extern void DrawScene();
#endif
