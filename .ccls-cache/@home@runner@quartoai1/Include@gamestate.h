#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include <stdint.h>

typedef struct _GS {
  uint_fast8_t turn;
  int_fast8_t given;
  int_fast8_t board[16];
  uint_fast16_t pieces_left;
  uint_fast16_t places_left;
} GameState;

#endif