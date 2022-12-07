#ifndef _GAME_
#define _GAME_

#include "raylib.h"
#include <iostream>
#include <string>

#include "GUI.hpp"
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

    int _speed;
    int _speed_max;
    bool _infinite_generation;
    long _nb_generation;
    int* _nb_generation_max;
    int _nb_random;

    int number_of_rows;
    int number_of_cols;
    float size_of_cell;

    RenderTexture2D _game_canvas;
    Camera2D* _camera;
    Rectangle _game_area;

    //GUI
    /*Rectangle _button_start;
    Rectangle _button_pause;
    Rectangle _button_stop;
    Vector2 _settings_origin;
    Rectangle _dropdownbox_array_size;
    Rectangle _checkbox_inf_gen;
    Rectangle _spinner_nb_gen;
    Rectangle _slider_nb_random;
    Rectangle _slider_speed;*/

  public:
    inline static Game* getInstance(){
      return instance = (instance != nullptr) ? instance : new Game();
    }

    inline bool getEndingScreen() const { return _ending_screen; }
    inline void setEndingScreen(bool ending_screen) { _ending_screen = ending_screen; }
    inline bool getRun() const { return _run; }
    inline void setRun(bool run) { _run = run; }
    inline bool getPause() const { return _pause; }
    inline void setPause(bool pause) { _pause = pause; }
    inline bool getRainbow() const { return _rainbow; }
    inline void setRainbow(bool rainbow) { _rainbow = rainbow; }
    inline Rectangle getGameArea() const { return _game_area; }
    inline Camera2D* getCamera() { return _camera; }

    inline int getSpeedMax() const { return _speed_max; }
    inline void setSpeedMax(int speed_max) { _speed_max = speed_max; }
    inline bool getInfiniteGeneration() const { return _infinite_generation; }
    inline void setInfiniteGeneration(bool infinite_generation) { _infinite_generation = infinite_generation; }
    inline long getNbGeneration() const { return _nb_generation; }
    inline void setNbGeneration(long nb_generation) { _nb_generation = nb_generation; }
    inline int* getNbGenerationMax() const { return _nb_generation_max; }
    inline void setNbGenerationMax(int nb_generation_max) { *_nb_generation_max = nb_generation_max; }
    inline int getNbRandom() const { return _nb_random; }
    inline void setNbRandom(int nb_random) { _nb_random = nb_random; }

    void init();
    //void init_GUI();
    void init_camera();
    void init_game();
    void clean();

    void update();
    //void update_GUI();
    void render();
    //void render_GUI();

    Color getRandomColor();
};

#endif
