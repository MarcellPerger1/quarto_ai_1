#include "base_ai.h"
#include "game_runner.h"
#include "gamestate.h"
#include "minimax_ai.h"
#include <inttypes.h>
#include <stdio.h>

int main(int argc, char **argv) {
  printf("Hello World\n");
  unsigned int depth = 10;
  if (argc > 1) {
    sscanf(argv[1], " %d", &depth);
  }
  GameRunner gr = GR_new();
  GR_run(&gr, depth);
  return 0;
}
