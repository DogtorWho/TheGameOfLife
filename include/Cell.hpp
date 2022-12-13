/**
 * @file Cell.hpp
 * File containing the Cell class
 */

#ifndef _CELL_
#define _CELL_

#include "raylib.h"
#include <iostream>
#include <string>

/**
 * @brief Cell class
 * Represents a cell which can be be alive or dead and has a constant position
 */
class Cell {
  private:
    Vector2 _position; /**< Vector2 (raylib) representing the position of the cell */
    bool _alive; /**< bool representing the state of the cell, true = the cell is alive */

  public:
    /**
     * @fn constructor Cell()
     * @brief create an empty Cell object
     */
    Cell() : _position(Vector2()), _alive(false) {}
    /**
     * @fn constructor Cell(Vector2 position, bool alive)
     * @brief create a Cell object
     * @param position the position of the cell
     * @param alive the state of the cell
     */
    Cell(Vector2 position, bool alive) : _position(position), _alive(alive) {}
    /**
     * @fn destructor ~Cell()
     * @brief destroy the Cell object
     */
    virtual ~Cell(){}

    /* getters and setters */
    void setPosition(Vector2 position) { _position = position; }
    Vector2 getPosition() const { return _position; }
    void setAlive(bool alive) { _alive = alive; }
    bool isAlive() const { return _alive; }

    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& s, const Cell& c);
};

#endif
