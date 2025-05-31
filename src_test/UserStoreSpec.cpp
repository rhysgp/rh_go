
#define BOOST_TEST_MODULE egg benny smoked salmon tests
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>

#include "../src/store/UserStore.hpp"

BOOST_AUTO_TEST_CASE( users_are_retrievable_after_being_added )
{
  InMemoryUserStore store;
  boost::uuids::uuid id = boost::uuids::random_generator()();
  auto now = std::chrono::system_clock::now();
  auto newUser = User(id, "foo", "Foo Bar", std::nullopt, now, now);
  store.createOrUpdate(newUser);
  BOOST_TEST(store.findUser(id) == newUser);
}
