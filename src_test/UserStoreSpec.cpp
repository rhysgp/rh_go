
#define BOOST_TEST_MODULE rhgo
#define BOOST_TEST_DYN_LINK

#include <chrono>
#include <optional>
#include <boost/test/included/unit_test.hpp>

#include "../src/store/UserStore.hpp"
#include "../src/common/utils/date_utils.hpp"

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

BOOST_AUTO_TEST_CASE( updating_one_user_does_not_overwrite_a_different_user )
{
  InMemoryUserStore store;
  boost::uuids::uuid id1 = boost::uuids::random_generator()();
  boost::uuids::uuid id2 = boost::uuids::random_generator()();
  auto now = std::chrono::system_clock::now();
  auto u1 = User(id1, "neil_macgregor", "Neil MacGregor", std::make_optional(DateUtils::dob(1946, 6, 16)), now, now);
  auto u2 = User(id2, "trotten", "Standing Desk", DateUtils::dob(2020, 3, 19), now, now);
  auto updatedU1 = User(id1, "neil_the_great", "The History of Neil in 100 Books", std::make_optional(DateUtils::dob(1946, 6, 16)), now, now);
  store.createOrUpdate(u1);
  store.createOrUpdate(u2);
  store.createOrUpdate(updatedU1);
  BOOST_TEST(store.findUser(id1) == updatedU1);
  BOOST_TEST(store.findUser(id2) == u2);
}
