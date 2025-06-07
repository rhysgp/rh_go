#ifndef STORE_ENTITY_NOT_FOUND_HPP
#define STORE_ENTITY_NOT_FOUND_HPP

#include <exception>
#include <string>
#include <utility>

class EntityNotFoundException : std::exception {
 private:
  std::string message;

 public:
  explicit EntityNotFoundException(std::string  msg) : message(std::move(msg)) {}

  [[nodiscard]] const char* what() const noexcept override {
    return message.c_str();
  }
};

#endif
