#include <gtest/gtest.h>
#include <time.h>
#include "../User.hpp"
#include "../Publication.hpp"
#include "../Bark.hpp"
#include "../Rebark.hpp"
#include "../Reply.hpp"


// The fixture for testing class Foo.
class TestBarkerPublication : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  TestBarkerPublication() {
     // You can do set-up work for each test here.

    //-- Test data
    id1 = 0;
    id2 = 1;
    id3 = 2;

    /*time(&t1);
    time(&t2);
    time(&t3);*/
    t1 = 1;
    t2 = 20;
    t3 = 300;

    text1 = "This is my first bark. Hello, world!";
    text2 = "This guy is hilarious";
    text3 = "You don't have a clue of what you're saying";

    //-- Define test users
    email1 = "email@domain.com";
    password1 = "1234";
    name1 = "coolGuy98";
    bio1 = "I'm just a random guy living my life";
    user = new User(email1, password1, name1, bio1);
    puser = (PublicUserData *)user;

    email2 = "otheremail@domain.com";
    password2 = "user2pass";
    name2 = "user2";
    bio2 = "Second user of Barker";
    user2 = new User(email2, password2, name2, bio2);
    puser2 = (PublicUserData *)user2;

    //-- Define expected output texts
    // bark format -> "{username} - {timestamp}:\n{text}"
    bark_text = "coolGuy98 - 1:\nThis is my first bark. Hello, world!";

    // rebark format -> "{username} rebarked - {timestamp}:\n{text}\n***\n{original bark}\n***"
    rebark_text = "user2 rebarked - 20:\nThis guy is hilarious\n***\n" + bark_text + "\n***";

    // reply format -> "{username} replied - {timestamp}:\n===\n{original bark}\n==="\n{text}"
    reply_text = "user2 replied - 300:\n===\n" + bark_text + "\n===\nYou don't have a clue of what you're saying";
  }

  ~TestBarkerPublication() override {
     // You can do clean-up work that doesn't throw exceptions here.
      delete user;
      user = nullptr;

      delete user2;
      user2 = nullptr;

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
  std::string text1, text2, text3;
  std::string bark_text, rebark_text, reply_text;
  std::string email1, password1, name1, bio1;
  std::string email2, password2, name2, bio2;
  User * user, *user2;
  PublicUserData * puser, *puser2;

  //Publication* publication1, publication2, publication3;
};

TEST_F(TestBarkerPublication, CanCreateBark)
{
    Bark bark(id1, t1, puser, text1);
    EXPECT_EQ(id1, bark.getId());
    EXPECT_EQ(t1, bark.getTime());
    EXPECT_EQ(puser, bark.getUser());
    EXPECT_EQ(text1, bark.getText());

    Publication* publication1 = (Publication*)&bark;
    EXPECT_EQ(id1, publication1->getId());
    EXPECT_EQ(t1, publication1->getTime());
    EXPECT_EQ(puser, publication1->getUser());
    EXPECT_EQ(bark_text, publication1->getBark());
}

TEST_F(TestBarkerPublication, CanCreateRebark)
{
    Bark bark(id1, t1, puser, text1);
    Rebark rebark(id2, t2, &bark, puser2, text2);
    EXPECT_EQ(id2, rebark.getId());
    EXPECT_EQ(t2, rebark.getTime());
    EXPECT_EQ(&bark, rebark.getPublication());
    EXPECT_EQ(puser2, rebark.getUser());
    EXPECT_EQ(text2, rebark.getText());

    Publication* publication1 = (Publication*)&rebark;
    EXPECT_EQ(id2, publication1->getId());
    EXPECT_EQ(t2, publication1->getTime());
    EXPECT_EQ(puser2, publication1->getUser());
    EXPECT_EQ(rebark_text, publication1->getBark());
}

TEST_F(TestBarkerPublication, CanCreateReply)
{
    Bark bark(id1, t1, puser, text1);
    Reply reply(id3, t3, &bark, puser2, text3);
    EXPECT_EQ(id3, reply.getId());
    EXPECT_EQ(t3, reply.getTime());
    EXPECT_EQ(&bark, reply.getPublication());
    EXPECT_EQ(puser2, reply.getUser());
    EXPECT_EQ(text3, reply.getText());

    Publication* publication1 = (Publication*)&reply;
    EXPECT_EQ(id3, publication1->getId());
    EXPECT_EQ(t3, publication1->getTime());
    EXPECT_EQ(puser2, publication1->getUser());
    EXPECT_EQ(reply_text, publication1->getBark());
}
