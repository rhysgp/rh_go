#ifndef COMMON_MODEL_USER_HPP
#define COMMON_MODEL_USER_HPP

#include <chrono>
#include <utility>
#include <string>
#include <optional>
#include <ostream>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

class User {
 public:
  User()
    : m_id(boost::uuids::random_generator()())
  {
  }

  User (const boost::uuids::uuid &id,
        std::string name,
        std::string displayName,
        const std::optional<std::chrono::year_month_day> &date_of_birth,
        const std::chrono::time_point<std::chrono::system_clock> &created,
        const std::chrono::time_point<std::chrono::system_clock> &updated)
      : m_id (id), m_name (std::move(name)), m_displayName (std::move(displayName)),
        m_dateOfBirth (date_of_birth), m_created (created), m_updated (updated)
  {}

  bool operator==(const User& other) const = default;

  std::ostream& operator<<(std::ostream& os) {
    os << "User{"
       << "id=" << m_id
       << ", name=" << m_name
       << ", displayName=" << m_displayName;
    if (m_dateOfBirth) {
        auto dob = *m_dateOfBirth;
        os << ", dob=" << static_cast<int>(dob.year()) << "-"
           << static_cast<unsigned>(dob.month()) << "-"
           << static_cast<unsigned>(dob.day());
      } else {
        os << ", dob=null";
      }
    os << ", created=[...], updated=[...]"
       << "}";
    return os;
  }

  [[nodiscard]] boost::uuids::uuid id() const { return m_id; }
  [[nodiscard]] const std::string& name() const { return m_name; }
  [[nodiscard]] const std::string& displayName() const { return m_displayName; }
  [[nodiscard]] const std::optional<std::chrono::year_month_day>& dateOfBirth() const { return m_dateOfBirth; }
  [[nodiscard]] std::chrono::time_point<std::chrono::system_clock> created() const { return m_created; }
  [[nodiscard]] std::chrono::time_point<std::chrono::system_clock> updated() const { return m_updated; }

 private:
  boost::uuids::uuid m_id;
  std::string m_name;
  std::string m_displayName;
  std::optional<std::chrono::year_month_day> m_dateOfBirth;
  std::chrono::time_point<std::chrono::system_clock> m_created;
  std::chrono::time_point<std::chrono::system_clock> m_updated;

};

#endif
