#define ENEMY_START_INDEX	99

SPR_ATTR attr_Enemy[] = {
	SPR_ATTRIBUTE(ENEMY_START_INDEX,No_Palet,No_Gouraud,CL32KRGB|SPenb|ECdis,sprNoflip|_ZmLT),
	SPR_ATTRIBUTE(ENEMY_START_INDEX,No_Palet,No_Gouraud,CL32KRGB|SPenb|ECdis,sprNoflip|_ZmCC)
};
SPR_ATTR attr_EnemyInverted[] = {
	SPR_ATTRIBUTE(ENEMY_START_INDEX+0,No_Palet,No_Gouraud,CL32KRGB|SPenb|ECdis,sprHflip|_ZmLT),
	SPR_ATTRIBUTE(ENEMY_START_INDEX+0,No_Palet,No_Gouraud,CL32KRGB|SPenb|ECdis,sprNoflip|_ZmCC)
};
