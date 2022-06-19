#ifndef _MINIMAX_AI_
#define _MINIMAX_AI_

#include "types.h"
#include "gamestate.h"


IF8 MMAB_getValue_debug(GameState *gs, UIF8 depth, IF8 alpha, IF8 beta, bool is_max, int indent);

IF8 MMAB_getValue(GameState *gs, UIF8 depth, IF8 alpha, IF8 beta, bool is_max);

IF8 MMAB_getValueTop(GameState *gs, UIF8 depth);

#endif
