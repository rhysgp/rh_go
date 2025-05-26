#ifndef COMMON_MODEL_GAME_HPP
#define COMMON_MODEL_GAME_HPP

#include <chrono>
#include <boost/uuid/uuid.hpp>

class Move {
 public:
 private:
  std::chrono::time_point<std::chrono::system_clock> played;
};

class Game {
 public:


 private:
  boost::uuids::uuid blackUser;
  boost::uuids::uuid whiteUser;

};

#endif