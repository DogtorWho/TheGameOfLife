#include "Menu.hpp"

#include "GUI.hpp"
#include "Game.hpp"

#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"

Menu *Menu::instance = nullptr;

void Menu::init(){
  _button_pause = false;
  _button_stop = false;
}

void Menu::clean(){

}

void Menu::update(){
  if(GuiButton((Rectangle){950, 200, 120, 40}, "Pause Sim")){
    Game::getInstance()->pause();
    _button_pause = true;
  }
  else{

  }
    Game::getInstance()->unpause();
}

void Menu::render(){
  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), LIGHTGRAY);
  
  if(_button_pause)
    _button_pause = GuiButton((Rectangle){950, 200, 120, 40}, "Resume Sim");
  else
    _button_pause = GuiButton((Rectangle){950, 200, 120, 40}, "Pause Sim");
}
