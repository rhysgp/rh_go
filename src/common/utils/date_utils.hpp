#ifndef COMMON_MODEL_DATE_UTILS_HPP
#define COMMON_MODEL_DATE_UTILS_HPP

#include <chrono>

class DateUtils {

public:
  [[nodiscard]] static const std::chrono::year_month_day dob(int year, int month, int day) {
    return std::chrono::year_month_day(std::chrono::year(year), std::chrono::month(month), std::chrono::day(day));
  }
};


#endif