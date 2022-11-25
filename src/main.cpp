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
  - choose the initale alive cells instead of random (but still an option for random and the percentage)
  - choose the number of turns
  - choose the size of the map
  - can click on map and zoom / move in it with mouse
  - button to stop the simulation
  - choose alive cell color (even skin later)
  - change to 60fps always, add a limiter in the render and update function to slow down the simulation
  - remove Menu and GUI classes
*/

int main(void){
  srand(time(NULL));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Game Of Life");
  SetTargetFPS(30);


  Game::getInstance()->init();

  while (!WindowShouldClose()){
    Game::getInstance()->update();
    Game::getInstance()->render();
  }

  Game::getInstance()->clean();

  CloseWindow(); // Close window and OpenGL context

  return 0;
}
