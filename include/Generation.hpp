#ifndef _GENERATION_
#define _GENERATION_

#include "raylib.h"
#include <vector>

#include "Cell.hpp"

class Generation {
  private:
    std::vector<std::vector<Cell*> > _cells;
    std::vector<std::vector<Cell*> > _buffer;

    Vector2 _array_size; // x = row, y = column
    float _cell_size;
    int _random;

  public:
    Generation(Vector2 array_size, float cell_size, int random) : _array_size(array_size), _cell_size(cell_size), _random(random) {}
    virtual ~Generation() { /*free the vector*/ }

    Vector2 getSize() const { return _array_size; }

    void init();

    void update();
    void render();

    void fill_buffer();
    bool areCellsDead();
    bool IsCellAlive(int row, int col);
};

#endif
