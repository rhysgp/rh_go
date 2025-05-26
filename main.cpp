#include <iostream>

#include <boost/uuid/uuid_io.hpp>

#include "src/common/model/user.hpp"

int main ()
{
  User user;

  std::cout << "Hello, World! " << boost::uuids::to_string(user.id ()) << std::endl;
  return 0;
}
