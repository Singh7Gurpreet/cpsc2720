#include <fstream>

#include "gtest/gtest.h"
#include "Environment.h"
#include "Inventory.h"
#include "Claws.h"
#include "Character.h"
#include "Opponent.h"
#include "GameManager.h"

TEST(GameManger, constructionTest) {
    EXPECT_NO_THROW(GameManager());
}

TEST(GameManager, gameSetupTest) {
    GameManager* GM = new GameManager();
    EXPECT_NO_THROW(GM->gameSetup());
    EXPECT_NO_THROW(GM->countDownUpdate());
    EXPECT_NO_THROW(GM->startMsg());
    EXPECT_FALSE(GM->winLossCheck());
    EXPECT_EQ(GM->getUser()->getName(), "Ripley");
    EXPECT_EQ(GM->getAlien()->getName(), "XenoMorph");
}

TEST(GameManager, giveQuestItemTest) {
    GameManager* GM = new GameManager();
    GM->gameSetup();
    EXPECT_NO_THROW(GM->giveQuestItem(GM->getUser()));
}

TEST(GameManager, warningMsgsTest) {
    GameManager* GM = new GameManager();
    std::ifstream fin;
    fin.open("test/data/inputForWarningMsg.txt");
    GM->gameSetup();
    EXPECT_NO_THROW(GM->warningMsg(fin));
}

