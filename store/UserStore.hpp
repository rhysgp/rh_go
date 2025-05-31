#ifndef STORE_USER_STORE_HPP
#define STORE_USER_STORE_HPP

#include <format>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_hash.hpp>
#include <vector>
#include <algorithm>

#include "../common/model/user.hpp"
#include "EntityNotFound.hpp"

class UserStore {
 public:
  UserStore() = default;

  virtual void createOrUpdate(const User& user) = 0;
  virtual const User& findUser(const boost::uuids::uuid& id) const = 0;


};

class InMemoryUserStore : public UserStore {

 public:

  void createOrUpdate(const User& user) override {
    std::unique_lock lock(mtx);
    users[user.id()] = user;
  }

  const User& findUser(const boost::uuids::uuid& id) const override {
    std::shared_lock lock(mtx);
    auto it = users.find(id);
    if (it == users.end()) {
        throw EntityNotFoundException(std::format("Failed to find user with id `{}`", boost::uuids::to_string(id)));
      }
    return it->second;  }

 private:
  mutable std::shared_mutex mtx;
  std::unordered_map<boost::uuids::uuid, User, boost::hash<boost::uuids::uuid>> users;

};

#endif