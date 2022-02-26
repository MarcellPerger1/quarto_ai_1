#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "gamestate.h"

GameState GS_new(uint_fast8_t turn, int_fast8_t given, int_fast8_t board[16],
                 uint_fast16_t pieces_left, uint_fast16_t places_left) {
  GameState gs = {.turn = turn,
                  .given = given,
                  .pieces_left = pieces_left,
                  .places_left = places_left};
  memcpy(&gs.board, board, 16);
  return gs;
}

IF8 GS_getPieceFromXY(const GameState *gs, IF8 x, IF16 y){
  return gs->board[GS_IndexOf(x, y)];
}

GameState GS_givePiece(GameState* gs, IF8 piece){
  assert(gs->given == -1);
  assert(GS_TurnType(gs))
}
