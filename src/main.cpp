#include "raylib.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>

#include "Game.hpp"

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

/* TODO :
  - comment all functions (doxygen)
  - start with the choice menu and switch to the simulation
  - choose the initial alive cells instead of random (but still an option for random and the percentage)
  - choose the number of turns
  - choose the size of the map
  - can click on map and zoom / move in it with mouse
  - button to stop the simulation
  - choose alive cell color (even skin later)
  - refactoring : add GUI singleton to contain all the variables and renders
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

  CloseWindow(); // Close window and OpenGL context

  return 0;
}
