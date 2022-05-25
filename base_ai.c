#include "gamestate.h"

// returns amount of moves in out (it should be 16+ big)
// actual return value is amount of moves
IF8 GS_getGiveMoves(const GameState *gs, GameState out[16]) {
  UIF16 mask = 1;
  IF8 n = 0;
  for (IF8 i = 0; i < 16; ++i) {
    if (!(gs->pieces_left & mask)) {
      out[n++] = GS_givePiece(gs, i);
    }
    mask <<= 1;
  }
  return n;
}

IF8 GS_getPlaceMoves(const GameState *gs, GameState out[16]) {
  UIF16 mask = 1;
  IF8 n = 0;
  for (IF8 i = 0; i < 16; ++i) {
    if ((gs->places_left & mask) == 0) {
      out[n++] = GS_placePiece(gs, i);
    }
    mask <<= 1;
  }
  return n;
}

IF8 GS_getMoves(const GameState *gs, GameState out[16]) {
  if (GS_TurnType(gs) == 0) {
    return GS_getGiveMoves(gs, out);
  } else {
    return GS_getPlaceMoves(gs, out);
  }
}
