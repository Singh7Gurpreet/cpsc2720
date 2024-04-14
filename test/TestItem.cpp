#include <vector>
#include <fstream>

#include "gtest/gtest.h"
#include "Character.h"
#include "Environment.h"
#include "MainPlayer.h"
#include "Item.h"
#include "Claws.h"
#include "Pipe.h"
#include "FlameItem.h"
#include "FlamePartItem.h"
#include "Oxygen.h"
#include "Note.h"
#include "Bandages.h"

TEST(BandagesItem, bandagesTest) {
    Item* bnd = new Bandages("Test", "Test2");
    Player *hero = new MainPlayer("Hero", nullptr, 100);
    EXPECT_EQ(bnd->getName(), "Test");
    EXPECT_EQ(bnd->getDescription(), "Test2");
    EXPECT_EQ(bnd->getUses(), 3);
    EXPECT_FALSE(bnd->action(hero, hero));
    hero->takeDamage(2);
    EXPECT_TRUE(bnd->action(hero, hero));
    delete bnd;
    delete hero;
}

TEST(ClawsItem, clawsTest) {
    Item* bnd = new Claws("Test", "Test2");
    Player *hero = new MainPlayer("Hero", nullptr, 100);
    EXPECT_EQ(bnd->getName(), "Test");
    EXPECT_EQ(bnd->getDescription(), "Test2");
    EXPECT_EQ(bnd->getUses(), 999);
    EXPECT_TRUE(bnd->action(hero, hero));
    delete bnd;
    delete hero;
}

TEST(FlameItem, flameItemTest) {
    Item* bnd = new FlameItem("Test", "Test2");
    Player *hero1 = new MainPlayer("Hero", nullptr, 100);
    EXPECT_EQ(bnd->getName(), "Test");
    EXPECT_EQ(bnd->getDescription(), "Test2");
    EXPECT_EQ(bnd->getUses(), 3);
    EXPECT_FALSE(bnd->action(hero1, hero1, std::cin));
    delete hero1;
}

TEST(FlameItem, flameItem2Test) {
    Item* bnd = new FlameItem("Test", "Test2");
    Environment *gr = new GeneralRoom("s", "ds");
    Player *hero1 = new MainPlayer("Hero", nullptr, 100);
    Player *h = new MainPlayer("Hero", gr, 100);
    EXPECT_EQ(bnd->getName(), "Test");
    EXPECT_EQ(bnd->getDescription(), "Test2");
    EXPECT_EQ(bnd->getUses(), 3);
    EXPECT_FALSE(bnd->action(hero1, hero1, std::cin));
    EXPECT_FALSE(bnd->action(hero1, h, std::cin));
    delete hero1;
}

TEST(FlamePartItem, flamePartItemTest) {
    Item* bnd = new FlamePartItem("Test", "Test2");
    Player *hero1 = new MainPlayer("Hero", nullptr, 100);
    EXPECT_EQ(bnd->getName(), "Test");
    EXPECT_EQ(bnd->getDescription(), "Test2");
    EXPECT_FALSE(bnd->action(hero1, hero1));
    delete bnd;
    delete hero1;
}

TEST(NotesItem, notesTest) {
    Item* bnd = new Note("Test", "Test2");
    Player *hero = new MainPlayer("Hero", nullptr, 100);
    EXPECT_EQ(bnd->getName(), "Test");
    EXPECT_EQ(bnd->getDescription(), "Test2");
    EXPECT_EQ(bnd->getUses(), 999);
    EXPECT_FALSE(bnd->action(hero, hero));
    delete bnd;
    delete hero;
}

TEST(OxygenItem, oxygenTest) {
    Item* bnd = new Oxygen("Test", "Test2");
    Player *hero = new MainPlayer("Hero", nullptr, 100);
    EXPECT_EQ(bnd->getName(), "Test");
    EXPECT_EQ(bnd->getDescription(), "Test2");
    EXPECT_EQ(bnd->getUses(), 1);
    EXPECT_TRUE(bnd->action(hero, hero));
    delete bnd;
    delete hero;
}

TEST(PipeItem, wrongPipeTest) {
    Item* bnd = new Pipe("Test", "Test2");
    Environment *p1 = new GeneralRoom("Sad", "very");
    Environment *p2 = new GeneralRoom("2", "2");
    p1->addRoute(p2);
    Player *hero = new MainPlayer("Hero", p1, 100);
    EXPECT_EQ(bnd->getName(), "Test");
    EXPECT_EQ(bnd->getDescription(), "Test2");
    EXPECT_EQ(bnd->getUses(), 1);
    std::ifstream fin;
    fin.open("test/data/wrongInputForPipeTest.txt");
    EXPECT_FALSE(bnd->action(hero, hero, fin));
    delete bnd;
    delete hero;
    fin.close();
}

TEST(PipeItem, correctPipeTest) {
    Item* bnd = new Pipe("Test", "Test2");
    Environment *p1 = new GeneralRoom("Sad", "very");
    Environment *p2 = new GeneralRoom("2", "2");
    p1->addRoute(p2);
    Player *hero = new MainPlayer("Hero", p1, 100);
    EXPECT_EQ(bnd->getName(), "Test");
    EXPECT_EQ(bnd->getDescription(), "Test2");
    EXPECT_EQ(bnd->getUses(), 1);
    std::ifstream fin;
    fin.open("test/data/correctInputForPipeTest.txt");
    EXPECT_FALSE(bnd->action(hero, hero, fin));
    delete bnd;
    delete hero;
    fin.close();
}

