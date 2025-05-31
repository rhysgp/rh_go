#ifndef STORE_ENTITY_NOT_FOUND_HPP
#define STORE_ENTITY_NOT_FOUND_HPP

#include <exception>
#include <string>

class EntityNotFoundException : std::exception {
 private:
  std::string message;

 public:
  EntityNotFoundException(const std::string& msg) : message(msg) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};

#endif
