#ifndef _CELL_
#define _CELL_

#include "raylib.h"
#include <iostream>
#include <string>

class Cell {
  private:
    Vector2 _position;
    bool _alive;

  public:
    Cell() : _position(Vector2()), _alive(false) {}
    Cell(Vector2 position, bool alive) : _position(position), _alive(alive) {}
    virtual ~Cell(){}

    void setPosition(Vector2 position) { _position = position; }
    Vector2 getPosition() const { return _position; }
    void setAlive(bool alive) { _alive = alive; }
    bool isAlive() const { return _alive; }

    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& s, const Cell& c);
};

#endif
