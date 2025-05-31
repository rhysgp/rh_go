#ifndef COMMON_MODEL_USER_HPP
#define COMMON_MODEL_USER_HPP

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <chrono>
#include <utility>

class User {
 public:
  User()
    : m_id(boost::uuids::random_generator()())
  {
  }

  User (const boost::uuids::uuid &m_id,
        std::string m_name,
        std::string m_display_name,
        const std::optional<std::chrono::year_month_day> &m_date_of_birth,
        const std::chrono::time_point<std::chrono::system_clock> &m_created,
        const std::chrono::time_point<std::chrono::system_clock> &m_updated)
      : m_id (m_id), m_name (std::move(m_name)), m_displayName (std::move(m_display_name)),
        m_dateOfBirth (m_date_of_birth), m_created (m_created), m_updated (m_updated)
  {}

  [[nodiscard]] boost::uuids::uuid id() const { return m_id; }

  [[nodiscard]] const std::string& name() const { return m_name; };
  [[nodiscard]] const std::string& displayName() const { return m_displayName; };
  [[nodiscard]] const std::optional<std::chrono::year_month_day>& dateOfBirth() const { return m_dateOfBirth; };
  [[nodiscard]] std::chrono::time_point<std::chrono::system_clock> created() const { return m_created; };
  [[nodiscard]] std::chrono::time_point<std::chrono::system_clock> updated() const { return m_updated; };

 private:
  boost::uuids::uuid m_id;
  std::string m_name;
  std::string m_displayName;
  std::optional<std::chrono::year_month_day> m_dateOfBirth;
  std::chrono::time_point<std::chrono::system_clock> m_created;
  std::chrono::time_point<std::chrono::system_clock> m_updated;

};

#endif
