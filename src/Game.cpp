#include "Game.hpp"
#include "raymath.h"

/*#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"*/

Game *Game::instance = nullptr;

Generation* _gen;

/** brief init - intialize the Game Singleton and the Generation in it
 * param
 * return void
 */
void Game::init(){
  _ending_screen = false;
  _run = false;
  _pause = false;
  _rainbow = false;

  // game variables
  _speed = 0;
  _speed_max = 1;
  _infinite_generation = true;
  _nb_generation = 0;
  *_nb_generation_max = 100;
  _nb_random = 10;

  number_of_rows = 60;
  number_of_cols = number_of_rows * 1.5; // 900/600=1.5 ratio of the screen
  size_of_cell = 10.f;

  // game screen
  _game_area = {GAME_SCREEN_OFFSET, GAME_SCREEN_OFFSET, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT};
  _game_canvas = LoadRenderTexture(_game_area.width, _game_area.height);

  init_camera();

  //init_GUI();
  GUI::getInstance()->init();
}

/*void Game::init_GUI(){
  _button_start = {_game_area.width/2 + _game_area.x - 150, 675, 300, 100};
  _button_pause = {250, 700, 150, 50};
  _button_stop = {600, 700, 150, 50};

  _settings_origin = {975, 50};
  _dropdownbox_array_size = {_settings_origin.x, _settings_origin.y + 90, 100, 20};
  _checkbox_inf_gen = {_settings_origin.x, _settings_origin.y + 160, 20, 20};
  _spinner_nb_gen = {_settings_origin.x + 40, _settings_origin.y + 190, 80, 20};
  _slider_nb_random = {_settings_origin.x, _settings_origin.y + 260, 150, 20};
  _slider_speed = {_settings_origin.x, _settings_origin.y + 330, 80, 20};
}*/

void Game::init_camera(){
  _camera = { 0 };
  _camera->target.x = _game_area.width/2;
  _camera->target.y = _game_area.height/2;
  _camera->offset = _camera->target;
  _camera->zoom = 1.0f;
}

void Game::init_game(){
  delete _gen;

  Vector2 array_size;
  array_size.x = number_of_rows;
  array_size.y = number_of_cols;

  _gen = new Generation(array_size, size_of_cell, _nb_random);
  _gen->init();

  init_camera();
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
  //update_GUI();
  GUI::getInstance()->update();

  if(_run){
    if(!_pause){

      if(_speed < _speed_max){
        _speed += 1.f;
      }
      else{ // update the game
        _gen->update();

        _nb_generation++;

        if(!_infinite_generation && (_nb_generation >= *_nb_generation_max)){
          _pause = false;
          _run = false;
          _ending_screen = true;
        }

        _speed = 0.f;
      }
    }
  }
}

/*void Game::update_GUI(){
  if(CheckCollisionPointRec(GetMousePosition(), _game_area)){
    // zoom on the map
    float wheel = GetMouseWheelMove();
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

      if(_camera.zoom <= 1.f){ // avoid from zooming out too much
        _camera.zoom = 1.f;
        _camera.target.x = _game_area.width/2;
        _camera.target.y = _game_area.height/2;
        _camera.offset = _camera.target;
      }
    }

    // move the map with the mouse
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && _camera.zoom != 1.f){
      Vector2 delta = GetMouseDelta();
      delta = Vector2Scale(delta, -1.0f/_camera.zoom);

      _camera.target.x += delta.x;
      _camera.target.y -= delta.y;
    }
  }

  if(_run){
    if(IsKeyPressed('P') || GuiButton(_button_pause, "Pause"))
      _pause = !_pause;

    if(GuiButton(_button_stop, "Stop")){
      _pause = false;
      _run = false;
      _ending_screen = true;
    }

    if (IsKeyPressed('R'))
      _rainbow = !_rainbow;
  }
  else{
    if(GuiButton(_button_start, "Start")){
      init_game();
      _ending_screen = false;
      _run = true;
    }
  }
}*/

/** brief render - render the Game Singleton and the Generation in it
 * param
 * return void
 */
void Game::render(){
  if(_run || _ending_screen){
    BeginTextureMode(_game_canvas);
    BeginMode2D(*_camera);

    ClearBackground(GRAY);

    _gen->render();

    EndMode2D();
    EndTextureMode();
  }
  else{
    BeginTextureMode(_game_canvas);
    ClearBackground(GRAY);
    EndTextureMode();
  }

  BeginDrawing();
  ClearBackground(RAYWHITE);

  DrawTexture(_game_canvas.texture, _game_area.x, _game_area.y, RAYWHITE);

  if(_ending_screen){
    DrawText("PRESS [START] TO SIMULATE AGAIN",
              ((_game_area.width - (MeasureText("PRESS [START] TO SIMULATE AGAIN", 40))) / 2) + _game_area.x,
              (_game_area.height / 2) + 30,
              40, GRAY);
  }
  else if(_pause){
    DrawText("SIMULATION PAUSED",
              ((_game_area.width - (MeasureText("SIMULATION PAUSED", 40))) / 2) + _game_area.x,
              (_game_area.height / 2) + 30,
              40, GRAY);
  }

  //render_GUI();
  GUI::getInstance()->render();

  EndDrawing();
}

/*void Game::render_GUI(){
  int border_size = 5;
  DrawRectangleLinesEx((Rectangle){_game_area.x - border_size,
                                    _game_area.y - border_size,
                                    _game_area.width + (border_size * 2),
                                    _game_area.height + (border_size * 2)},
                        border_size, LIGHTGRAY);

  std::string text_nb_generation = "GEN : ";
  text_nb_generation += std::to_string(_nb_generation);
  DrawText(text_nb_generation.c_str(), _game_area.x + 5, _game_area.y - 25, 20, GRAY);

  if(_run){
    GuiButton(_button_pause, "Pause");
    GuiButton(_button_stop, "Stop");
  }
  else{
    GuiButton(_button_start, "Start");
  }

  DrawText("Settings", _settings_origin.x, _settings_origin.y, 40, GRAY);

  if(_run)
    GuiDisable();

  DrawLine(_settings_origin.x, _settings_origin.y + 50, _settings_origin.x + MeasureText("Settings", 40), _settings_origin.y + 50, GRAY);

  DrawText("Map Size", _settings_origin.x, _settings_origin.y + 60, 25, GRAY);
  int v1 = 0;
  GuiDropdownBox(_dropdownbox_array_size, "60x90", &v1, false);

  DrawText("Randomness", _settings_origin.x, _settings_origin.y + 230, 25, GRAY);
  _nb_random = GuiSlider(_slider_nb_random, "", std::to_string(_nb_random).c_str(), (float)_nb_random, 0.f, 100.f);

  DrawText("Generations", _settings_origin.x, _settings_origin.y + 130, 25, GRAY);
  _infinite_generation = GuiCheckBox(_checkbox_inf_gen, "Infinite", _infinite_generation);
  if(_infinite_generation)
    GuiDisable();
  GuiSpinner(_spinner_nb_gen, "Number", &_nb_generation_max, 1, 500, false);

  GuiEnable();

  DrawText("Speed", _settings_origin.x, _settings_origin.y + 300, 25, GRAY);
  int tmp_speed;
  switch (_speed_max){
    case 8 : tmp_speed = 1; break;
    case 4 : tmp_speed = 2; break;
    case 2 : tmp_speed = 3; break;
    case 1 : tmp_speed = 4; break;
    default : tmp_speed = 4;
  }
  tmp_speed = GuiSlider(_slider_speed, "", std::to_string(tmp_speed).c_str(), (float)tmp_speed, 1.f, 4.f);
  switch (tmp_speed){
    case 1 : _speed_max = 8; break;
    case 2 : _speed_max = 4; break;
    case 3 : _speed_max = 2; break;
    case 4 : _speed_max = 1; break;
    default : _speed_max = 1;
  }
}*/

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
