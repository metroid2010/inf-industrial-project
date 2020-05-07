#include <gtest/gtest.h>
#include <time.h>
#include "../User.hpp"
#include "../Manager.hpp"
#include "../Publication.hpp"
#include "../Bark.hpp"
#include "../Rebark.hpp"
#include "../Reply.hpp"

::testing::AssertionResult IsBarkInVector(std::string text, std::vector<Publication *> v)
{
    bool found = false;
    int i = 0;
    while (!found && i < v.size() )
    {
        Bark * b = dynamic_cast<Bark*>(v[i]);
        if (b != nullptr && b->getText() == text)
            found = true;
        i++;
    }

    if (found)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << "Bark with text: " << text << " not in publications vector.";
}

::testing::AssertionResult IsRebarkInVector(int id, std::string text, std::vector<Publication *> v)
{
    bool found = false;
    int i = 0;
    while (!found && i < v.size() )
    {
        Rebark * b = dynamic_cast<Rebark*>(v[i]);
        if (b != nullptr)
            if (b->getPublication()->getId() == id && b->getText() == text)
                found = true;
        i++;
    }

    if (found)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << "Rebark with text: " << text << "  of publication with id: " << id << " not in publications vector.";
}

::testing::AssertionResult IsReplyInVector(int id, std::string text, std::vector<Publication *> v)
{
    bool found = false;
    int i = 0;
    while (!found && i < v.size() )
    {
        Reply * b = dynamic_cast<Reply*>(v[i]);
        if (b != nullptr)
            if (b->getPublication()->getId()  == id  && b->getText() == text)
            found = true;
        i++;
    }

    if (found)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << "Reply with text: " << text << " to publication with id: " << id << " not in publications vector.";
}


// The fixture for testing class Foo.
class TestBarkerPublicationIntegration : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  TestBarkerPublicationIntegration() {
     // You can do set-up work for each test here.
    //-- Test data
    id1 = 0;
    id2 = 1;
    id3 = 2;

    t1 = 1;
    t2 = 20;
    t3 = 300;

    text1 = "This is my first bark. Hello, world!";
    text2 = "This guy is hilarious";
    text3 = "You don't have a clue of what you're saying";
    text4 = "It's difficult to come up with a cool bark";
    text5 = "Hey yo!";

    //-- Define test users
    email1 = "email@domain.com";
    password1 = "1234";
    name1 = "coolGuy98";
    bio1 = "I'm just a random guy living my life";
    user = new User(email1, password1, name1, bio1);

    email2 = "otheremail@domain.com";
    password2 = "user2pass";
    name2 = "user2";
    bio2 = "Second user of Barker";
    user2 = new User(email2, password2, name2, bio2);

    email3 = "fakeemail@domain.com";
    password3 = "user3pass";
    name3 = "user3";
    bio3 = "Third user of Barker";
    user3 = new User(email3, password3, name3, bio3);

    //-- Define expected output texts
    // bark format -> "{username} - {timestamp}:\n{text}"
    bark_text = "coolGuy98 - 1:\nThis is my first bark. Hello, world!";

    // rebark format -> "{username} rebarked - {timestamp}:\n{text}\n***\n{original bark}\n***"
    rebark_text = "user2 rebarked - 20:\nThis guy is hilarious\n***\n" + bark_text + "\n***";

    // reply format -> "{username} replied - {timestamp}:\n===\n{original bark}\n==="\n{text}
    reply_text = "user2 replied - 300:\n===\n" + bark_text + "\n===\nYou don't have a clue of what you're saying";
  }

  ~TestBarkerPublicationIntegration() override {
     // You can do clean-up work that doesn't throw exceptions here.
      delete user;
      user = nullptr;

      delete user2;
      user2 = nullptr;

      delete user3;
      user3 = nullptr;
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).

  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
      /*if (publication1)
      {
          delete publication1;
          publication1 = nullptr;
      }

      if (publication2)
      {
          delete publication2;
          publication2 = nullptr;
      }

      if (publication3)
      {
          delete publication3;
          publication3 = nullptr;
      }*/
  }

  int id1, id2, id3;
  time_t t1, t2, t3;
  std::string text1, text2, text3, text4, text5;
  std::string bark_text, rebark_text, reply_text;
  std::string email1, password1, name1, bio1;
  std::string email2, password2, name2, bio2;
  std::string email3, password3, name3, bio3;

  User * user, *user2, *user3;

  //Publication* publication1, publication2, publication3;
};

TEST_F(TestBarkerPublicationIntegration, UserCanHavePublications)
{
    Bark bark(id1, t1, user, text1);
    ASSERT_TRUE(user->addPublication(&bark));

    std::vector<Publication*> publications = user->getPublications();
    ASSERT_EQ(1, publications.size());
    EXPECT_EQ(id1, publications[0]->getId());
    EXPECT_EQ(t1, publications[0]->getTime());
    EXPECT_EQ(user, publications[0]->getUser());
    EXPECT_EQ(bark_text, publications[0]->getBark());
}

TEST_F(TestBarkerPublicationIntegration, UserCannotOwnPublicationsFromOthers)
{
    Bark bark(id1, t1, user2, text1);
    ASSERT_FALSE(user->addPublication(&bark));
    ASSERT_EQ(0, user->getPublications().size());

    Bark bark2(id1, t1, user, text1);
    ASSERT_TRUE(user->addPublication(&bark2));
    ASSERT_EQ(1, user->getPublications().size());
}

TEST_F(TestBarkerPublicationIntegration, UserCanRemovePublications)
{
    Bark bark(id1, t1, user, text1);
    Bark bark2(id2, t2, user, text2);

    ASSERT_TRUE(user->addPublication(&bark));
    ASSERT_TRUE(user->addPublication(&bark2));

    ASSERT_EQ(2, user->getPublications().size());

    ASSERT_TRUE(user->removePublication(id1));
    std::vector<Publication*> publications = user->getPublications();
    ASSERT_EQ(1, publications.size());
    EXPECT_EQ(id2, publications[0]->getId());
    EXPECT_EQ(t2, publications[0]->getTime());
    EXPECT_EQ(user, publications[0]->getUser());
}

TEST_F(TestBarkerPublicationIntegration, ManagerCanShowUserFeed)
{
    Manager manager;
    ASSERT_TRUE(manager.createUser(email1, password1, name1, bio1));
    ASSERT_FALSE(manager.createBark(text1)); //-- Cannot create publications if not logged in
    ASSERT_TRUE(manager.login(email1, password1));

    ASSERT_TRUE(manager.createBark(text1));
    ASSERT_TRUE(manager.createBark(text2));

    std::vector<Publication *> pubs = manager.getUserFeed(name1);
    ASSERT_EQ(2, pubs.size());
    ASSERT_TRUE(IsBarkInVector(text1, pubs));
    ASSERT_TRUE(IsBarkInVector(text2, pubs));
    ASSERT_FALSE(IsBarkInVector(text3, pubs));
}

TEST_F(TestBarkerPublicationIntegration, ManagerCanShowUserTimeline)
{
    Manager manager;
    ASSERT_TRUE(manager.createUser(email1, password1, name1, bio1));
    ASSERT_TRUE(manager.createUser(email2, password2, name2, bio2));
    ASSERT_TRUE(manager.createUser(email3, password3, name3, bio3));

    //-- Add content to users
    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.createBark(text1));
    std::vector<Publication *> pubs = manager.getCurrentUser()->getPublications();
    ASSERT_EQ(1, pubs.size());
    int id = pubs[0]->getId();
    ASSERT_TRUE(manager.logout());

    ASSERT_FALSE(manager.createRebark(id, text2)); //-- Need to be logged in
    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_TRUE(manager.createRebark(id, text2));
    ASSERT_TRUE(manager.createBark(text4));
    ASSERT_TRUE(manager.logout());

    ASSERT_FALSE(manager.createReply(id, text3)); //-- Need to be logged in
    ASSERT_TRUE(manager.login(email3, password3));
    ASSERT_TRUE(manager.createBark(text5));
    ASSERT_TRUE(manager.createReply(id, text3));
    ASSERT_TRUE(manager.logout());

    //-- Get timeline for user 1:
    ASSERT_TRUE(manager.login(email1, password1));
    std::vector<Publication *> timeline = manager.getTimeline();
    ASSERT_EQ(0, timeline.size());

    //-- Follow user 2 and get timeline for user 1:
    ASSERT_TRUE(manager.followUser(name2));
    timeline = manager.getTimeline();
    ASSERT_EQ(2, timeline.size());
    EXPECT_TRUE(IsBarkInVector(text4, timeline));
    EXPECT_TRUE(IsRebarkInVector(id, text2, timeline));

    //-- Follow user 3 and get timeline for user 1:
    ASSERT_TRUE(manager.followUser(name3));
    timeline = manager.getTimeline();
    EXPECT_TRUE(IsBarkInVector(text4, timeline));
    EXPECT_TRUE(IsBarkInVector(text5, timeline));
    EXPECT_TRUE(IsRebarkInVector(id, text2, timeline));
    EXPECT_TRUE(IsReplyInVector(id, text3, timeline));

    //-- Unfollow user 2 and get timeline for user 1:
    ASSERT_TRUE(manager.unfollowUser(name2));
    timeline = manager.getTimeline();
    EXPECT_TRUE(IsBarkInVector(text5, timeline));
    EXPECT_TRUE(IsReplyInVector(id, text3, timeline));
}

