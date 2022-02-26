#include <stdio.h>
#include <inttypes.h>
#include "gamestate.h"


int main(void) {
  printf("Hello World\n");
  IF8 b[16] = {-1, -1, -1, -1,
  -1, -1, -1, -1,
  -1, -1, -1, -1,
  0, 1, 2, -1};
  GameState gs = GS_new((3<<1)+1, 3, b, 0, 0);
  printf("%i\n", GS_getPieceFromXY(&gs, 3, 2));
  printf("%lu\n", sizeof(GameState));
  return 0;
}