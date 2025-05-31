#ifndef COMMON_MODEL_GAME_HPP
#define COMMON_MODEL_GAME_HPP

#include <memory>
#include <vector>
#include <chrono>
#include <boost/uuid/uuid.hpp>

#include "move.hpp"

class Game {
 public:
  Game(boost::uuids::uuid blackUser, boost::uuids::uuid whiteUser)
    : m_created(std::chrono::system_clock::now()), m_blackUser(blackUser), m_whiteUser(whiteUser) {}

  Game(const Game& other) = default;
  Game(Game&& other) noexcept = default;

  void playMove(std::unique_ptr<Move> move) {
    m_moves.emplace_back(std::move(move));
  }

 private:
  std::chrono::time_point<std::chrono::system_clock> m_created;
  boost::uuids::uuid m_blackUser;
  boost::uuids::uuid m_whiteUser;
  std::vector<std::unique_ptr<Move>> m_moves; // You need to store polymorphic objects via pointers or smart pointers in the vector.
};

#endif