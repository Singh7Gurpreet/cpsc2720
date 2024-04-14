#include <vector>
#include <fstream>

#include "gtest/gtest.h"
#include "Inventory.h"
#include "Item.h"
#include "Claws.h"
#include "Pipe.h"
#include "FlameItem.h"

TEST(TestInventoryClass, defaultConstructorTest) {
  EXPECT_NO_THROW(Inventory());
  EXPECT_FALSE(Inventory().isEmpty());
}

TEST(TestInventoryClass, oneParamConstructorTest) {
  Item * i1 = new Claws("Sword", "Kill em with sword");
  Item * i2 = new Pipe("Sword1", "Kill em with sword");
  Item * i3 = new FlameItem("Sword2", "Kill em with sword");
  EXPECT_NO_THROW(Inventory({i1, i2, i3}));
  delete i1;
  delete i2;
  delete i3;
  i1 = i2 = i3 = nullptr;
}

TEST(TestInventoryClass, hasItemTest) {
  Item * i1 = new Claws("Sword", "Kill em with sword");
  Item * i2 = new Pipe("Sword1", "Kill em with sword");
  Item * i3 = new FlameItem("Sword2", "Kill em with sword");
  Inventory *bag = new Inventory({i1, i3});
  EXPECT_FALSE(bag->hasItem(i2));
  EXPECT_FALSE(bag->hasItem(i2->getName()));
  EXPECT_TRUE(bag->hasItem(i1));
  EXPECT_TRUE(bag->hasItem(i1->getName()));
  delete i2;
  delete i1;
  delete i3;
  delete bag;
  i1 = i2 = i3 = nullptr;
  bag = nullptr;
}

TEST(TestInventoryClass, addItemTest) {
  //Test that its added properly
  Inventory *Base = new Inventory();
  Item* testItem = new Claws("Test", "Test");
  Base->addItem(testItem);
  delete Base;
  delete testItem;
  //Test list item
  //Test get item
  //Test etc
}

TEST(TestInventoryClass, rmItemTest) {
  //Ensure its added and then promptly destroyed
  Inventory Base;
  Item* testItem = new Claws("Test", "Test");
  Base.rmItem(testItem); // Item not present

  Base.addItem(testItem);//Item present
  EXPECT_TRUE(Base.hasItem(testItem));
  Base.rmItem(testItem);
  EXPECT_FALSE(Base.hasItem(testItem));
  delete testItem;
  testItem = nullptr;
  //Handles gracefully if item is present or not
  //List Item test
}

TEST(TestInventoryClass, questFalseCheckTest) {
  //Check for 5 valid pieces, then rm all and add finished item
  //Check on failing(nothing updates), check on some(nothing updates)
  //Check on has all(rm and adds)
  std::vector<Item*> v;
  for (int i = 0; i < 4; i++) {
    v.push_back(new FlameItem("Flame Part", "temp"));
  }
  Inventory bag(v);
  EXPECT_FALSE(bag.questCheck());
  for (auto i : v) {
    delete i;
  }
}

TEST(TestInventoryClass, questTrueCheckTest) {
  //Check for 5 valid pieces, then rm all and add finished item
  //Check on failing(nothing updates), check on some(nothing updates)
  //Check on has all(rm and adds)
  std::vector<Item*> v;
  for (int i = 0; i <= 4; i++) {
    v.push_back(new FlameItem("Flame Part", "temp"));
  }
  Inventory bag(v);
  EXPECT_TRUE(bag.questCheck());
    for (auto i : v) {
    delete i;
  }
}

TEST(TestInventoryClass, choseItemTest) {
    Item * i1 = new Claws("Sword", "Kill em with sword");
    Item * i2 = new Pipe("Sword1", "Kill em with sword");
    Item * i3 = new FlameItem("Sword2", "Kill em with sword");
    Inventory bag({i1, i2, i3});
    std::ifstream fin;
    fin.open("test/data/correctChoseItemTest.txt");
    EXPECT_EQ(bag.chooseItem(fin), i2);
    delete i1;
    delete i2;
    delete i3;
    fin.close();
}

