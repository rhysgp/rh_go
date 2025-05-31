#include <iostream>

#include <boost/uuid/uuid_io.hpp>

#include "common/model/user.hpp"
#include "common/model/game.hpp"

int main ()
{
  User user;
  Game game{boost::uuids::random_generator()(), boost::uuids::random_generator()()};

  std::cout << "Hello, World! " << boost::uuids::to_string(user.id ()) << std::endl;
  return 0;
}
