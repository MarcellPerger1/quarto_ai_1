#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "base_ai.h"
#include "gamestate.h"
#include "minimax_ai.h"
#include "utils.h"

// MMAB_ = Minimax alpha-beta bruning
IF8 MMAB_getValue_debug(GameState *gs, UIF8 depth, IF8 alpha, IF8 beta,
                        bool is_max, int indent) {
  char inds[indent + 1];
  memset(inds, ' ', indent);
  inds[indent] = '\0';
  char inds2[indent + 2 + 1];
  memset(inds2, ' ', indent + 2);
  inds2[indent + 2] = '\0';
  printf("%scall MMAB_getValue(gs, %3i, %3i, %3i, %s)\n", inds, (int)depth,
         (int)alpha, (int)beta, is_max ? "true" : "false");
  if (GS_isWon(gs)) {
    printf("return %3i [win]\n", is_max ? 1 : -1);
    return is_max ? 1 : -1;
  }
  if (!depth || GS_IsFull(gs)) {
    if (!depth) {
      printf("%sreturn %3i [max-depth]\n", inds2, 0);
    } else {
      printf("%sreturn %3i [draw]\n", inds2, 0);
    }
    return 0;
  }
  UIF8 is_place = GS_TurnType(gs);
  // players don't swap after `place`
  bool next_is_max = is_place ? is_max : !is_max;
  IF8 value = is_max ? -1 : 1; // important to iniitalise here as used in min
  GameState children[16];
  IF8 nChildren = GS_getMoves(gs, children);
  assert(nChildren);
  if (is_max) {
    for (IF8 i = 0; i < nChildren; ++i) {
      IF8 val = MMAB_getValue_debug(&children[i], depth - 1, alpha, beta,
                                    next_is_max, indent + 2);
      value = MAX_UNSAFE(value, val);
      alpha = MAX_UNSAFE(alpha, value);
      printf("%supdate-vals %3i, a=%3i, b=%3i, val=%3i\n", inds2, value, alpha,
             beta, val);
      if (value >= 1) {
        printf("%sreturn %3i [at-max]\n", inds2, value);
        return value;
      }
      if (value >= beta) {
        printf("%sreturn %3i [beta-cut]\n", inds2, value);
        return value; // beta cutoff
      }
    }
  } else {
    for (IF8 i = 0; i < nChildren; ++i) {
      IF8 val = MMAB_getValue_debug(&children[i], depth - 1, alpha, beta,
                                    next_is_max, indent + 2);
      value = MIN_UNSAFE(value, val);
      beta = MIN_UNSAFE(beta, value);
      printf("%supdate-vals %3i, a=%3i, b=%3i, val=%3i\n", inds2, value, alpha,
             beta, val);
      if (value <= -1) {
        printf("%sreturn %3i [at-min]\n", inds2, value);
        return value;
      }
      if (value <= alpha) {
        printf("%sreturn %3i [alpha-cut]\n", inds2, value);
        return value; // beta cutoff
      }
    }
  }
  printf("%sreturn %3i [full]\n", inds2, value);
  return value;
}

IF8 MMAB_getValue(GameState *gs, UIF8 depth, IF8 alpha, IF8 beta, bool is_max) {
  if (GS_isWon(gs)) {
    return is_max ? 1 : -1;
  }
  if (!depth || GS_IsFull(gs)) {
    return 0;
  }
  UIF8 is_place = GS_TurnType(gs);
  // players don't swap after `place`
  bool next_is_max = is_place ? is_max : !is_max;
  // important to iniitalise here as used in min/max in loop unconditionally
  IF8 value = is_max ? -1 : 1; 
  GameState children[16];
  IF8 nChildren = GS_getMoves(gs, children);
  assert(nChildren);
  if (is_max) {
    for (IF8 i = 0; i < nChildren; ++i) {
      IF8 val =
          MMAB_getValue(&children[i], depth - 1, alpha, beta, next_is_max);
      value = MAX_UNSAFE(value, val);
      alpha = MAX_UNSAFE(alpha, value);
      if (value >= 1) {
        return value;
      }
      if (value >= beta) {
        return value; // beta cutoff
      }
    }
  } else {
    for (IF8 i = 0; i < nChildren; ++i) {
      IF8 val =
          MMAB_getValue(&children[i], depth - 1, alpha, beta, next_is_max);
      value = MIN_UNSAFE(value, val);
      beta = MIN_UNSAFE(beta, value);
      if (value <= -1) {
        return value;
      }
      if (value <= alpha) {
        return value; // beta cutoff
      }
    }
  }
  return value;
}

IF8 MMAB_getValueTop(GameState *gs, UIF8 depth){
  return MMAB_getValue(gs, depth, -1, 1, true);
}
