#ifndef _BASE_AI_H_
#define _BASE_AI_H_

#include "gamestate.h"

IF8 GS_getGiveMoves(const GameState *gs, GameState out_arr[16]);
IF8 GS_getPlaceMoves(const GameState *gs, GameState out_arr[16]);
IF8 GS_getMoves(const GameState *gs, GameState out_arr[16]);

#endif
