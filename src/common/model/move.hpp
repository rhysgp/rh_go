#ifndef COMMON_MODEL_MOVE_HPP
#define COMMON_MODEL_MOVE_HPP

#include "position.hpp"
#include "user.hpp"

class Move {
 public:

 private:
  Position m_position;
  bool m_black;
  User user;
};

#endif