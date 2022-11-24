#ifndef _GENERATION_
#define _GENERATION_

#include "raylib.h"
#include <vector>

#include "Game.hpp"
#include "Cell.hpp"

class Generation {
  private:
    std::vector<std::vector<Cell*> > _cells;
    Vector2 _size; // x = row, y = column
    int _turns;
    int _random;

  public:
    Generation(Vector2 size) : _size(size), _turns(0), _random(6) {}
    virtual ~Generation() { /*free the vector*/ }

    Vector2 getSize() const { return _size; }
    int getTurns() const { return _turns; }
    inline void addOneTurn() { _turns++; }

    void init();

    void update();
    void render();

    bool areCellsDead();
    bool IsCellAlive(int row, int col);
};

#endif
