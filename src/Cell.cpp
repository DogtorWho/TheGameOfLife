#include "Cell.hpp"

std::string Cell::toString() const {
  std::string res;
  res += "Cell : \n";
  res += " - position(";
  res += std::to_string(getPosition().x);
  res += ", ";
  res += std::to_string(getPosition().y);
  res += ")\n";
  res += " - size(";
  res += std::to_string(getSize().x);
  res += ", ";
  res += std::to_string(getSize().y);
  res += ")\n";
  res += " - alive(";
  res += std::to_string(isAlive());
  res += ")\n";
  return res;
}

std::ostream& operator<<(std::ostream& s, const Cell& c) {
	return (s << c.toString());
}
