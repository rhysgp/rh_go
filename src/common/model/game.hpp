#ifndef COMMON_MODEL_GAME_HPP
#define COMMON_MODEL_GAME_HPP

#include <memory>
#include <vector>
#include <chrono>
#include <boost/uuid/uuid.hpp>

#include "move.hpp"

class Game {
 public:
  Game(boost::uuids::uuid id, boost::uuids::uuid blackUser, boost::uuids::uuid whiteUser)
    : m_id(id), m_created(std::chrono::system_clock::now()), m_blackUser(blackUser), m_whiteUser(whiteUser) {}
  Game(boost::uuids::uuid blackUser, boost::uuids::uuid whiteUser) : Game(boost::uuids::random_generator()(), blackUser, whiteUser) {};
  Game(const Game& other) : m_created(other.m_created), m_id(other.m_id), m_blackUser(other.m_blackUser), m_whiteUser(other.m_whiteUser) {
    m_moves.reserve(other.m_moves.size());
    for (const auto& move : other.m_moves) {
      m_moves.push_back(move->clone());
    }
  }
  Game(Game&& other) noexcept = default;
  ~Game() = default;

  bool operator==(const Game& other) const {
    return other.m_id == m_id
      && other.m_whiteUser == m_whiteUser
      && other.m_blackUser == m_blackUser
      && other.m_moves.size() == m_moves.size(); // NB We're assuming moves are never updated, only ever added to
  }

  Game& operator=(Game&& other) noexcept = default;
  Game& operator=(const Game& other) {
    Game temp(other);
    std::swap(*this, temp);
    return *this;
  }

  void playMove(std::unique_ptr<Move> move) {
    m_moves.emplace_back(std::move(move));
  }

  friend std::ostream& operator<<(std::ostream& os, const Game& game) {
    os << "User{"
       << "id=" << game.m_id
       << ", black=" << game.m_blackUser
       << ", white=" << game.m_whiteUser;
    bool first = true;
    for (auto& m : game.m_moves) {
      if (first) { first = false; } else { os << ", "; }
      m->print(os);
    }
    os << "}";
    return os;
  }

  [[nodiscard]] boost::uuids::uuid id() const { return m_id; }
  [[nodiscard]] boost::uuids::uuid blackUser() const { return m_blackUser; }
  [[nodiscard]] boost::uuids::uuid whiteUser() const { return m_whiteUser; }
  [[nodiscard]] const std::vector<std::unique_ptr<Move>>& moves() const { return m_moves; }

private:
  std::chrono::time_point<std::chrono::system_clock> m_created;
  boost::uuids::uuid m_id;
  boost::uuids::uuid m_blackUser;
  boost::uuids::uuid m_whiteUser;
  std::vector<std::unique_ptr<Move>> m_moves; // You need to store polymorphic objects via pointers or smart pointers in the vector.
};

#endif