#ifndef COMMON_MODEL_GAME_HPP
#define COMMON_MODEL_GAME_HPP

#include <chrono>
#include <boost/uuid/uuid.hpp>

class Move {
 public:
  Move(const Position& position): m_position(position), m_played(std::chrono::system_clock::now()) {}
  Move(const Move& other) : m_played(other.m_played), m_position(other.m_position) {}
  Move(Move&& other) noexcept : m_played(std::move(other.m_played)), m_position(std::move(other.m_position)) {} // nothing to nullify on `other`
 private:
  std::chrono::time_point<std::chrono::system_clock> m_played;
  Position m_position;
};

class Game {
 public:


 private:
  boost::uuids::uuid blackUser;
  boost::uuids::uuid whiteUser;

};

#endif