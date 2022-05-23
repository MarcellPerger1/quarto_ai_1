#include <stdio.h>
#include "gamestate.h"
#include "base_ai.h"
#include "game_runner.h"

int main(void) {
  printf("Hello World\n");
  GameRunner gr = GR_new();
  GR_run(&gr);
  return 0;
}
