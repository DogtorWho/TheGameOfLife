/**
 * @file Game.hpp
 * File containing the Game singleton class
 */

#ifndef _GAME_
#define _GAME_

#include "raylib.h"
#include <iostream>
#include <string>

#include "GUI.hpp"
#include "Generation.hpp"

const int GAME_SCREEN_WIDTH = 900; /**< const int representing the size of the game screen width in pixels */
const int GAME_SCREEN_HEIGHT = 600; /**< const int representing the size of the game screen height in pixels */
const int GAME_SCREEN_OFFSET = 50; /**< const int representing the offset of the game screen in pixels */

/**
 * @brief Game singleton class
 * Represents the game core and screen
 */
class Game {
  private:
    Game(){}

    static Game* instance; /**< static Game* representing the instance of the Game Singleton */

    Generation* _gen; /**< Generation* representing the core of the game */

    bool _ending_screen; /**< bool representing the state of the game, true = the game ended and we wait for a new game */
    bool _run; /**< bool representing the state of the game, true = the game loop continue */
    bool _pause; /**< bool representing the state of the game, true = the game is paused */
    bool _rainbow; /**< bool representing the choice of color for the cells in the game */

    int _speed; /**< int representing the current speed iteration of the loop */
    int _speed_max; /**< int representing the speed of the game */
    bool _infinite_generation; /**< bool representing the choice of infinite generation in the game */
    long _nb_generation;  /**< long representing the current generation number */
    int _nb_generation_max; /**< int* representing the maximum generation number before ending the game */
    int _nb_random; /**< int representing the percentage of random alive cells at the start of the game (0-100) */

    int number_of_rows; /**< int representing the number of rows of cells in the generation array */
    int number_of_cols; /**< int representing the number of columns of cells in the generation array */
    float size_of_cell; /**< float representing the size of each cells (square) */

    RenderTexture2D _game_canvas; /**< RenderTexture2D (raylib) representing the game screen */
    Camera2D* _camera; /**< Camera2D* (raylib) representing the camera */
    Rectangle _game_area; /**< Rectangle (raylib) representing the game area position in the window */

  public:
    inline static Game* getInstance(){
      return instance = (instance != nullptr) ? instance : new Game();
    }

    /* getters and setters */
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
    inline int getNbGenerationMax() const { return _nb_generation_max; }
    inline void setNbGenerationMax(int nb_generation_max) { _nb_generation_max = nb_generation_max; }
    inline int getNbRandom() const { return _nb_random; }
    inline void setNbRandom(int nb_random) { _nb_random = nb_random; }

    void init();
    void init_camera();
    void init_game();
    void clean();

    void update();
    void update_camera();
    void render();
    void render_camera();

    void set_array_size(int array_size_index);
    Color get_random_color();
};

#endif
