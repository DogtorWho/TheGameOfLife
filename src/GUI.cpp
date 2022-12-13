#include "GUI.hpp"

#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"

#include "raymath.h"
#include "Game.hpp"

GUI *GUI::instance = nullptr;

void GUI::init(){
  _button_start = {Game::getInstance()->getGameArea().width/2 + Game::getInstance()->getGameArea().x - 150, 675, 300, 100};
  _button_pause = {250, 700, 150, 50};
  _button_stop = {600, 700, 150, 50};

  _settings_origin = {975, 50};
  _dropdownbox_array_size = {_settings_origin.x, _settings_origin.y + 90, 100, 20};
  _checkbox_inf_gen = {_settings_origin.x, _settings_origin.y + 160, 20, 20};
  _slider_nb_gen = {_settings_origin.x + 40, _settings_origin.y + 190, 80, 20};
  _slider_nb_random = {_settings_origin.x, _settings_origin.y + 260, 150, 20};
  _slider_speed = {_settings_origin.x, _settings_origin.y + 330, 80, 20};
}

void GUI::clean(){
  // empty
}

void GUI::update(){
  if(Game::getInstance()->getRun()){
    if(IsKeyPressed('P') || GuiButton(_button_pause, "Pause"))
      Game::getInstance()->setPause(!Game::getInstance()->getPause());

    if(GuiButton(_button_stop, "Stop")){
      Game::getInstance()->setPause(false);
      Game::getInstance()->setRun(false);
      Game::getInstance()->setEndingScreen(true);
    }

    if (IsKeyPressed('R'))
      Game::getInstance()->setRainbow(!Game::getInstance()->getRainbow());
  }
  else{
    if(GuiButton(_button_start, "Start")){
      Game::getInstance()->init_game();
      Game::getInstance()->setEndingScreen(false);
      Game::getInstance()->setRun(true);
    }
  }
}

void GUI::render(){
  int border_size = 5;
  DrawRectangleLinesEx((Rectangle){Game::getInstance()->getGameArea().x - border_size,
                                    Game::getInstance()->getGameArea().y - border_size,
                                    Game::getInstance()->getGameArea().width + (border_size * 2),
                                    Game::getInstance()->getGameArea().height + (border_size * 2)},
                        border_size, LIGHTGRAY);

  std::string text_nb_generation = "GEN : ";
  text_nb_generation += std::to_string(Game::getInstance()->getNbGeneration());
  DrawText(text_nb_generation.c_str(), Game::getInstance()->getGameArea().x + 5, Game::getInstance()->getGameArea().y - 25, 20, GRAY);

  if(Game::getInstance()->getRun()){
    GuiButton(_button_pause, "Pause");
    GuiButton(_button_stop, "Stop");
  }
  else{
    GuiButton(_button_start, "Start");
  }

  DrawText("Settings", _settings_origin.x, _settings_origin.y, 40, GRAY);

  if(Game::getInstance()->getRun())
    GuiDisable();

  DrawLine(_settings_origin.x, _settings_origin.y + 50, _settings_origin.x + MeasureText("Settings", 40), _settings_origin.y + 50, GRAY);

  DrawText("Map Size", _settings_origin.x, _settings_origin.y + 60, 25, GRAY);
  int v1 = 0;
  GuiDropdownBox(_dropdownbox_array_size, "60x90", &v1, false);

  DrawText("Randomness", _settings_origin.x, _settings_origin.y + 230, 25, GRAY);
  Game::getInstance()->setNbRandom(GuiSlider(_slider_nb_random, "", std::to_string(Game::getInstance()->getNbRandom()).c_str(), (float)Game::getInstance()->getNbRandom(), 0.f, 100.f));

  DrawText("Generations", _settings_origin.x, _settings_origin.y + 130, 25, GRAY);
  Game::getInstance()->setInfiniteGeneration(GuiCheckBox(_checkbox_inf_gen, "Infinite", Game::getInstance()->getInfiniteGeneration()));

  if(Game::getInstance()->getInfiniteGeneration())
    GuiDisable();

  Game::getInstance()->setNbGenerationMax(GuiSlider(_slider_nb_gen, "Number", std::to_string(Game::getInstance()->getNbGenerationMax()).c_str(), (float)Game::getInstance()->getNbGenerationMax(), 1.f, 500.f));

  GuiEnable();

  DrawText("Speed", _settings_origin.x, _settings_origin.y + 300, 25, GRAY);
  int tmp_speed;
  switch (Game::getInstance()->getSpeedMax()){
    case 8 : tmp_speed = 1; break;
    case 4 : tmp_speed = 2; break;
    case 2 : tmp_speed = 3; break;
    case 1 : tmp_speed = 4; break;
    default : tmp_speed = 4;
  }
  tmp_speed = GuiSlider(_slider_speed, "", std::to_string(tmp_speed).c_str(), (float)tmp_speed, 1.f, 4.f);
  switch (tmp_speed){
    case 1 : Game::getInstance()->setSpeedMax(8); break;
    case 2 : Game::getInstance()->setSpeedMax(4); break;
    case 3 : Game::getInstance()->setSpeedMax(2); break;
    case 4 : Game::getInstance()->setSpeedMax(1); break;
    default : Game::getInstance()->setSpeedMax(1);
  }
}
