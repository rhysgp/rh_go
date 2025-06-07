#ifndef COMMON_MODEL_MOVE_HPP
#define COMMON_MODEL_MOVE_HPP

#include <utility>

#include "position.hpp"
#include "user.hpp"

class Move {
public:
  virtual ~Move() = default;

  [[nodiscard]] virtual bool isPlay() const = 0;
  [[nodiscard]] virtual bool isUndo() const = 0;

  [[nodiscard]] virtual std::unique_ptr<Move> clone() const = 0;

  [[nodiscard]] std::chrono::time_point<std::chrono::system_clock> timePlayed() const {
    return m_timePlayed;
  }

  [[nodiscard]] virtual const Position& position() const = 0;

  virtual void print(std::ostream&) const = 0;

protected:
  Move() : m_timePlayed(std::chrono::system_clock::now()) {}
  explicit Move(const std::chrono::time_point<std::chrono::system_clock>& timePlayed) : m_timePlayed(timePlayed) {}

  Move(const Move&) = default;
  Move(Move&&) = default;
  Move& operator=(const Move&) = default;
  Move& operator=(Move&&) = default;

  std::chrono::time_point<std::chrono::system_clock> m_timePlayed;
};

class PlayMove final : public Move {
public:
  PlayMove(Position  position, bool black): m_position(std::move(position)), m_black(black) {}
  PlayMove(const PlayMove& other) : Move(other.m_timePlayed), m_position(other.m_position), m_black(other.m_black) {}
  PlayMove(PlayMove&& other) noexcept : Move(other.m_timePlayed), m_position(std::move(other.m_position)), m_black(other.m_black) {} // nothing to nullify on `other`

  PlayMove& operator=(const PlayMove&) = default;
  PlayMove& operator=(PlayMove&&) = default;

  [[nodiscard]] std::unique_ptr<Move> clone() const override {
    return std::make_unique<PlayMove>(*this);  // Use copy constructor
  }

  void print(std::ostream& os) const override {
    os << "PlayMove{ "
       << (m_black ? "BLACK " : "WHITE ")
       << m_position.horizontal()
       << " / "
       << m_position.vertical()
       << " }";
  }

  [[nodiscard]] bool isPlay() const override { return true; }
  [[nodiscard]] bool isUndo() const override { return false; }
  [[nodiscard]] const Position& position() const override { return m_position; }
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

  [[nodiscard]] bool isPlay() const override { return false; }
  [[nodiscard]] bool isUndo() const override { return true; }

  void print(std::ostream& os) const override {
    os << "UndoMove{}";
  }

  [[nodiscard]] const Position& position() const override { throw std::logic_error("Undo move has no explicit position"); }

  [[nodiscard]] std::unique_ptr<Move> clone() const override {
    return std::make_unique<UndoMove>(*this);
  }
};

#endif