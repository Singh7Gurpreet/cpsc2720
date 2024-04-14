#include <vector>
#include <fstream>

#include "gtest/gtest.h"
#include "Environment.h"
#include "Inventory.h"
#include "Character.h"
#include "MainPlayer.h"
#include "Pipe.h"

TEST(EnvrionmentTest, TestGeneralRoomFunctions) {
    GeneralRoom *generalRoom = new GeneralRoom("", "General Room");
    EXPECT_EQ(generalRoom->getDescription(), "General Room");
    delete generalRoom;
}

TEST(Environment, TestGeneralRoomInteractWith) {
    GeneralRoom *generalRoom = new GeneralRoom("", "General Room");
    EXPECT_TRUE(generalRoom->interactWith(nullptr));
    delete generalRoom;
}

TEST(EnvrionmentTest, PuzzleRoomFunctions) {
    PuzzleRoom *puzzleRoom = new PuzzleRoom("", "Puzzle Room");
    EXPECT_EQ(puzzleRoom->getDescription(), "Puzzle Room");
    puzzleRoom->setPuzzle("What comes before you");
    puzzleRoom->setAnswer("t");
    EXPECT_EQ(puzzleRoom->getPuzzle(), "What comes before you");
    delete puzzleRoom;
}

TEST(EnvironmentTest, PuzzleRoomCorrectTest) {
    PuzzleRoom *puzzleRoom = new PuzzleRoom("", "Puzzle Room");
    EXPECT_EQ(puzzleRoom->getDescription(), "Puzzle Room");
    puzzleRoom->setPuzzle("What comes before you");
    puzzleRoom->setAnswer("t");
    EXPECT_EQ(puzzleRoom->getPuzzle(), "What comes before you");
    std::ifstream fin;
    fin.open("test/data/correctInputForPuzzle.txt");
    EXPECT_TRUE(puzzleRoom->interactWith(nullptr, fin));
    EXPECT_FALSE(puzzleRoom->interactWith(nullptr, fin));
    delete puzzleRoom;
    fin.close();
}

TEST(EnvironmentTest, PuzzleRoomWrongTest) {
    PuzzleRoom *puzzleRoom = new PuzzleRoom("", "Puzzle Room");
    EXPECT_EQ(puzzleRoom->getDescription(), "Puzzle Room");
    puzzleRoom->setPuzzle("What comes before you");
    puzzleRoom->setAnswer("t");
    EXPECT_EQ(puzzleRoom->getPuzzle(), "What comes before you");
    std::ifstream fin;
    fin.open("test/data/wrongInputForPuzzle.txt");
    EXPECT_TRUE(puzzleRoom->interactWith(nullptr, fin));
    delete puzzleRoom;
    fin.close();
}

TEST(EnvironmentTest, puzzleRoomRewardsTest) {
    PuzzleRoom *puzzleRoom = new PuzzleRoom("", "Puzzle Room");
    puzzleRoom->setRewardMsg("Here is it\n");
    Item *claws = new Pipe("hel", "dsf");
    puzzleRoom->setReward(claws);
    EXPECT_EQ(puzzleRoom->getReward(), claws);
    delete puzzleRoom;
    delete claws;
}

TEST(EnvrionmentTest, TestNpcRoomFunctions) {
    NpcRoom *npcRoom = new NpcRoom("", "NPC Room");
    EXPECT_EQ(npcRoom->getDescription(), "NPC Room");
    NPC* p = new NPC("sa", "wa", "fa");
    std::ifstream fin;
    fin.open("test/data/inputForNpcRoomFunction.txt");
    EXPECT_FALSE(npcRoom->interactWith(nullptr, fin));
    npcRoom->setNPC(p);
    EXPECT_EQ(npcRoom->getNPC(), p);
    EXPECT_TRUE(npcRoom->interactWith(nullptr, fin));
    // delete npcRoom;
    // delete p;
    fin.close();
}


TEST(EnvrionmentTest, TestHazardRoomFunctions) {
    HazardRoom *hazardRoom = new HazardRoom("abc", "Hazard Room");
    hazardRoom->setHazardDesc("helo");
    EXPECT_EQ(hazardRoom->getHazardDesc(), "helo");
    hazardRoom->setHazardDmg(10);
    EXPECT_EQ(hazardRoom->getHazardDmg(), 10);
    EXPECT_EQ(hazardRoom->getDescription(), "Hazard Room");
    EXPECT_EQ(hazardRoom->getHazardStatus(), true);
    hazardRoom->triggerHazard();
    EXPECT_EQ(hazardRoom->getHazardStatus(), true);
    hazardRoom->clearHazard();
    EXPECT_EQ(hazardRoom->getHazardStatus(), false);
    Player *p1 = new MainPlayer("132", nullptr, 100);
    hazardRoom->triggerHazard();
    EXPECT_TRUE(hazardRoom->interactWith(p1));
    delete hazardRoom;
    hazardRoom = nullptr;
    delete p1;
}

TEST(EnvrionmentTest, emptyRoutes) {
    Environment *gr = new GeneralRoom("", "General Room");
    EXPECT_NO_THROW(gr->setRoutes({}));
    delete gr;
}
/*
TEST(EnvironmentTest, InventoryTest) {
    Environment *gr = new GeneralRoom("", "General Room");
    Inventory *bag = new Inventory();
    Item* item = new Pipe("pipe", "test");
    gr->setInventory(bag);
    gr->addItem(item);
    bag = gr->getItemsInRoom();
    ASSERT_EQ(bag->getItem(0), item);
    delete gr;
}
*/
