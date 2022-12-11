#include "Game.hpp"
#include "raymath.h"

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

  GUI::getInstance()->init();
}

void Game::init_camera(){
  _camera = new Camera2D();
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

  GUI::getInstance()->render();

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
