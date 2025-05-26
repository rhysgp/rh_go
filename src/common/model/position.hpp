#ifndef COMMON_MODEL_POSITION
#define COMMON_MODEL_POSITION

class Position {
 public:
  Position(int horizontal, int vertical)
      : m_horizontal(horizontal), m_vertical(vertical)
  {
  }

  Position(const Position& p)
      : m_horizontal(p.m_horizontal), m_vertical(p.m_vertical) { }

  Position(Position&& p) noexcept = default;

  Position& operator=(const Position& other) {
    if (this != &other) {
        m_horizontal = other.m_horizontal;
        m_vertical = other.m_vertical;
      }
    return *this;
  }

  Position& operator=(Position&& other) noexcept {
    if (this != &other) {
        m_horizontal = other.m_horizontal;
        m_vertical = other.m_vertical;
        other.m_horizontal = 0;
        other.m_vertical = 0;
      }
    return *this;
  }

  [[nodiscard]] int horizontal() const { return m_horizontal; }
  [[nodiscard]] int vertical() const { return m_vertical; }
 private:
  int m_horizontal;
  int m_vertical;
};



#endif