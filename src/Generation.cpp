#include "Generation.hpp"

#include <stdlib.h>
#include <time.h>

void Generation::init() {
  int initialDownPosition = SIZE_OF_CELL/2;

  Vector2 position;
  position.x = 0;
  position.y = 0;
  Vector2 cell_size;
  cell_size.x = SIZE_OF_CELL;
  cell_size.y = SIZE_OF_CELL;

  // initialize the 2D vector
  for(int i = 0; i < _size.x; i++){
    std::vector<Cell*> v;
    for(int j = 0; j < _size.y; j++)
      v.push_back(new Cell(position, cell_size, false));

    _cells.push_back(v);
  }

  for (int i = 0; i < _size.x; i++){
    for (int j = 0; j < _size.y; j++){
      position.x = (j*SIZE_OF_CELL) + (SIZE_OF_CELL/2) + GAME_SCREEN_OFFSET;
      position.y = (i*SIZE_OF_CELL) + (initialDownPosition) + GAME_SCREEN_OFFSET;
      _cells[i][j]->setPosition(position);

      if(_random >= ((rand()%100)+1))
        _cells[i][j]->setAlive(true);
    }
  }
}

void Generation::update(){
  for (int i = 0; i < _size.x; i++)
    for (int j = 0; j < _size.y; j++)
      _cells[i][j]->setAlive(IsCellAlive(i, j)); // update the cell status
}

void Generation::render(){
  for (int i = 0; i < _size.x; i++){
    for (int j = 0; j < _size.y; j++){
      if(_cells[i][j]->isAlive()){
        if(!Game::getInstance()->getPause() && Game::getInstance()->getRainbow())
          DrawRectangle(
            _cells[i][j]->getPosition().x - _cells[i][j]->getSize().x/2,
            _cells[i][j]->getPosition().y - _cells[i][j]->getSize().y/2,
            _cells[i][j]->getSize().x,
            _cells[i][j]->getSize().y,
            Game::getInstance()->getRandomColor()
          );
        else
          DrawRectangle(
            _cells[i][j]->getPosition().x - _cells[i][j]->getSize().x/2,
            _cells[i][j]->getPosition().y - _cells[i][j]->getSize().y/2,
            _cells[i][j]->getSize().x,
            _cells[i][j]->getSize().y,
            WHITE
          );
      }
      else
        DrawRectangle(
          _cells[i][j]->getPosition().x - _cells[i][j]->getSize().x/2,
          _cells[i][j]->getPosition().y - _cells[i][j]->getSize().y/2,
          _cells[i][j]->getSize().x,
          _cells[i][j]->getSize().y,
          BLACK
        );
    }
  }
}

bool Generation::areCellsDead() {
  for (int i = 0; i < _size.x; i++){
    for (int j = 0; j < _size.y; j++){
      if(_cells[i][j]->isAlive())
        return false;
    }
  }
  return true;
}

bool Generation::IsCellAlive(int row, int col){
  // living cell stay alive (white) if it has 2 or 3 living cells around it
  // dead cell (black) become alive if it has exactly 3 living cells around it

  int cpt_livingCells = 0; // number of living cells around the [i][j] cell

  for(int i=row-1; i <= row+1; i++){
    if(i < 0 || i >= _size.x)
      continue;

    for(int j=col-1; j <= col+1; j++){
      if(j < 0 || j >= _size.y)
        continue;

      if(_cells[i][j]->isAlive())
        cpt_livingCells++;
    }
  }

  if(_cells[row][col]->isAlive()){
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