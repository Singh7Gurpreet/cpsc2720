#ifndef FLAMEITEM_H
#define FLAMEITEM_H

#include <iostream>
#include <string>

#include "Item.h"
class FlameItem : public Item {
 public:
  FlameItem(std::string initName, std::string initDescription);
  bool action(Player* user, Player* target, std::istream& = std::cin);
};

#endif
