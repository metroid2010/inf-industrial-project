#include <gtest/gtest.h>
#include <string>

#include "../User.hpp"
#include "../Manager.hpp"

// The fixture for testing class Foo.
class TestBarkerManagerBasic : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  TestBarkerManagerBasic() {
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

  ~TestBarkerManagerBasic() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
     user = new User(email1, password1, name1, bio1);
     user2 = new User(email2, password2, name2, bio2);
     user3 = new User(email3, password3, name3, bio3);
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


TEST_F(TestBarkerManagerBasic, ManagerCanCreateAndShowAllUsers)
{
    Manager manager;
    ASSERT_TRUE(manager.createUser(email1, password1, name1, bio1));
    std::vector<PublicUserData*> users = manager.showUsers();
    ASSERT_EQ(1, users.size());
    EXPECT_EQ(name1, users[0]->getUsername());
    EXPECT_EQ(bio1, users[0]->getBio());
    EXPECT_EQ(0, users[0]->getFollowers());
    EXPECT_EQ(0, users[0]->getFollowing().size());

    ASSERT_TRUE(manager.createUser(email2, password2, name2, bio2));
    users = manager.showUsers();
    ASSERT_EQ(2, users.size());
    EXPECT_EQ(name2, users[1]->getUsername());
    EXPECT_EQ(bio2, users[1]->getBio());
    EXPECT_EQ(0, users[1]->getFollowers());
    EXPECT_EQ(0, users[1]->getFollowing().size());
}

TEST_F(TestBarkerManagerBasic, ManagerCanShowSingleUser)
{
    Manager manager;
    ASSERT_TRUE(manager.createUser(email1, password1, name1, bio1));
    ASSERT_TRUE(manager.createUser(email2, password2, name2, bio2));
    ASSERT_TRUE(manager.createUser(email3, password3, name3, bio3));

    PublicUserData* user = manager.showUser(name2);

    ASSERT_NE(nullptr, user);
    EXPECT_EQ(name2, user->getUsername());
    EXPECT_EQ(bio2, user->getBio());
    EXPECT_EQ(0, user->getFollowers());
    EXPECT_EQ(0, user->getFollowing().size());

    user = manager.showUser(name3);

    ASSERT_NE(nullptr, user);
    EXPECT_EQ(name3, user->getUsername());
    EXPECT_EQ(bio3, user->getBio());
    EXPECT_EQ(0, user->getFollowers());
    EXPECT_EQ(0, user->getFollowing().size());

    user = manager.showUser(name1);

    ASSERT_NE(nullptr, user);
    EXPECT_EQ(name1, user->getUsername());
    EXPECT_EQ(bio1, user->getBio());
    EXPECT_EQ(0, user->getFollowers());
    EXPECT_EQ(0, user->getFollowing().size());
}

TEST_F(TestBarkerManagerBasic, ManagerCannotDuplicateUser)
{
    Manager manager;
    ASSERT_TRUE(manager.createUser(email1, password1, name1, bio1));
    std::vector<PublicUserData*> users = manager.showUsers();
    ASSERT_EQ(1, users.size());
    EXPECT_EQ(name1, users[0]->getUsername());
    EXPECT_EQ(bio1, users[0]->getBio());
    EXPECT_EQ(0, users[0]->getFollowers());
    EXPECT_EQ(0, users[0]->getFollowing().size());

    ASSERT_FALSE(manager.createUser(email1, password1, name1, bio1));
    users = manager.showUsers();
    ASSERT_EQ(1, users.size());
}


TEST_F(TestBarkerManagerBasic, ManagerCanLoginUser)
{
    Manager manager;
    ASSERT_TRUE(manager.createUser(email1, password1, name1, bio1));
    std::vector<PublicUserData*> users = manager.showUsers();
    ASSERT_EQ(1, users.size());
    EXPECT_EQ(name1, users[0]->getUsername());
    EXPECT_EQ(bio1, users[0]->getBio());
    EXPECT_EQ(0, users[0]->getFollowers());
    EXPECT_EQ(0, users[0]->getFollowing().size());

    EXPECT_TRUE(manager.login(email1, password1));
    EXPECT_TRUE(manager.isLogged());
    User *logged_user = manager.getCurrentUser();
    ASSERT_NE(nullptr, logged_user);
    EXPECT_EQ(name1, logged_user->getUsername());
    EXPECT_EQ(bio1, logged_user->getBio());
    EXPECT_EQ(name1, logged_user->getUsername());
    EXPECT_EQ(bio1, logged_user->getBio());
    EXPECT_EQ(0, logged_user->getFollowers());
    EXPECT_EQ(0, logged_user->getFollowing().size());
}

TEST_F(TestBarkerManagerBasic, ManagerWrongUserCannotLogin)
{
    Manager manager;
    ASSERT_TRUE(manager.createUser(email1, password1, name1, bio1));
    EXPECT_FALSE(manager.login(email1, password2));
    EXPECT_FALSE(manager.isLogged());
    EXPECT_EQ(nullptr, manager.getCurrentUser());
    EXPECT_FALSE(manager.login(email2, password2));
    EXPECT_FALSE(manager.isLogged());
    EXPECT_EQ(nullptr, manager.getCurrentUser());
}

TEST_F(TestBarkerManagerBasic, ManagerCannotLoginUserTwice)
{
    Manager manager;
    ASSERT_TRUE(manager.createUser(email1, password1, name1, bio1));
    ASSERT_TRUE(manager.createUser(email2, password2, name2, bio2));
    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.isLogged());
    EXPECT_FALSE(manager.login(email1, password1));
    EXPECT_FALSE(manager.login(email2, password2));
}

TEST_F(TestBarkerManagerBasic, ManagerCanLogoutUser)
{
    Manager manager;
    ASSERT_TRUE(manager.createUser(email1, password1, name1, bio1));
    ASSERT_TRUE(manager.createUser(email2, password2, name2, bio2));
    EXPECT_FALSE(manager.logout());  //-- No user logged in yet
    ASSERT_TRUE(manager.login(email1, password1));
    EXPECT_TRUE(manager.logout());
    EXPECT_EQ(nullptr, manager.getCurrentUser());
}


TEST_F(TestBarkerManagerBasic, ManagerCanEraseLoggedUser)
{
    Manager manager;
    ASSERT_FALSE(manager.eraseCurrentUser()); //-- Error if not logged in
    ASSERT_TRUE(manager.createUser(email1, password1, name1, bio1));
    ASSERT_TRUE(manager.createUser(email2, password2, name2, bio2));
    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.eraseCurrentUser());
    EXPECT_EQ(nullptr, manager.getCurrentUser());
    std::vector<PublicUserData*> users = manager.showUsers();
    ASSERT_EQ(1, users.size());
    EXPECT_EQ(name2, users[0]->getUsername());
}

TEST_F(TestBarkerManagerBasic, ManagerLoggedUserCanEditProfile)
{
    Manager manager;
    ASSERT_TRUE(manager.createUser(email1, password1, name1, bio1));
    ASSERT_TRUE(manager.createUser(email2, password2, name2, bio2));
    EXPECT_FALSE(manager.editEmail(email3)); //-- Cannot edit profile if not logged in
    EXPECT_FALSE(manager.editPassword(password3)); //-- Cannot edit profile if not logged in
    EXPECT_FALSE(manager.editUsername(name3)); //-- Cannot edit profile if not logged in
    EXPECT_FALSE(manager.editBio(bio3)); //-- Cannot edit profile if not logged in
    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_EQ(email1, manager.getCurrentUser()->getEmail());
    ASSERT_EQ(password1, manager.getCurrentUser()->getPassword());
    ASSERT_EQ(name1, manager.getCurrentUser()->getUsername());
    ASSERT_EQ(bio1, manager.getCurrentUser()->getBio());

    EXPECT_TRUE(manager.editEmail(email3));
    EXPECT_EQ(email3, manager.getCurrentUser()->getEmail());
    EXPECT_EQ(password1, manager.getCurrentUser()->getPassword());
    EXPECT_EQ(name1, manager.getCurrentUser()->getUsername());
    EXPECT_EQ(bio1, manager.getCurrentUser()->getBio());

    ASSERT_TRUE(manager.editPassword(password3));
    EXPECT_EQ(email3, manager.getCurrentUser()->getEmail());
    EXPECT_EQ(password3, manager.getCurrentUser()->getPassword());
    EXPECT_EQ(name1, manager.getCurrentUser()->getUsername());
    EXPECT_EQ(bio1, manager.getCurrentUser()->getBio());

    ASSERT_TRUE(manager.editUsername(name3));
    EXPECT_EQ(email3, manager.getCurrentUser()->getEmail());
    EXPECT_EQ(password3, manager.getCurrentUser()->getPassword());
    EXPECT_EQ(name3, manager.getCurrentUser()->getUsername());
    EXPECT_EQ(bio1, manager.getCurrentUser()->getBio());

    ASSERT_TRUE(manager.editBio(bio3));
    EXPECT_EQ(email3, manager.getCurrentUser()->getEmail());
    EXPECT_EQ(password3, manager.getCurrentUser()->getPassword());
    EXPECT_EQ(name3, manager.getCurrentUser()->getUsername());
    EXPECT_EQ(bio3, manager.getCurrentUser()->getBio());

    ASSERT_FALSE(manager.editEmail(email2)); //-- cannot duplicate an existing email
    EXPECT_EQ(email3, manager.getCurrentUser()->getEmail());
    ASSERT_FALSE(manager.editUsername(name2)); //-- cannot duplicate an existing username
    EXPECT_EQ(name3, manager.getCurrentUser()->getUsername());


}


TEST_F(TestBarkerManagerBasic, ManagerLoggedUserCanFollowOtherUsers)
{
    Manager manager;
    ASSERT_TRUE(manager.createUser(email1, password1, name1, bio1));
    ASSERT_TRUE(manager.createUser(email2, password2, name2, bio2));
    ASSERT_TRUE(manager.createUser(email3, password3, name3, bio3));
    ASSERT_FALSE(manager.followUser(name2));  //-- error if trying to follow but not logged in
    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.followUser(name2));
    EXPECT_EQ(1, manager.getCurrentUser()->getFollowing().size());
    EXPECT_EQ(0, manager.showUser(name2)->getFollowing().size());
    EXPECT_EQ(0, manager.showUser(name3)->getFollowing().size());
    EXPECT_EQ(0, manager.getCurrentUser()->getFollowers());
    EXPECT_EQ(1, manager.showUser(name2)->getFollowers());
    EXPECT_EQ(0, manager.showUser(name3)->getFollowers());

    ASSERT_TRUE(manager.followUser(name3));
    EXPECT_EQ(2, manager.getCurrentUser()->getFollowing().size());
    EXPECT_EQ(0, manager.showUser(name2)->getFollowing().size());
    EXPECT_EQ(0, manager.showUser(name3)->getFollowing().size());
    EXPECT_EQ(0, manager.getCurrentUser()->getFollowers());
    EXPECT_EQ(1, manager.showUser(name2)->getFollowers());
    EXPECT_EQ(1, manager.showUser(name3)->getFollowers());

    ASSERT_FALSE(manager.followUser(name2));  //-- error if trying to follow same user twice
    ASSERT_FALSE(manager.followUser("FakeUser")); //-- error if following a non-existing user
    ASSERT_FALSE(manager.followUser(name1)); //-- error if user is trying to follow himself
}

TEST_F(TestBarkerManagerBasic, ManagerLoggedUserCanUnfollow)
{
    Manager manager;
    ASSERT_TRUE(manager.createUser(email1, password1, name1, bio1));
    ASSERT_TRUE(manager.createUser(email2, password2, name2, bio2));
    ASSERT_TRUE(manager.createUser(email3, password3, name3, bio3));
    ASSERT_FALSE(manager.unfollowUser(name3));  //-- error if trying to unfollow but not logged in
    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.followUser(name2));
    ASSERT_TRUE(manager.followUser(name3));
    ASSERT_TRUE(manager.unfollowUser(name3));
    EXPECT_EQ(1, manager.getCurrentUser()->getFollowing().size());
    EXPECT_EQ(0, manager.showUser(name2)->getFollowing().size());
    EXPECT_EQ(0, manager.showUser(name3)->getFollowing().size());
    EXPECT_EQ(0, manager.getCurrentUser()->getFollowers());
    EXPECT_EQ(1, manager.showUser(name2)->getFollowers());
    EXPECT_EQ(0, manager.showUser(name3)->getFollowers());

    ASSERT_FALSE(manager.unfollowUser(name3));  //-- error if trying to unfollow same user twice
    ASSERT_FALSE(manager.unfollowUser("FakeUser")); //-- error if unfollowing a non-existing user
}
