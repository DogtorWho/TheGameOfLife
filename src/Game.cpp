#include "Game.hpp"
#include "raymath.h"

#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"

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

  _game_canvas = LoadRenderTexture(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);

  _camera = { 0 };
  _camera.zoom = 1.0f;

  _game_area = {GAME_SCREEN_OFFSET, GAME_SCREEN_OFFSET, 900, 650};
  _game_screen_source = {0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT};
  _game_screen_dest = {50, 50, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT};

  _area_hitbox = _game_area;

  //GUI
  _button_pause = {250, 725, 150, 50};
  _button_stop = {600, 725, 150, 50};

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
  update_GUI();

  if(_run){
    if(!_pause){
      _gen->update();

      // if all the cells are dead we stop the simulation
      _run = !(_gen->areCellsDead());
    }
  }
}

void Game::update_GUI(){
  if(IsKeyPressed('P') || GuiButton(_button_pause, "Pause"))
    _pause = !_pause;

  if(GuiButton(_button_stop, "Stop"))
    _run = !_run;

  if (IsKeyPressed('R'))
    _rainbow = !_rainbow;

  if(CheckCollisionPointRec(GetMousePosition(), _game_area)){
    // move the map with the mouse
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
      Vector2 old_target = _camera.target;
      Rectangle old_hitbox = _area_hitbox;

      Vector2 delta = GetMouseDelta();
      delta = Vector2Scale(delta, -1.0f/_camera.zoom);

      //_camera.target = Vector2Add(_camera.target, delta);
      _camera.target.x += delta.x;
      _camera.target.y -= delta.y;

      _area_hitbox.x -= delta.x;
      _area_hitbox.y -= delta.y;

      Vector2 up_left_corner = (Vector2) {_area_hitbox.x, _area_hitbox.y};
      Vector2 up_right_corner = (Vector2) {_area_hitbox.x + _area_hitbox.width, _area_hitbox.y};
      Vector2 down_left_corner = (Vector2) {_area_hitbox.x, _area_hitbox.y + _area_hitbox.height};
      Vector2 down_right_corner = (Vector2) {_area_hitbox.x + _area_hitbox.width, _area_hitbox.y + _area_hitbox.height};

      std::cout << up_left_corner.x << ":" << up_left_corner.y << " " << up_right_corner.x << ":" << up_right_corner.y << " " << down_left_corner.x << ":" << down_left_corner.y << " " << down_right_corner.x << ":" << down_right_corner.y << " " << std::endl;
      std::cout << (_game_area.x + _game_area.width) << ":" << (_game_area.y + _game_area.height) << std::endl;

      bool keep_changes = true;
      if(_camera.zoom = 1.f){
        if(CheckCollisionPointRec(up_left_corner, _game_area)){
          std::cout << "up_left touch" << std::endl;
          keep_changes = false;
        }
        if(CheckCollisionPointRec(up_right_corner, _game_area)){
          std::cout << "up_right touch" << std::endl;
          keep_changes = false;
        }
        if(CheckCollisionPointRec(down_left_corner, _game_area)){
          std::cout << "down_left touch" << std::endl;
          keep_changes = false;
        }
        if(CheckCollisionPointRec(down_right_corner, _game_area)){
          std::cout << "down_right touch" << std::endl;
          keep_changes = false;
        }
      }

      if(!keep_changes){
        _camera.target = old_target;
        _area_hitbox = old_hitbox;
      }
    }

    // zoom on the map
    /*float wheel = GetMouseWheelMove();
    if(wheel != 0){
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
      if(_camera.zoom < 1.f) // avoid from zooming out too much
        _camera.zoom = 1.f;

      if(_camera.zoom < zoomIncrement)
        _camera.zoom = zoomIncrement;
    }*/
  }
}

/** brief render - render the Game Singleton and the Generation in it
 * param
 * return void
 */
void Game::render(){
  BeginTextureMode(_game_canvas);

  BeginMode2D(_camera);

  ClearBackground(RAYWHITE);
  _gen->render();

  EndMode2D();

  EndTextureMode();

  BeginDrawing();

  ClearBackground(RAYWHITE);

  //BeginMode2D(_camera);

  DrawTexture(_game_canvas.texture, _game_area.x, _game_area.y, RAYWHITE);

  //EndMode2D();

  //tmp
  DrawRectangleLinesEx((Rectangle){_game_area.x-5, _game_area.y-5, _game_area.width+10, _game_area.height+10}, 5, LIGHTGRAY);

  DrawRectangleLinesEx((Rectangle){_area_hitbox.x, _area_hitbox.y, _area_hitbox.width, _area_hitbox.height}, 5, RED);

  EndDrawing();

  /*BeginDrawing();

  if(_run){
    ClearBackground(RAYWHITE);

    BeginMode2D(_camera);

    _gen->render();

    EndMode2D();

    if(_pause)
      DrawText("SIMULATION PAUSED", (GAME_SCREEN_WIDTH/2 - MeasureText("SIMULATION PAUSED", 40)/2) + GAME_SCREEN_OFFSET, GAME_SCREEN_HEIGHT/2 - 40, 40, GRAY);
  }
  else
    DrawText("PRESS [ENTER] TO SIMULATE AGAIN", GAME_SCREEN_WIDTH/2 - MeasureText("PRESS [ENTER] TO SIMULATE AGAIN", 20)/2, GAME_SCREEN_HEIGHT/2 - 50, 20, GRAY);

  render_GUI();

  EndDrawing();*/
}

void Game::render_GUI(){
  //DrawRectangleLinesEx((Rectangle){_game_area.x-500, _game_area.y-500, _game_area.width+1000, _game_area.height+1000}, 500, WHITE);
  DrawRectangleLinesEx((Rectangle){_game_area.x-5, _game_area.y-5, _game_area.width+10, _game_area.height+10}, 5, LIGHTGRAY);

  GuiButton(_button_pause, "Pause");
  GuiButton(_button_stop, "Stop");
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
