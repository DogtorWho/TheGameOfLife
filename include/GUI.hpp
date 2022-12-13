#ifndef _GUI_
#define _GUI_

#include "raylib.h"

class GUI {
  private:
    static GUI* instance; /**< instance of the GUI Singleton */

    Rectangle _button_start;
    Rectangle _button_pause;
    Rectangle _button_stop;
    Vector2 _settings_origin;
    Rectangle _dropdownbox_array_size;
    Rectangle _checkbox_inf_gen;
    Rectangle _slider_nb_gen;
    Rectangle _slider_nb_random;
    Rectangle _slider_speed;

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
