#include <gtest/gtest.h>
#include <string>

#include "../User.hpp"

// The fixture for testing class Foo.
class TestBarkerUser : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  TestBarkerUser() {
     // You can do set-up work for each test here.
      user = nullptr;
      email1 = "email@domain.com";
      password1 = "1234";
      name1 = "coolGuy98";
      bio1 = "I'm just a random guy living my life";

      user2 = nullptr;
      email2 = "otheremail@domain.com";
      password2 = "user2pass";
      name2 = "user2";
      bio2 = "Second user of Barker";

      user3 = nullptr;
      email3 = "fakeemail@domain.com";
      password3 = "user3pass";
      name3 = "user3";
      bio3 = "Third user of Barker";
  }

  ~TestBarkerUser() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
     user = new User(email1, password1, name1, bio1);
     user2 = new User(email2, password2, name2, bio2);
     user3 = new User(email3, password3, name1, bio3);
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
      delete user;
      user = nullptr;

      delete user2;
      user2 = nullptr;

      delete user3;
      user3 = nullptr;
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
  std::string email1, email2, email3;
  std::string password1, password2, password3;
  std::string name1, name2, name3;
  std::string bio1, bio2, bio3;
  User* user, *user2, *user3;
};

TEST_F(TestBarkerUser, UserHasCorrectAttributes)
{
    EXPECT_EQ(email1, user->getEmail());
    EXPECT_EQ(password1, user->getPassword());
    EXPECT_EQ(name1, user->getUsername());
    EXPECT_EQ(bio1, user->getBio());
    EXPECT_EQ(0, user->getFollowers());
    EXPECT_EQ(0, user->getFollowing().size());
}

TEST_F(TestBarkerUser, UserCanBeModified)
{
    std::string new_email = "newmail@domain.com";
    std::string new_password = "securepassword";
    std::string new_name = "coolerGuy98";
    std::string new_bio = "I'm back with more cool facts!";

    user->setEmail(new_email);
    user->setPassword(new_password);
    user->setUsername(new_name);
    user->setBio(new_bio);

    EXPECT_EQ(new_email, user->getEmail());
    EXPECT_EQ(new_password, user->getPassword());
    EXPECT_EQ(new_name, user->getUsername());
    EXPECT_EQ(new_bio, user->getBio());
    EXPECT_EQ(0, user->getFollowers());
    EXPECT_EQ(0, user->getFollowing().size());
}

TEST_F(TestBarkerUser, UserCanFollow)
{
    user->follow(user2);
    ASSERT_EQ(1, user->getFollowing().size());
    EXPECT_EQ(user2, user->getFollowing()[0]);

    user->follow(user3);
    ASSERT_EQ(2, user->getFollowing().size());
    EXPECT_EQ(user2, user->getFollowing()[0]);
    EXPECT_EQ(user3, user->getFollowing()[1]);
}

TEST_F(TestBarkerUser, UserCanUnfollow)
{
    user->follow(user2);
    user->follow(user3);

    user->unfollow(user3);
    EXPECT_EQ(1, user->getFollowing().size());

    user->unfollow(user2);
    EXPECT_EQ(0, user->getFollowing().size());
}

//-- Increment / decrement followers count
TEST_F(TestBarkerUser, UserFollowerCountIncreases)
{
    user->increaseFollowers();
    EXPECT_EQ(1, user->getFollowers());

    user->increaseFollowers();
    user->increaseFollowers();
    EXPECT_EQ(3, user->getFollowers());
}

TEST_F(TestBarkerUser, UserFollowerCountDecreases)
{
    user->increaseFollowers();
    user->increaseFollowers();
    user->increaseFollowers();
    user->increaseFollowers();
    ASSERT_EQ(4, user->getFollowers());

    user->decreaseFollowers();
    EXPECT_EQ(3, user->getFollowers());

    user->decreaseFollowers();
    user->decreaseFollowers();
    EXPECT_EQ(1, user->getFollowers());
}

TEST_F(TestBarkerUser, UserFollowerCountCannotBeNegative)
{
    user->decreaseFollowers();
    EXPECT_EQ(0, user->getFollowers());
}
