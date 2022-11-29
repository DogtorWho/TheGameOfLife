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

  number_of_rows = 64;
  number_of_cols = 96;
  size_of_cell = 10.f;

  _game_area = {GAME_SCREEN_OFFSET, GAME_SCREEN_OFFSET, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT};

  _game_canvas = LoadRenderTexture(_game_area.width, _game_area.height);

  _camera = { 0 };
  _camera.target.x = _game_area.width/2;
  _camera.target.y = _game_area.height/2;
  _camera.offset = _camera.target;
  _camera.zoom = 1.0f;

  _area_hitbox = _game_area;
  z_key = false;

  //GUI
  _button_pause = {250, 725, 150, 50};
  _button_stop = {600, 725, 150, 50};

  Vector2 array_size;
  array_size.x = number_of_rows;
  array_size.y = number_of_cols;

  _gen = new Generation(array_size, size_of_cell);
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


  /*if(CheckCollisionPointRec(GetMousePosition(), _game_area)){
    // zoom on the map
    float wheel = GetMouseWheelMove();
    if(wheel != 0){
      // Get the world point that is under the mouse
      /*Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), _camera);

      // Set the offset to where the mouse is
      _camera.offset = GetMousePosition();

      // Set the target to match, so that the camera maps the world space point
      // under the cursor to the screen space point under the cursor at any zoom
      _camera.target = mouseWorldPos;*/

      // Zoom increment
      /*const float zoomIncrement = 0.125f;
      _camera.zoom += (wheel*zoomIncrement);

      float old_width = _area_hitbox.width;
      float old_height = _area_hitbox.height;

      _area_hitbox.width = _game_area.width * _camera.zoom;
      _area_hitbox.height = _game_area.height * _camera.zoom;

      if(wheel > 0){
        _area_hitbox.x -= (_area_hitbox.width - old_width) / 2;
        _area_hitbox.y -= (_area_hitbox.height - old_height) / 2;
      }
      else{
        _area_hitbox.x += (old_width - _area_hitbox.width) / 2;
        _area_hitbox.y += (old_height - _area_hitbox.height) / 2;
      }

      if(_camera.zoom <= 1.f){ // avoid from zooming out too much
        _camera.zoom = 1.f;
        _area_hitbox = _game_area;
      }
    }


    // move the map with the mouse
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && _camera.zoom != 1.f){
      Vector2 old_target = _camera.target;
      Rectangle old_hitbox = _area_hitbox;

      Vector2 delta = GetMouseDelta();
      delta = Vector2Scale(delta, -1.0f/_camera.zoom);

      //_camera.target = Vector2Add(_camera.target, delta);
      _camera.target.x += delta.x;
      _camera.target.y -= delta.y;

      _area_hitbox.x -= delta.x;
      _area_hitbox.y -= delta.y;

      bool keep_changes = true;
      Vector2 hitbox_down_right = (Vector2) {_area_hitbox.x + _area_hitbox.width, _area_hitbox.y + _area_hitbox.height};
      Vector2 game_down_right = (Vector2) {_game_area.x + _game_area.width, _game_area.y + _game_area.height};

      if(_area_hitbox.x >= _game_area.x){ //left side collision
        std::cout << "left touch" << std::endl;

        _area_hitbox.x = _game_area.x;

        keep_changes = false;
      }
      if(hitbox_down_right.x <= game_down_right.x){ //right side collision
        std::cout << "right touch" << std::endl;

        _area_hitbox.x += (game_down_right.x - hitbox_down_right.x);

        keep_changes = false;
      }
      if(_area_hitbox.y >= _game_area.y){ //top side collision
        std::cout << "top touch" << std::endl;

        _area_hitbox.y = _game_area.y;

        keep_changes = false;
      }
      if(hitbox_down_right.y <= game_down_right.y){ //bottom side collision
        std::cout << "bottom touch" << std::endl;

        _area_hitbox.y += (game_down_right.y - hitbox_down_right.y);

        keep_changes = false;
      }

      std::cout << _area_hitbox.width << " " << _area_hitbox.height << std::endl;

      /*if(!keep_changes){
        _camera.target = old_target;
        _area_hitbox = old_hitbox;
      }*/
    /*}
  }*/
}

/** brief render - render the Game Singleton and the Generation in it
 * param
 * return void
 */
void Game::render(){
  if(_run){
    BeginTextureMode(_game_canvas);
    BeginMode2D(_camera);
    ClearBackground(RAYWHITE);

    _gen->render();

    EndMode2D();
    EndTextureMode();
  }

  BeginDrawing();
  ClearBackground(RAYWHITE);

  DrawTexture(_game_canvas.texture, _game_area.x, _game_area.y, RAYWHITE);

  if(!_run){
    DrawText("PRESS [ENTER] TO SIMULATE AGAIN",
              ((_game_area.width - (MeasureText("PRESS [ENTER] TO SIMULATE AGAIN", 40))) / 2) + _game_area.x,
              (_game_area.height / 2) + 30,
              40, GRAY);
  }
  else if(_pause){
    DrawText("SIMULATION PAUSED",
              ((_game_area.width - (MeasureText("SIMULATION PAUSED", 40))) / 2) + _game_area.x,
              (_game_area.height / 2) + 30,
              40, GRAY);
  }

  render_GUI();

  EndDrawing();
}

void Game::render_GUI(){
  int border_size = 5;
  DrawRectangleLinesEx((Rectangle){_game_area.x - border_size,
                                    _game_area.y - border_size,
                                    _game_area.width + (border_size * 2),
                                    _game_area.height + (border_size * 2)},
                                    border_size, LIGHTGRAY);

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
