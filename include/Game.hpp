#ifndef _GAME_
#define _GAME_

#include "raylib.h"
#include <iostream>
#include <string>

#include "Generation.hpp"

#define LINES_OF_CELLS 65
#define CELLS_PER_LINE 90
#define SIZE_OF_CELL 10

const int GAME_SCREEN_WIDTH = CELLS_PER_LINE*SIZE_OF_CELL;
const int GAME_SCREEN_HEIGHT = LINES_OF_CELLS*SIZE_OF_CELL;
const int GAME_SCREEN_OFFSET = 50;

class Game {
  private:
    Game(){}

    static Game* instance; /**< instance of the Game Singleton */
    bool _run; /**< boolean representing the state of the game, true = the game loop continue */
    bool _pause; /**< boolean representing the state of the game, true = the game is paused */
    bool _rainbow; /**< boolean representing the choice of color for the cells in the game */

    RenderTexture2D _game_canvas;
    Camera2D _camera;
    Rectangle _game_area;
    Rectangle _game_screen_source;
    Rectangle _game_screen_dest;

    Rectangle _area_hitbox;
    bool z_key;

    //GUI
    Rectangle _button_pause;
    Rectangle _button_stop;

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
    void clean();

    void update();
    void update_GUI();
    void render();
    void render_GUI();

    Color getRandomColor();
};

#endif
