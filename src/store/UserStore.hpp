#ifndef STORE_USER_STORE_HPP
#define STORE_USER_STORE_HPP

#include <format>
#include <mutex>
//#include <algorithm>
#include <boost/uuid/uuid_io.hpp>

#include "../common/model/user.hpp"
#include "EntityNotFound.hpp"

class UserStore {
 public:
  UserStore() {}

  virtual void createOrUpdate(const User& user) = 0;
  virtual const User& findUser(const boost::uuids::uuid& id) const = 0;


};

class InMemoryUserStore : public UserStore {

 public:

  void createOrUpdate(const User& user) override {
    std::lock_guard<std::mutex> lock(mtx);
    users.emplace_back(user);
  }

  const User& findUser(const boost::uuids::uuid& id) const override {
    std::lock_guard<std::mutex> lock(mtx);
    auto userIt = std::find_if(users.begin (), users.end (),
                               [&id](const User& user) { return user.id() == id; });
    if (userIt == users.end()) {
      throw EntityNotFoundException(std::format("Failed to find user with id `{}`", boost::uuids::to_string(id)));
    }

    return *userIt; // We will not be deleting users, just marking them 'deleted', so
                    // the user should always exist.
  }

 private:
  mutable std::mutex mtx;
  std::vector<User> users;

};

#endif