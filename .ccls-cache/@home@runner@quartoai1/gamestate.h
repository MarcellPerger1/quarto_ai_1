#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <stdint.h>

#define IF8 int_fast8_t
#define UIF8 uint_fast8_t
#define IF16 int_fast16_t
#define UIF16 uint_fast16_t

#define GS_IndexOf(x, y) ((y) * 4 + (x))
#define GS_TurnType(gsp) ((gsp)->turn & 1)
#define GS_Player(gsp) ((gsp)->turn & 2)
#define P_EMPTY ((IF8)(-1))


typedef struct {
  UIF8 turn;
  IF8 given;
  IF8 board[16];
  UIF16 pieces_left;
  UIF16 places_left;
} GameState;

GameState GS_new(uint_fast8_t turn, int_fast8_t given, int_fast8_t board[16],
                 uint_fast16_t pieces_left, uint_fast16_t places_left);

IF8 GS_getPieceFromXY(const GameState *gs, IF8 x, IF16 y);

#endif