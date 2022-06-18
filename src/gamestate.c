#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "gamestate.h"

// NOTE: copies data from `board` arg
GameState GS_new(UIF8 turn, IF8 given, const IF8 board[16], UIF16 pieces_left,
                 UIF16 places_left) {
  GameState gs = {.turn = turn,
                  .given = given,
                  .pieces_left = pieces_left,
                  .places_left = places_left};
  memcpy(&gs.board, board, 16);
  return gs;
}

GameState GS_empty() {
  GameState gs = {
      .turn = 0,
      .given = P_EMPTY,
      .pieces_left = ~0,
      .places_left = ~0,
  };
  memset(gs.board, P_EMPTY, 16*sizeof(IF8));
  return gs;
  // return GS_new(0, );
}

IF8 GS_getPieceFromXY(const GameState *gs, IF8 x, IF16 y) {
  return gs->board[GS_IndexOf(x, y)];
}

IF8 GS_getPiece(const GameState *gs, UIF8 pos){
  return gs->board[pos];
}

GameState GS_givePiece(const GameState *gs, IF8 piece) {
  assert(gs->given == P_EMPTY);
  assert(GS_TurnType(gs) == 0);
  const UIF16 pieces_left = gs->pieces_left & ~(1 << piece);
  GameState new =
      GS_new(gs->turn + 1, piece, gs->board, pieces_left, gs->places_left);
  return new;
}

GameState GS_placePiece(const GameState *gs, UIF8 place) {
  assert(gs->given != P_EMPTY);
  assert(GS_TurnType(gs) == 1);
  assert(gs->board[place] == P_EMPTY);
  const UIF16 places_left = gs->places_left & ~(1 << place);
  GameState new =
      GS_new(gs->turn + 1, P_EMPTY, gs->board, gs->pieces_left, places_left);
  new.board[place] = gs->given;
  return new;
}

IF8 GS_isFull(const GameState *gs){
  return !gs->places_left;
}

IF8 GS_isWon(const GameState *gs) {
  const IF8 *board = gs->board;
  for (int i = 0; i < 16; i+=4) {
    // todo i'd be tempted to write this in assembly
    IF8 row[4] = {board[i], board[i + 1], board[i + 2], board[i + 3]};
    if (GS_isRowWon_Arr(row)) {
      return 1;
    }
  }
  for(int i = 0; i < 4; ++i) {
    IF8 row[4] = {board[i], board[i + 4], board[i + 8], board[i + 12]};
    if (GS_isRowWon_Arr(row)) {
      return 1;
    }
  }
  // diagonals
  {
    IF8 row[4] = {board[0], board[5], board[10], board[15]};
    if (GS_isRowWon_Arr(row)) {
      return 1;
    }
  }
  {
    IF8 row[4] = {board[3], board[6], board[9], board[12]};
    if (GS_isRowWon_Arr(row)) {
      return 1;
    }
  }
  return 0;
}


/*
#define _GS_isRowWon_LOOP_START(bi) \
if (board[bi] == P_EMPTY) { return 0; } \
value = board[bi];

#define _GS_isRowWon_LOOP_MAIN(bi) \
if (board[bi] == P_EMPTY) { return 0; } \
same_bits &= ~(value ^ board[bi]); \
if (!same_bits) { \
  return 0; \
}

#define _GS_isRowWon_LOOP(i1, i2, i3, i4) \
_GS_isRowWon_LOOP_START(i1) \
_GS_isRowWon_LOOP_MAIN(i2) \
_GS_isRowWon_LOOP_MAIN(i3) \
_GS_isRowWon_LOOP_MAIN(i4) \

#define _GS_isRowWon_INLINE(i1, i2, i3, i4) \
{ \
  UIF8 same_bits = 0b1111; \
  IF8 value = -1; \
  _GS_isRowWon_LOOP(i1, i2, i3, i4) \
}

#define _GS_isRowWon_INCREMENT(start, inc) \
{ \
  UIF8 same_bits = 0b1111; \
  IF8 value = -1; \
  UIF8 i = start;\
  _GS_isRowWon_LOOP_START(i) \
  i += inc;\
  _GS_isRowWon_LOOP_MAIN(i) \
  i += inc;\
  _GS_isRowWon_LOOP_MAIN(i) \
  i += inc;\
  _GS_isRowWon_LOOP_MAIN(i) \
}

IF8 GS_isWon2(const GameState *gs) {
  const IF8 *board = gs->board;
  UIF8 row_start = 0;
  assert(0);
  return 0;
}
*/

IF8 GS_isRowWon_Idx(const IF8* board, const UIF8 idx[4]){
  UIF8 same_bits = 15;
  IF8 value = -1;
  for (int i = 0; i < 4; ++i) {
    if (board[idx[i]] == P_EMPTY) {
      return 0;
    }
    if (value == -1) {
      value = board[idx[i]];
      continue;
    }
    same_bits &= ~(value ^ board[idx[i]]);
    if (same_bits == 0) {
      return 0;
    }
  }
  return 1;
}

IF8 GS_isRowWon_Arr(const IF8 row[4]) {
  UIF8 same_bits = 15;  // 0b1111
  IF8 value = -1;
  for (int i = 0; i < 4; ++i) {
    if (row[i] == P_EMPTY) {
      return 0;
    }
    if (value == -1) {
      value = row[i];
      continue;
    }
    same_bits &= ~(value ^ row[i]);
    if (same_bits == 0) {
      return 0;
    }
  }
  return 1;
}
