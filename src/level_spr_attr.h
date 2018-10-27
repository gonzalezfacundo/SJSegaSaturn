#define TILE_START_INDEX					0

#define	CHECK_SONIC_START_INDEX				41
#define	CHECK_EGMANN_START_INDEX			42
#define	BONUS_BALLS_START_INDEX				43
#define	SUPER_JUMP_RING_START_INDEX		46
#define	RING_START_INDEX					57

#define	CHECK_POINT_BASE_START_INDEX		49
#define	CHECK_POINT_REDBALL_START_INDEX		103
#define	CHECK_POINT_BLUEBALL_START_INDEX	104

#define	HUD_LIVES_START_INDEX				63
#define	HUD_RINGS_START_INDEX				64

SPR_ATTR attr_levelSprites[] = {
	SPR_ATTRIBUTE(0,No_Palet,No_Gouraud,CL32KRGB|SPenb|ECdis,sprNoflip|_ZmLT),
	SPR_ATTRIBUTE(0,No_Palet,No_Gouraud,CL32KRGB|SPenb|ECdis,sprNoflip|_ZmCC),
};	
SPR_ATTR attr_levelSpritesInverted[] = {
	SPR_ATTRIBUTE(0,No_Palet,No_Gouraud,CL32KRGB|SPenb|ECdis,sprHflip|_ZmLT),
	SPR_ATTRIBUTE(0,No_Palet,No_Gouraud,CL32KRGB|SPenb|ECdis,sprHflip|_ZmCC),
};
