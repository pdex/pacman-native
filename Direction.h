// -*- C++ -*-
#ifndef DIRECTION_H
#define DIRECTION_H

#include <ostream>

enum class Direction : int8_t {
  Stop,
  North,
  South,
  East,
  West
};

std::ostream& operator<<(std::ostream& out, Direction direction) {
  switch(direction) {
    case Direction::Stop  : out << "Stop";  break;
    case Direction::North : out << "North"; break;
    case Direction::South : out << "South"; break;
    case Direction::East  : out << "East";  break;
    case Direction::West  : out << "West";  break;
    default               : out.setstate(std::ios_base::failbit);
  }
  return out;
}

#endif//DIRECTION_H
