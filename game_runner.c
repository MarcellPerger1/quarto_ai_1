#include <stdio.h>
#include <stdlib.h>

#include "game_runner.h"
#include "gamestate.h"

GameRunner GR_new() {
  GameRunner gr = {GS_empty(), .winner = 0, .player = 0};
  return gr;
}

void GR_run(GameRunner *gr) {
  while (1) {
    GR_ShowPlayer(gr);
    GR_showBoard(gr);
    IF8 given = GR_getGive(gr);
    gr->gs = GS_givePiece(&gr->gs, given);
    UIF8 at = GR_getPlace(gr);
    gr->gs = GS_placePiece(&gr->gs, at);
    if (GR_testEnd(gr)) {
      break;
    }
  }
}

bool GR_testEnd(GameRunner *gr) {
  if (GS_isWon(&gr->gs)) {
    gr->winner = GS_Player(&gr->gs) + 1;
    GR_displayWin(gr);
    return true;
  }
  if (GS_IsFull(&gr->gs)) {
    GR_displayFull(gr);
    return true;
  }
  return false;
}

void GR_ShowPlayer(const GameRunner *gr) {
  printf("Player %i's turn\n", GS_Player(&gr->gs) + 1);
}

#define _TO_BIN4_STR_REV(v)                                                    \
  '0' + (v & 8 ? 1 : 0), '0' + (v & 4 ? 1 : 0), '0' + (v & 2 ? 1 : 0),         \
      '0' + (v & 1 ? 1 : 0)
#define _BIN4_FMT "%c%c%c%c"

void GR_showBoard(const GameRunner *gr) {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      IF8 p = GS_getPieceFromXY(&gr->gs, x, y);
      if (p != P_EMPTY) {
        printf("  "_BIN4_FMT
               "  ",
               _TO_BIN4_STR_REV(p));
      } else {
        printf("  ----  ");
      }
    }
    printf("\n");
  }
}

void GR_displayWin(const GameRunner *gr) {
  GR_showBoard(gr);
  printf("Player %i wins!\n", gr->winner);
}

void GR_displayFull(const GameRunner *gr) {
  GR_showBoard(gr);
  printf("Draw (board full)\n");
}

IF8 GR_getGive(const GameRunner *gr) {
  while (1) {
    int p;
    printf("Enter piece to give: ");
    if (getInput(&p, 10, "%d", NULL)) {
      continue;
    }
    if (!(0 <= p && p < 16)) {
      printf("Out of range\n");
      continue;
    }
    if (!(gr->gs.pieces_left & (1 << p))) {
      printf("Not available\n");
      continue;
    };
    return p;
  }
}

UIF8 GR_getPlace(const GameRunner *gr) {
  while (1) {
    int p;
    printf("Enter where to place piece %i: ", gr->gs.given);
    if (getInput(&p, 10, "%d", NULL)) {
      continue;
    }
    if (!(0 <= p && p < 16)) {
      printf("Out of range\n");
      continue;
    }
    if (!(gr->gs.places_left & (1 << p))) {
      printf("Not available\n");
      continue;
    };
    return p;
  }
}

int getInput(void *out, size_t buf_sz, char *fmt, char *line) {
  if (line == NULL) {
    char ln[buf_sz];
    line = ln;
  }
  if (fgets(line, buf_sz, stdin)) {
    if (sscanf(line, fmt, out) != 1) {
      if (line[0] != '\n') {
        printf("Invalid input\n");
      }
      return 1; // invaild input
    }
  } else {
    printf("\nStream was closed unexpectedly!\n");
    exit(1);  // eg. Ctrl+D just closes stdin!
  }
  return 0; // OK
}
