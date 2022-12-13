/**
 * @file Generation.cpp
 * File containing the functions of the Generation class
 */

#include "Generation.hpp"

#include <stdlib.h>
#include <time.h>

#include "Game.hpp"

/**
 * @fn void init()
 * @brief initialize the Generation class
 */
void Generation::init() {
  int initialDownPosition = _cell_size/2;

  Vector2 position;
  position.x = 0;
  position.y = 0;

  /* initialize the cell array and its buffer */
  for(int i = 0; i < _array_size.x; i++){
    std::vector<Cell*> v;
    std::vector<Cell*> v_buf;

    for(int j = 0; j < _array_size.y; j++){
      position.x = (j*_cell_size) + (_cell_size/2);
      position.y = (i*_cell_size) + (initialDownPosition);

      if(_random >= ((rand()%100)+1))
        v.push_back(new Cell(position, true));
      else
        v.push_back(new Cell(position, false));

      v_buf.push_back(new Cell(position, false));
    }

    _cells.push_back(v);
    _buffer.push_back(v_buf);
  }
}

/**
 * @fn void update()
 * @brief update the Generation class
 */
void Generation::update(){
  fill_buffer();

  for (int i = 0; i < _array_size.x; i++)
    for (int j = 0; j < _array_size.y; j++)
      _cells[i][j]->setAlive(IsCellAlive(i, j)); // update the cell status
}

/**
 * @fn void render()
 * @brief render the Generation class
 */
void Generation::render(){
  for (int i = 0; i < _array_size.x; i++){
    for (int j = 0; j < _array_size.y; j++){
      if(_cells[i][j]->isAlive()){ // to reduce the lag we only render the alive cells
        if(!Game::getInstance()->getPause() && Game::getInstance()->getRainbow()){
          DrawRectangle(
            _cells[i][j]->getPosition().x - _cell_size/2,
            _cells[i][j]->getPosition().y - _cell_size/2,
            _cell_size,
            _cell_size,
            Game::getInstance()->get_random_color()
          );
        }
        else{
          DrawRectangle(
            _cells[i][j]->getPosition().x - _cell_size/2,
            _cells[i][j]->getPosition().y - _cell_size/2,
            _cell_size,
            _cell_size,
            WHITE
          );
        }
      }
    }
  }
}

/**
 * @fn void fill_buffer()
 * @brief fill the buffer array
 * Copy the cells array informations into the buffer
 */
void Generation::fill_buffer(){
  for (int i = 0; i < _array_size.x; i++)
    for (int j = 0; j < _array_size.y; j++)
      _buffer[i][j]->setAlive(_cells[i][j]->isAlive());
}

/**
 * @fn bool areCellsDead()
 * @brief check if at least one cell is alive
 * Copy the cells array informations into the buffer
 * @return the state of the cells in the array
 */
bool Generation::areCellsDead(){
  for (int i = 0; i < _array_size.x; i++){
    for (int j = 0; j < _array_size.y; j++){
      if(_cells[i][j]->isAlive())
        return false;
    }
  }
  return true;
}

/**
 * @fn bool IsCellAlive()
 * @brief check if the cell should be alive
 * Update the cell state with the rules of the Game of Life :
 * - living cell stay alive if it has 2 or 3 living cells around it
 * - dead cell become alive if it has exactly 3 living cells around it
 * @return the state of the cell at the position given
 */
bool Generation::IsCellAlive(int row, int col){
  int cpt_livingCells = 0; // number of living cells around the [i][j] cell

  for(int i = row-1; i <= row+1; i++){
    if(i < 0 || i >= _array_size.x)
      continue;

    for(int j=col-1; j <= col+1; j++){
      if(j < 0 || j >= _array_size.y)
        continue;

      if(_buffer[i][j]->isAlive())
        cpt_livingCells++;
    }
  }

  if(_buffer[row][col]->isAlive()){
    cpt_livingCells--; // remove the current living cell

    if(cpt_livingCells == 2 || cpt_livingCells == 3){
      return true;
    }
  }
  else{ // the current cell is dead
    if(cpt_livingCells == 3)
      return true;
  }

  return false;
}
