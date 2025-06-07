#ifndef STORE_GAME_STORE_HPP
#define STORE_GAME_STORE_HPP

#include <format>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_hash.hpp>
#include <vector>
#include <algorithm>

#include "EntityNotFound.hpp"
#include "../common/model/game.hpp"


class GameStore {
public:
  GameStore() = default;
  virtual ~GameStore() = default;

  virtual void createOrUpdate(const Game& game) = 0;
  [[nodiscard]] virtual const Game& findGame(const boost::uuids::uuid& id) const = 0;
};


class InMemoryGameStore: public GameStore {

 public:
  void createOrUpdate(const Game& game) override {
    std::unique_lock lock(mtx);
    games.insert_or_assign(game.id(), game);
  }

  [[nodiscard]] const Game& findGame(const boost::uuids::uuid& id) const override {
    std::shared_lock lock(mtx);
    auto it = games.find(id);
    if (it == games.end()) {
      throw EntityNotFoundException(std::format("Failed to find game with id `{}`", boost::uuids::to_string(id)));
    }
    return it->second;
  }

 private:
  mutable std::shared_mutex mtx;
  std::unordered_map<boost::uuids::uuid, Game, boost::hash<boost::uuids::uuid>> games;
};

#endif