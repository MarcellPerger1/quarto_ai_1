#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "gamestate.h"

// NOTE: copies data from `board` arg
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
  assert(GS_TurnType(gs) == 0);
  UIF16 pieces_left = gs->pieces_left & ~(1<<piece);
  GameState new = GS_new(gs->turn + 1, piece,
    gs->board,pieces_left, gs->places_left);
  return new;
}
