
#include "Inventory.h"
#include "FlameItem.h"
#include <string>
#include <vector>


Inventory::Inventory() {}  // Test that its empty

// Test on an empty list, one item, and many
Inventory::Inventory(std::vector<Item*> itemList) {
  for (int i = 0; i < itemList.size(); i++) {
    Items.push_back(itemList[i]);
  }
}

Inventory::~Inventory() {
  // Deallocate each item, the end
}
// Test on nothing, filled and missing, filled and with.
bool Inventory::hasItem(std::string toFindName) {
  // Will wait for items implement, will be a fast add
  for (int i = 0; i < Items.size(); i++) {
    if (toFindName == Items[i]->getName()) {
      return true;  // Item found, return true
    }
  }
  return false;
}

// Test on nothing, filled and missing, filled and with.
bool Inventory::hasItem(Item* item) {
  bool flag = false;
  for (int i = 0; i < Items.size(); i++) {
    if (item == Items[i]) {
      flag = true;
    }
  }
  return flag;
}

// Test on none, many and one
Item* Inventory::chooseItem(std::istream& in) {
  //Provides list
  std::vector<Item*> itemList = this->getItems();
  if (itemList.size() == 0) {
    std::cout << "You have nothing to use" << std::endl;
    return nullptr;
  } else {
    std::cout << "Pick an Item:" << std::endl;
    std::string input;
    int validatedInput;
    do {
      int j = 1;
      for (auto i : itemList) {
        std::cout << j++ << ". " << i->getName() << "\n";
      }
      std::cout << j << ". Cancel" << "\n";
      std::cout << "Pick an Item to use: \n" << std::endl;
      bool repeat = true;
      while (repeat) {
      try {
        in >> input;
        validatedInput = std::stoi(input);
        repeat = false;
      }
      catch(const std::exception& ex)
      {}
    }
    if (validatedInput == j) {
      return nullptr;
    }
  } while (validatedInput < 1 || validatedInput > itemList.size());
  //Use selected Item
  return itemList[validatedInput-1];
  //return item use type
  }
}

bool Inventory::isEmpty() { return Items.size(); }

std::vector<Item*> Inventory::getItems() { return Items; }

// Test on an empty list, one item, and many
Item* Inventory::getItem(int index) { return Items[index]; }

// Check it gets added
void Inventory::addItem(Item* item) { Items.push_back(item); }

// Check it does nothing if item is not in the list, and if removed if it is

void Inventory::rmItem(Item* item) {
  for (int i = 0; i < Items.size(); i++) {
    // Pretty sure theres a find function, but meh, scale is small
    // THIS IS A SPECIFIC ITEM ADDRESS, might alter to check by name
    if (item == Items[i]) {
      Items.erase(Items.begin() + i);
    }
  }
}

// Check it does nothing if item is not in the list, and if removed if it is
// void Inventory::rmItem(int index) { Items.erase(Items.begin() + index); }

bool Inventory::questCheck() {
  // Wait for items, and then deal with it
  int counter = 0;
  for (int i = 0; i < Items.size(); i++) {
    //Find 5 flamethrower parts
    if (Items[i]->getName() == "Flame Part") {
      counter += 1;
    }
  }
  if (counter >= 5) {
    std::cout <<
    "It looks like you can make a flamethower with what you have"
    << std::endl;
    //Remove all flamethrower parts, and add flamer to inv
    return true;
  }
  return false;
}
