#ifndef BANDAGES_H
#define BANDAGES_H

#include <iostream>
#include <string>

#include "Item.h"
class Bandages : public Item {
 public:
  Bandages(std::string initName, std::string initDescription);
  bool action(Player* user, Player* target, std::istream& = std::cin);
};

#endif
