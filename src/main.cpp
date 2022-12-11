#include "raylib.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>

#include "Game.hpp"

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

/* TODO :
  - comment all functions (doxygen)
  - choose the initial alive cells instead of random (but still an option for random and the percentage)
  - choose the size of the map
  - choose alive cell color (even skin later)
  - replace GuiSpinner for nb_generation with something else
  - Gui functions only in render
*/

int main(void){
  srand(time(NULL));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Game Of Life");
  SetTargetFPS(60);

  Game::getInstance()->init();

  while (!WindowShouldClose()){
    Game::getInstance()->update();
    Game::getInstance()->render();
  }

  Game::getInstance()->clean();

  CloseWindow();

  return 0;
}
