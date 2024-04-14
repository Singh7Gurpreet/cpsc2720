#include <vector>
#include <fstream>

#include "gtest/gtest.h"
#include "Environment.h"
#include "Inventory.h"
#include "Claws.h"
#include "Character.h"
#include "Opponent.h"

TEST(OpponentTest, constructionTest) {
    EXPECT_NO_THROW(Opponent("sd", nullptr, 1000));
}

TEST(OpponentTest, useItemTest) {
    Player *p1 = new Opponent("alien", nullptr, 10);
    Inventory i;
    Item* claw = new Claws("sa", "Fds");
    i.addItem(claw);
    p1->setBag(i);
    EXPECT_TRUE(p1->useItem(std::cin, p1));
    delete p1;;
}

TEST(OpponentTest, moveTest) {
    Environment *gr1 = new GeneralRoom("sda", "sada");
    Environment *gr2 = new GeneralRoom("sda", "sada");
    gr1->addRoute(gr2);
    Player *p1 = new Opponent("alien", gr1, 10);
    p1->move(std::cin);
    EXPECT_NE(p1->getLocation(), gr1);
    p1->takeDamage(19);
    EXPECT_FALSE(p1->move(std::cin));
    delete p1;
}

TEST(OpponentTest, miscellaneousTest) {
    Player *p1 = new Opponent("dsf", nullptr, 10);
    EXPECT_NO_THROW(p1->statDisplay());
    EXPECT_FALSE(p1->helpAction());
    EXPECT_FALSE(p1->search());
    EXPECT_FALSE(p1->interact());
    EXPECT_NO_THROW(p1->actionSelect(std::cin, nullptr));
    EXPECT_NO_THROW(p1->getOxygen());
    EXPECT_NO_THROW(p1->reduceOxygen());
    EXPECT_NO_THROW(p1->setOxygen(12));
    delete p1;
}
