#include "gamestate.h"

// returns amount of moves in out_arr (it should be 16+ big)
IF8 GS_getGiveMoves(const GameState *gs, GameState out_arr[16]) {
  UIF16 mask = 1;
  IF8 n = 0;
  for (IF8 i = 0; i < 16; ++i) {
    if ((gs->pieces_left & mask) == 0) {
      out_arr[i] = GS_givePiece(gs, n);
      ++n;
    }
    mask <<= 1;
  }
  return n;
}

IF8 GS_getPlaceMoves(const GameState *gs, GameState out_arr[16]) {
  UIF16 mask = 1;
  IF8 n = 0;
  for (IF8 i = 0; i < 16; ++i) {
    if ((gs->places_left & mask) == 0) {
      out_arr[i] = GS_placePiece(gs, n);
      ++n;
    }
    mask <<= 1;
  }
  return n;
}

IF8 GS_getMoves(const GameState *gs, GameState out_arr[16]) {
  if (GS_TurnType(gs) == 0) {
    return GS_getGiveMoves(gs, out_arr);
  } else {
    return GS_getPlaceMoves(gs, out_arr);
  }
}
