#include "GUI.hpp"

#include "Game.hpp"
#include "Menu.hpp"

GUI *GUI::instance = nullptr;

void GUI::init(){
  Menu::getInstance()->init();
  Game::getInstance()->init();
}

void GUI::clean(){
  Game::getInstance()->clean();
  Menu::getInstance()->clean();
}

void GUI::update(){
  Menu::getInstance()->update();
  Game::getInstance()->update();
}

void GUI::render(){
  BeginDrawing();

  ClearBackground(RAYWHITE);

  Menu::getInstance()->render();
  Game::getInstance()->render();

  EndDrawing();
}
