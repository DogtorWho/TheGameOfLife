/**
 * @file main.cpp
 * File containing the main function
 */

#include "raylib.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>

#include "Game.hpp"

const int SCREEN_WIDTH = 1200; /**< const integer representing the size of the window screen width in pixels */
const int SCREEN_HEIGHT = 800; /**< const integer representing the size of the window screen height in pixels */

/* TODO :
  - GUI functions only in render
  - add comments inside important functions
*/

int main(void){
  srand(time(NULL));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Game Of Life");
  SetTargetFPS(60);

  Game::getInstance()->init();

  /* game loop */
  while (!WindowShouldClose()){
    Game::getInstance()->update();
    Game::getInstance()->render();
  }

  Game::getInstance()->clean();

  CloseWindow();

  return 0;
}
