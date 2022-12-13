/**
 * @file GUI.hpp
 * File containing the GUI singleton class
 */

#ifndef _GUI_
#define _GUI_

#include "raylib.h"

/**
 * @brief GUI singleton class
 * Represents the GUI of the game
 */
class GUI {
  private:
    static GUI* instance; /**< static GUI* representing the instance of the GUI Singleton */

    Rectangle _button_start; /**< Rectangle (raylib) representing the body of the start button */
    Rectangle _button_pause; /**< Rectangle (raylib) representing the body of the pause button */
    Rectangle _button_stop; /**< Rectangle (raylib) representing the body of the stop button */
    Vector2 _settings_origin; /**< Vector2 (raylib) representing the origin of the settings */
    Rectangle _spinner_speed; /**< Rectangle (raylib) representing the body of the speed spinner */
    Rectangle _checkbox_inf_gen; /**< Rectangle (raylib) representing the body of the infinite generation check box */
    Rectangle _slider_nb_gen; /**< Rectangle (raylib) representing the body of the number of generation slider */
    Rectangle _slider_nb_random; /**< Rectangle (raylib) representing the body of the percentage of random slider */
    Rectangle _dropdownbox_array_size; /**< Rectangle (raylib) representing the body of the size of the game array dropdown box */

    int _dropdown_index; /**< int representing the index of the dropdown box */
    bool _show_dropdown_items; /**< bool representing the state of the dropdown box items */

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
