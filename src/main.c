#include <stdio.h>
#include <inttypes.h>
#include "gamestate.h"
#include "base_ai.h"
#include "game_runner.h"
#include "minimax_ai.h"

int main(int argc, char **argv) {
  printf("Hello World\n");
  unsigned int depth = 10;
  if(argc>1){
    sscanf(argv[1], " %d", &depth);
  }
  printf("%d\n", depth);
  GameRunner gr = GR_new();
  GR_run(&gr, depth);
  return 0;
}
