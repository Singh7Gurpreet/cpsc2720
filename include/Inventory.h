// Minimal source file for a placebo class that does nothing but allows the
// pipeline to pass.

#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>
#include "Item.h"

class Inventory {
 public:
  Inventory();
  Inventory(std::vector<Item*> itemList);
  ~Inventory();

  bool hasItem(std::string toFindName);
  bool hasItem(Item* item);

  Item* chooseItem(std::istream& in);
  bool isEmpty();
  std::vector<Item*> getItems();
  Item* getItem(int index);

  void addItem(Item* item);

  void rmItem(Item* item);

  bool questCheck();

 private:
  std::vector<Item*> Items;
};

#endif
