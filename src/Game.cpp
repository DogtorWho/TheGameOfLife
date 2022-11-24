#include "Game.hpp"
#include "raymath.h"

Game *Game::instance = nullptr;

Generation* _gen;

/** brief init - intialize the Game Singleton and the Generation in it
 * param
 * return void
 */
void Game::init(){
  _run = true;
  _pause = false;
  _rainbow = false;

  _camera = { 0 };
  _camera.zoom = 1.0f;

  _game_area = {GAME_SCREEN_OFFSET - 5, GAME_SCREEN_OFFSET - 5, 900 + 10, 650 + 10};

  Vector2 size;
  size.x = LINES_OF_CELLS;
  size.y = CELLS_PER_LINE;

  _gen = new Generation(size);
  _gen->init();
}

/** brief clean - free the Generation in the Game Singleton
 * param
 * return void
 */
void Game::clean(){
  delete _gen;
}

/** brief update - update the Game Singleton and the Generation in it
 * param
 * return void
 */
void Game::update(){
  if(_run){
    if (IsKeyPressed('P'))
      _pause = !_pause;

    if(!_pause){
      if (IsKeyPressed('R'))
        _rainbow = !_rainbow;

      _gen->update();

      // if all the cells are dead we stop the simulation
      _run = !(_gen->areCellsDead());
    }
  }

  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
    Vector2 delta = GetMouseDelta();
    delta = Vector2Scale(delta, -1.0f/_camera.zoom);

    _camera.target = Vector2Add(_camera.target, delta);
  }

  float wheel = GetMouseWheelMove();
  if (wheel != 0){
    // Get the world point that is under the mouse
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), _camera);

    // Set the offset to where the mouse is
    _camera.offset = GetMousePosition();

    // Set the target to match, so that the camera maps the world space point
    // under the cursor to the screen space point under the cursor at any zoom
    _camera.target = mouseWorldPos;

    // Zoom increment
    const float zoomIncrement = 0.125f;

    _camera.zoom += (wheel*zoomIncrement);

    if (_camera.zoom < zoomIncrement)
      _camera.zoom = zoomIncrement;
  }
}

/** brief render - render the Game Singleton and the Generation in it
 * param
 * return void
 */
void Game::render(){
  BeginDrawing();
  BeginMode2D(_camera);

  if(_run){
    ClearBackground(RAYWHITE);

    _gen->render();

    if(_pause)
      DrawText("SIMULATION PAUSED", GAME_SCREEN_WIDTH/2 - MeasureText("SIMULATION PAUSED", 40)/2, GAME_SCREEN_HEIGHT/2 - 40, 40, GRAY);
  }
  else
    DrawText("PRESS [ENTER] TO SIMULATE AGAIN", GAME_SCREEN_WIDTH/2 - MeasureText("PRESS [ENTER] TO SIMULATE AGAIN", 20)/2, GAME_SCREEN_HEIGHT/2 - 50, 20, GRAY);

  DrawRectangleLinesEx(_game_area, 5, LIGHTGRAY);

  EndMode2D();
  EndDrawing();
}

/** brief getRandomColor - take a random color between 11 choices
 * Possible colors : MAGENTA, YELLOW, ORANGE, PINK, RED, GREEN, LIME,
 *                    VIOLET, SKYBLUE, BLUE, PURPLE
 * param
 * return raylib::Color
 */
Color Game::getRandomColor(){
  int random = rand()%9;
  switch(random){
    case 0: return MAGENTA;
    case 1: return YELLOW;
    case 2: return ORANGE;
    case 3: return PINK;
    case 4: return RED;
    case 5: return GREEN;
    case 6: return LIME;
    case 7: return VIOLET;
    case 8: return SKYBLUE;
    case 9: return BLUE;
    case 10: return PURPLE;
  }
  return WHITE;
}
