#ifndef _GAME_RUNNER_H_
#define _GAME_RUNNER_H_

#include <stdbool.h>
#include <stddef.h>
#include "gamestate.h"

#ifndef GIVE_AS_BINARY
#define GIVE_AS_BINARY 1
#endif

typedef struct _GameRunner{
  GameState gs;
  IF8 winner;
  IF8 player;
} GameRunner;

GameRunner GR_new();
void GR_run(GameRunner *gr, int depth);

bool GR_testEnd(GameRunner *gr);

void GR_printOutcome(GameRunner *gr, UIF8 depth);
void GR_ShowPlayer(const GameRunner *gr);
void GR_showBoard(const GameRunner *gr);
void GR_displayWin(const GameRunner *gr);
IF8 GR_getGive(const GameRunner *gr);
UIF8 GR_getPlace(const GameRunner *gr);
void GR_displayFull(const GameRunner *gr);

int getInput(void *out, size_t buf_sz, char *fmt, char *line);

#endif
