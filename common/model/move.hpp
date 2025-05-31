#ifndef COMMON_MODEL_MOVE_HPP
#define COMMON_MODEL_MOVE_HPP

#include "position.hpp"
#include "user.hpp"

class Move {
public:
  virtual ~Move() = default;

  virtual bool isPlay() const = 0;
  virtual bool isUndo() const = 0;

  [[nodiscard]] std::chrono::time_point<std::chrono::system_clock> timePlayed() const {
    return m_timePlayed;
  }

protected:
  Move() : m_timePlayed(std::chrono::system_clock::now()) {}
  Move(const std::chrono::time_point<std::chrono::system_clock>& timePlayed) : m_timePlayed(timePlayed) {}

  Move(const Move&) = default;
  Move(Move&&) = default;
  Move& operator=(const Move&) = default;
  Move& operator=(Move&&) = default;

  std::chrono::time_point<std::chrono::system_clock> m_timePlayed;
};

class PlayMove final : public Move {
public:
  PlayMove(const Position& position, bool black): m_position(position), m_black(black) {}
  PlayMove(const PlayMove& other) : Move(other.m_timePlayed), m_position(other.m_position), m_black(other.m_black) {}
  PlayMove(PlayMove&& other) noexcept : Move(std::move(other.m_timePlayed)), m_position(std::move(other.m_position)), m_black(other.m_black) {} // nothing to nullify on `other`

  PlayMove& operator=(const PlayMove&) = default;
  PlayMove& operator=(PlayMove&&) = default;

  [[nodiscard]] bool isPlay() const override { return true; }
  [[nodiscard]] bool isUndo() const override { return false; }
  [[nodiscard]] const Position& position() const { return m_position; }
  [[nodiscard]] bool isBlack() const { return m_black; }


private:
  Position m_position;
  bool m_black;
};

/**
 * Undo last move.
 */
class UndoMove final : public Move {
public:
  UndoMove() = default;

  bool isPlay() const override { return false; }
  bool isUndo() const override { return true; }

};

#endif