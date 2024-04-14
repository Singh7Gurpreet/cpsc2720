#ifndef FLAMEPARTITEM_H
#define FLAMEPARTITEM_H

#include <iostream>
#include <string>

#include "Item.h"
class FlamePartItem : public Item {
 public:
  FlamePartItem(std::string initName, std::string initDescription);
  bool action(Player* user, Player* target, std::istream& = std::cin);
};

#endif
