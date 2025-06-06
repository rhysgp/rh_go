
#define BOOST_TEST_MODULE rhgo
#define BOOST_TEST_DYN_LINK

#include <chrono>
#include <optional>
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

BOOST_AUTO_TEST_CASE( users_can_be_updated )
{
  InMemoryUserStore store;
  boost::uuids::uuid id = boost::uuids::random_generator()();
  auto now = std::chrono::system_clock::now();
  auto newUser = User(id, "foo", "Foo Bar", std::nullopt, now, now);
  auto dob = std::chrono::year_month_day(std::chrono::year(1971), std::chrono::January, std::chrono::day(12));
  auto updatedUser = User(id, "bar", "Bar Foo", std::make_optional(dob), now, std::chrono::system_clock::now());
  store.createOrUpdate(newUser);
  store.createOrUpdate(updatedUser);
  BOOST_TEST(store.findUser(id) == updatedUser);
}
