/**
 * @file Generation.hpp
 * File containing the Generation class
 */

#ifndef _GENERATION_
#define _GENERATION_

#include "raylib.h"
#include <vector>

#include "Cell.hpp"

/**
 * @brief Generation class
 * Represents an array of cells which evolves at each generations
 */
class Generation {
  private:
    std::vector<std::vector<Cell*> > _cells; /**< std::vector<std::vector<Cell*> > representing an array of cells */
    std::vector<std::vector<Cell*> > _buffer; /**< std::vector<std::vector<Cell*> > representing a buffer array of _cells */

    Vector2 _array_size; /**< Vector2 (raylib) representing the size of the cell array, x = rows, y = columns) */
    float _cell_size; /**< float representing the size of the cell (square) */
    int _random; /**< int representing the percentage of alive cells at the start of the game (0-100) */

  public:
    /**
     * @fn constructor Generation(Vector2 array_size, float cell_size, int random)
     * @brief create a Generation object
     * @param array_size the size of the array
     * @param cell_size the size of a cell
     * @param random the percentage of random alive cells
     */
    Generation(Vector2 array_size, float cell_size, int random) : _array_size(array_size), _cell_size(cell_size), _random(random) {}
    /**
     * @fn destructor ~Generation()
     * @brief destroy the Generation object
     */
    virtual ~Generation() { /*free the vector*/ }

    /* getters and setters */
    Vector2 getSize() const { return _array_size; }

    void init();

    void update();
    void render();

    void fill_buffer();
    bool areCellsDead();
    bool IsCellAlive(int row, int col);
};

#endif
