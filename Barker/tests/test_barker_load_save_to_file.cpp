#include <gtest/gtest.h>
#include <time.h>
#include "../User.hpp"
#include "../Manager.hpp"
#include "../Publication.hpp"
#include "../Bark.hpp"
#include "../Rebark.hpp"
#include "../Reply.hpp"
#include <fstream>
#include <sstream>

::testing::AssertionResult IsUserInFile(User user, std::string filename)
{
    //-- Open file
    std::ifstream file(filename);
    if (!file.is_open() || !file.good())
        return ::testing::AssertionFailure() << "Could not open file: " << filename;

    bool found = false;
    while (!found && !file.eof())
    {
        std::string line;
        std::getline(file, line);
        if (line == "#")
        {
            //-- Read data
            std::string email, password, name, bio;
            int followers = -1;
            std::vector<std::string> following;
            std::vector<int> publications;
            std::getline(file, email);
            std::getline(file, password);
            std::getline(file, name);
            std::getline(file, bio);
            file >> followers;
            std::getline(file, line); //-- "following" header is discarded
            bool end = false;
            while(!end)
            {
                std::getline(file, line);
                if (line == "publications:")
                    end = true;
                else
                    following.push_back(line);
            }
            end = false;
            while(!end)
            {
                std::getline(file, line);
                if (line == "#" || line == "$")
                    end = true;
                else
                {
                    std::stringstream ss;
                    int id;
                    ss << line;
                    ss >> id;
                    publications.push_back(id);
                }
            }

            //-- Check data
            if (email == user.getEmail() &&
                password == user.getPassword() &&
                name == user.getUsername() &&
                bio == user.getBio() &&
                followers == user.getFollowers())
            {
                //-- Following
                if (user.getFollowing().size() > 0)
                {
                    bool following_found = false;
                    for (int i = 0; i < user.getFollowing().size(); i++)
                    {
                        for (int j = 0; j < following.size(); j++)
                        {
                            if (user.getFollowing()[i]->getUsername() == following[j])
                                following_found = true;
                        }

                        if (!following_found)
                            break;
                    }
                    if (!following_found)
                        continue;
                }

                if (user.getPublications().size() > 0)
                {
                bool publication_found = false;
                for (int i = 0; i < user.getPublications().size(); i++)
                {
                    for (int j = 0; j < publications.size(); j++)
                    {
                        if (user.getPublications()[i]->getId() == publications[j])
                            publication_found = true;
                    }

                    if (!publication_found)
                        break;
                }
                if (!publication_found)
                    continue;
                }
                found = true;
            }
        }
    }

    file.close();
    if (found)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << "User: " << user.getUsername() << " not in file.";
}

::testing::AssertionResult IsPublicationInFile(Publication* publication, std::string filename)
{
    //-- Open file
    std::ifstream file(filename);
    if (!file.is_open() || !file.good())
        return ::testing::AssertionFailure() << "Could not open file: " << filename;

    //-- Detect type of publication and cast to type
    std::string keyword;
    Bark * bark =  dynamic_cast<Bark*>(publication);
    if (bark)
        keyword = "$Bark";
    Rebark * rebark =  dynamic_cast<Rebark*>(publication);
    if (rebark)
        keyword = "$Rebark";
    Reply * reply =  dynamic_cast<Reply*>(publication);
    if (reply)
        keyword = "$Reply";

    //-- Look for correct keyword
    bool found = false;
    while (!found && !file.eof())
    {
        std::string line;
        std::getline(file, line);
        if (line == keyword)
        {
            //-- Read data
            int id, pub_id;
            unsigned long time = 1;
            std::string name, text;
            std::stringstream ss;

            std::getline(file, line);
            ss << line;
            ss >> id;
            ss.clear();
            std::getline(file, line);
            ss << line;
            ss >> time;
            ss.clear();
            if (keyword == "$Rebark" || keyword == "$Reply")
            {
                std::getline(file, line);
                ss << line;
                ss >> pub_id;
                ss.clear();
            }
            std::getline(file, name);
            std::getline(file, text);

            //-- Check data
            if (id == publication->getId() &&
                time == publication->getTime() &&  //-- This should be uncommented
                name == publication->getUser()->getUsername())
            {
                if (keyword == "$Bark")
                {
                    if (text== bark->getText())
                        found = true;
                }
                else if (keyword == "$Rebark")
                {
                    if (text == rebark->getText() && pub_id == rebark->getPublication()->getId())
                        found = true;
                }
                else if (keyword == "$Reply")
                {
                    if (text == reply->getText() && pub_id == reply->getPublication()->getId())
                        found = true;
                }

            }
        }
    }

    file.close();
    if (found)
        return ::testing::AssertionSuccess();
    else
    {
        if (keyword == "$Bark")
            return ::testing::AssertionFailure() << "Bark with id: " << publication->getId() << " not in file.";
        else if (keyword == "$Rebark")
            return ::testing::AssertionFailure() << "Rebark with id: " << publication->getId() << " not in file.";
        else if (keyword == "$Reply")
            return ::testing::AssertionFailure() << "Reply with id: " << publication->getId() << " not in file.";
        else
            return ::testing::AssertionFailure() << "Publication not in file.";
    }
}

::testing::AssertionResult IsBarkInVector(Bark bark, std::vector<Publication *> v)
{
    bool found = false;
    int i = 0;
    while (!found && i < v.size() )
    {
        Bark * b = dynamic_cast<Bark*>(v[i]);
        if (b != nullptr)
            if ( b->getId() == bark.getId() &&
                 b->getTime() == bark.getTime() &&
                 b->getUser()->getUsername() == bark.getUser()->getUsername() &&
                 b->getText() == bark.getText())
                         found = true;
        i++;
    }

    if (found)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << "Bark with text: " << bark.getText() << " not in publications vector.";
}


::testing::AssertionResult IsRebarkInVector(Rebark rebark, std::vector<Publication *> v)
{
    bool found = false;
    int i = 0;
    while (!found && i < v.size() )
    {
        Rebark * b = dynamic_cast<Rebark*>(v[i]);
        if (b != nullptr)
            if ( b->getId() == rebark.getId() &&
                 b->getTime() == rebark.getTime() &&
                 b->getUser()->getUsername() == rebark.getUser()->getUsername() &&
                 b->getPublication()->getId() == rebark.getPublication()->getId() &&
                 b->getText() == rebark.getText())
                         found = true;
        i++;
    }

    if (found)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << "Rebark with text: " << rebark.getText() << "  of publication with id: " << rebark.getPublication()->getId() << " not in publications vector.";
}

::testing::AssertionResult IsReplyInVector(Reply reply, std::vector<Publication *> v)
{
    bool found = false;
    int i = 0;
    while (!found && i < v.size() )
    {
        Reply * b = dynamic_cast<Reply*>(v[i]);
        if (b != nullptr)
            if ( b->getId() == reply.getId() &&
                 b->getTime() == reply.getTime() &&
                 b->getUser()->getUsername() == reply.getUser()->getUsername() &&
                 b->getPublication()->getId() == reply.getPublication()->getId() &&
                 b->getText() == reply.getText())
                         found = true;
        i++;
    }

    if (found)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << "Reply with text: " << reply.getText() << "  to publication with id: " << reply.getPublication()->getId() << " not in publications vector.";
}


class TestBarkerLoadSaveToFile : public ::testing::Test {
 protected:

  TestBarkerLoadSaveToFile()
  {
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

    email2 = "otheremail@domain.com";
    password2 = "user2pass";
    name2 = "user2";
    bio2 = "Second user of Barker";

    email3 = "fakeemail@domain.com";
    password3 = "user3pass";
    name3 = "user3";
    bio3 = "Third user of Barker";
  }


  int id1, id2, id3;
  time_t t1, t2, t3;
  std::string text1, text2, text3, text4, text5;
  std::string bark_text, rebark_text, reply_text;
  std::string email1, password1, name1, bio1;
  std::string email2, password2, name2, bio2;
  std::string email3, password3, name3, bio3;
};

TEST_F(TestBarkerLoadSaveToFile, ManagerCanSaveState)
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

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_TRUE(manager.createRebark(id, text2));
    ASSERT_TRUE(manager.createBark(text4));
    ASSERT_TRUE(manager.followUser(name1));
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email3, password3));
    ASSERT_TRUE(manager.createBark(text5));
    ASSERT_TRUE(manager.createReply(id, text3));
    ASSERT_TRUE(manager.followUser(name1));
    ASSERT_TRUE(manager.followUser(name2));
    ASSERT_TRUE(manager.logout());

    manager.saveToFile("test_file.txt");
    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(IsUserInFile(*manager.getCurrentUser(), "test_file.txt"));
    pubs = manager.getCurrentUser()->getPublications();
    for (int i = 0; i < pubs.size(); i++)
        ASSERT_TRUE(IsPublicationInFile(pubs[i], "test_file.txt"));
    ASSERT_TRUE(manager.logout());
    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_TRUE(IsUserInFile(*manager.getCurrentUser(), "test_file.txt"));
    pubs = manager.getCurrentUser()->getPublications();
    for (int i = 0; i < pubs.size(); i++)
        ASSERT_TRUE(IsPublicationInFile(pubs[i], "test_file.txt"));
    ASSERT_TRUE(manager.logout());
    ASSERT_TRUE(manager.login(email3, password3));
    ASSERT_TRUE(IsUserInFile(*manager.getCurrentUser(), "test_file.txt"));
    pubs = manager.getCurrentUser()->getPublications();
    for (int i = 0; i < pubs.size(); i++)
        ASSERT_TRUE(IsPublicationInFile(pubs[i], "test_file.txt"));
    ASSERT_TRUE(manager.logout());
}

TEST_F(TestBarkerLoadSaveToFile, ManagerCanLoadState)
{
    Manager manager;
    ASSERT_TRUE(manager.loadFromFile("test_data.dat"));

    //-- Assemble data by hand:
    User test_user1(name1, password1, name1, bio1);
    User test_user2(name2, password2, name2, bio2);
    User test_user3(name3, password3, name3, bio3);

    test_user2.follow(&test_user1);
    test_user1.increaseFollowers();
    test_user3.follow(&test_user1);
    test_user1.increaseFollowers();
    test_user3.follow(&test_user2);
    test_user2.increaseFollowers();

    Bark bark1(0, 0, (PublicUserData*)&test_user1, text1);
    test_user1.addPublication(&bark1);
    Rebark bark2(1, 20, &bark1, (PublicUserData*)&test_user2, text2);
    Bark bark3(2, 40, (PublicUserData*)&test_user2, text4);
    test_user2.addPublication(&bark2);
    test_user2.addPublication(&bark3);
    Bark bark4(3, 60, (PublicUserData*)&test_user3, text5);
    Reply bark5(4, 80, &bark1, (PublicUserData*)&test_user3, text3);
    test_user3.addPublication(&bark4);
    test_user3.addPublication(&bark5);

    //-- Check users
    ASSERT_TRUE(manager.login(email1, password1));
    User* current = manager.getCurrentUser();
    EXPECT_EQ(email1, current->getEmail());
    EXPECT_EQ(password1, current->getPassword());
    EXPECT_EQ(name1, current->getUsername());
    EXPECT_EQ(bio1, current->getBio());
    EXPECT_EQ(2, current->getFollowers());
    EXPECT_EQ(0, current->getFollowing().size());

    std::vector<Publication*> pubs = manager.getCurrentUser()->getPublications();
    ASSERT_EQ(1, pubs.size());
    EXPECT_TRUE(IsBarkInVector(bark1, pubs));

    ASSERT_TRUE(manager.logout());


    ASSERT_TRUE(manager.login(email2, password2));
    current = manager.getCurrentUser();
    EXPECT_EQ(email2, current->getEmail());
    EXPECT_EQ(password2, current->getPassword());
    EXPECT_EQ(name2, current->getUsername());
    EXPECT_EQ(bio2, current->getBio());
    EXPECT_EQ(1, current->getFollowers());
    EXPECT_EQ(1, current->getFollowing().size());

    pubs = manager.getCurrentUser()->getPublications();
    ASSERT_EQ(2, pubs.size());
    EXPECT_TRUE(IsRebarkInVector(bark2, pubs));
    EXPECT_TRUE(IsBarkInVector(bark3, pubs));

    ASSERT_TRUE(manager.logout());


    ASSERT_TRUE(manager.login(email3, password3));
    current = manager.getCurrentUser();
    EXPECT_EQ(email3, current->getEmail());
    EXPECT_EQ(password3, current->getPassword());
    EXPECT_EQ(name3, current->getUsername());
    EXPECT_EQ(bio3, current->getBio());
    EXPECT_EQ(0, current->getFollowers());
    EXPECT_EQ(2, current->getFollowing().size());

    pubs = manager.getCurrentUser()->getPublications();
    ASSERT_EQ(2, pubs.size());
    for (int i = 0; i < pubs.size(); i++)
        std::cout << pubs[i]->getTime() << std::endl;
    EXPECT_TRUE(IsBarkInVector(bark4, pubs));
    EXPECT_TRUE(IsReplyInVector(bark5, pubs));

    ASSERT_TRUE(manager.logout());
}
