#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "gtest/gtest.h"

#include "Item.h"
#include "Character.h"
#include "MainPlayer.h"
#include "Pipe.h"
#include "Claws.h"

TEST(NPCPlayer, setterGetters) {
    NPC* newNPC = new NPC("test", "beans", "Hi");
    newNPC->setHint("Hint");
    EXPECT_EQ(newNPC->getHint(), "Hint");
    EXPECT_EQ(newNPC->getPrompt(), "Hi");
}

TEST(MainPlayer, helpTest) {
    Player *p1 = new MainPlayer("Hero", nullptr, 100);
    EXPECT_TRUE(p1->helpAction());
}

TEST(MainPlayer, movePlayerTest) {
    Environment *npc = new GeneralRoom("General Room", "");
    Environment *pr = new PuzzleRoom("Puzzle Room", "");
    Environment *hr = new HazardRoom("Hazard Room", "");
    Player *p1 = new MainPlayer("Hero", hr, 100);
    hr->setRoutes({npc});
    hr->addRoute(pr);
    hr->addRoute(hr);
    std::ifstream fin;
    fin.open("test/data/moveData.txt");
    p1->move(fin);
    fin.close();
    // delete static_cast<MainPlayer*>(p1);
}

TEST(MainPlayer, spwanLocationTest) {
    Player *p1 = new MainPlayer("Hero", nullptr, 100);
    p1->move(std::cin);
    // EXPECT_EQ(static_cast<MainPlayer*>(p1)->help(),"Somewhere");
    delete p1;
}

TEST(MainPlayer, descriptionTest) {
    Character* p1 = new MainPlayer("Hero", nullptr, 100);
    p1->setDescription("I am king of this world\n");
    EXPECT_EQ(p1->getDescription(), "I am king of this world\n");
    EXPECT_EQ(p1->getName(), "Hero");
    delete static_cast<MainPlayer*>(p1);
}

TEST(MainPlayer, inventoryOperationsTest) {
    Character* p1 = new MainPlayer("Hero", nullptr, 100);
    Item *i1 = new Pipe("Sword", "I am gonna kill them");
    p1->addItem(i1);
    //EXPECT_EQ(p1->hasItem(i1), true);
    p1->removeItem(i1);
    //EXPECT_EQ(p1->hasItem(i1), false); To fix if time
    delete i1;
    delete static_cast<MainPlayer*>(p1);
}

TEST(MainPlayer, interactWithTest) {
    Environment *hr = new HazardRoom("ASd", "SA");
    MainPlayer *p1 = new MainPlayer("Hero", hr, 100);
    EXPECT_NO_THROW(p1->interact());
    delete p1;
}

TEST(MainPlayer, HPTest) {
    Player* p1 = new MainPlayer("Hero", nullptr, 100);
    EXPECT_EQ(p1->getHP(), 100);
    EXPECT_EQ(p1->takeDamage(80), true);
    EXPECT_EQ(p1->takeDamage(-10), false);
    delete p1;
}

TEST(MainPlayer, itemsSearchTest) {
    Environment *npc = new GeneralRoom("General Room", "");
    Character* p1 = new MainPlayer("Hero", npc, 100);
    Inventory *i1 = new Inventory();
    Item *item = new Pipe("Sword", "Kill em with sword");
    i1->addItem(item);
    npc->setInventory(i1);
    static_cast<MainPlayer*>(p1)->search();
    i1->rmItem(item);
    static_cast<MainPlayer*>(p1)->search();
    static_cast<MainPlayer*>(p1)->statDisplay();
    delete static_cast<MainPlayer*>(p1);
}
TEST(MainPlayer, oxygenManipulatorFunctionsTest) {
    MainPlayer *mp = new MainPlayer("Hero", nullptr, 100);
    mp->setOxygen(10);
    EXPECT_EQ(mp->getOxygen(), 10);
    mp->reduceOxygen();
    EXPECT_EQ(mp->getOxygen(), 5);
    delete mp;
}

TEST(MainPlayer, useItemTest) {
    MainPlayer *mp = new MainPlayer("Hero", nullptr, 100);
    std::ifstream in;
    in.open("test/data/wrongInputsUseItem.txt");
    EXPECT_FALSE(mp->useItem(in, mp));
    //Inventory *m1 = new Inventory();
    Item* p = new Claws("hel", "sdd");
    p->setUses(0);
    mp->addItem(p);
    //EXPECT_TRUE(mp->useItem(in, mp));
    //EXPECT_FALSE(mp->useItem(in, mp));
    //delete mp;
    //delete p;
    //delete m1;
}

TEST(MainPlayer, actionSelectTest) {
    Environment *p = new GeneralRoom("afas", "SAs");
    MainPlayer *mp = new MainPlayer("Hero", p, 100);
    std::ifstream fin;
    fin.open("test/data/interactionDataTest.txt");
    EXPECT_NO_THROW(mp->actionSelect(fin, mp));
    // delete mp;
}

TEST(MainPlayer, attemptTradeTest) {
    Character* p1 = new MainPlayer("Hello", nullptr, 1000);
    NPC *trader = new NPC("2", "2", "2");

    Item* item1 = new Claws("1", "1");
    Inventory *bag1 = new Inventory();
    bag1->addItem(item1);

    Item* item2 = new Claws("2", "2");
    Inventory *bag2 = new Inventory();
    bag2->addItem(item2);

    trader->setBag(*bag1);
    p1->setBag(*bag2);
    EXPECT_FALSE(p1->hasItem(item2));
    trader->attemptTrade(static_cast<Player*>(p1));
    trader->attemptTrade(static_cast<Player*>(p1));
}
