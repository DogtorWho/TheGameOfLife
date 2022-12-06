#ifndef _GAME_
#define _GAME_

#include "raylib.h"
#include <iostream>
#include <string>

#include "Generation.hpp"

/*#define LINES_OF_CELLS 65
#define CELLS_PER_LINE 90
#define SIZE_OF_CELL 10*/

const int GAME_SCREEN_WIDTH = 900;
const int GAME_SCREEN_HEIGHT = 600;
const int GAME_SCREEN_OFFSET = 50;

class Game {
  private:
    Game(){}

    static Game* instance; /**< instance of the Game Singleton */

    bool _ending_screen;
    bool _run; /**< boolean representing the state of the game, true = the game loop continue */
    bool _pause; /**< boolean representing the state of the game, true = the game is paused */
    bool _rainbow; /**< boolean representing the choice of color for the cells in the game */

    double _speed;
    double _speed_max;
    bool _infinite_generation;
    long _nb_generation;
    long _nb_generation_max;
    int _nb_random;

    int number_of_rows;
    int number_of_cols;
    float size_of_cell;

    RenderTexture2D _game_canvas;
    Camera2D _camera;
    Rectangle _game_area;

    Rectangle _area_hitbox;

    //GUI
    Rectangle _button_start;
    Rectangle _button_pause;
    Rectangle _button_stop;
    Vector2 _settings_origin;
    Rectangle _dropdownbox_array_size;
    Rectangle _checkbox_inf_gen;
    Rectangle _valuebox_nb_gen;
    Rectangle _slider_nb_random;
    Rectangle _slider_speed;

  public:
    inline static Game* getInstance(){
      return instance = (instance != nullptr) ? instance : new Game();
    }

    inline bool getPause() const { return _pause; }
    inline bool getRainbow() const { return _rainbow; }

    inline bool running(){ return _run; }
    inline void pause(){ _pause = true; }
    inline void resume(){ _pause = false; }
    inline void quit(){ _run = false; }

    void init();
    void init_GUI();
    void init_camera();
    void init_game();
    void clean();

    void update();
    void update_GUI();
    void render();
    void render_GUI();

    Color getRandomColor();
};

#endif
