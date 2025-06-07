#include <iostream>

#include <boost/uuid/uuid_io.hpp>

#include "store/GameStore.hpp"
#include "store/UserStore.hpp"

int main ()
{
  User user;
  Game game{19, boost::uuids::random_generator()(), boost::uuids::random_generator()()};

  std::cout << "Hello, World! " << boost::uuids::to_string(user.id ()) << std::endl;
  return 0;
}
