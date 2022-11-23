#ifndef _GUI_
#define _GUI_

#include "raylib.h"
#include <iostream>
#include <string>

class GUI {
  private:
    GUI(){}

    static GUI* instance; /**< instance of the Menu Singleton */
    bool _run; /**< boolean representing the state of the menu, true = the menu loop continue */

  public:
    inline static GUI* getInstance(){
      return instance = (instance != nullptr) ? instance : new GUI();
    }

    void init();
    void clean();

    void update();
    void render();
};

#endif
