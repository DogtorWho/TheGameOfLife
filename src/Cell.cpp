/**
 * @file Cell.cpp
 * File containing the functions of the Cell class
 */

#include "Cell.hpp"

/**
 * @fn std::string toString() const
 * @brief transform the Cell informations into a string
 */
std::string Cell::toString() const {
  std::string res;
  res += "Cell : \n";
  res += " - position(";
  res += std::to_string(getPosition().x);
  res += ", ";
  res += std::to_string(getPosition().y);
  res += ")\n";
  res += " - alive(";
  res += std::to_string(isAlive());
  res += ")\n";
  return res;
}

/**
 * @fn std::ostream& operator<<(std::ostream& s, const Cell& c)
 * @brief override the << operator for the Cell object
 * transform the Cell informations into a string and send it to the output stream
 * @param s the output stream where the string will be writen
 * @param c the Cell to write in the stream
 */
std::ostream& operator<<(std::ostream& s, const Cell& c) {
	return (s << c.toString());
}
