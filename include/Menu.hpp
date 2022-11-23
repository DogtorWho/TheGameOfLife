#ifndef _MENU_
#define _MENU_

#include "raylib.h"
#include <iostream>
#include <string>

class Menu {
  private:
    Menu(){}

    static Menu* instance; /**< instance of the Menu Singleton */

    bool _button_pause;
    bool _button_stop;

  public:
    inline static Menu* getInstance(){
      return instance = (instance != nullptr) ? instance : new Menu();
    }

    void init();
    void clean();

    void update();
    void render();
};

#endif
