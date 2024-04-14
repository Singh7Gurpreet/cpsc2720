#ifndef OXYGEN_H
#define OXYGEN_H

#include <iostream>
#include <string>

#include "Item.h"
class Oxygen : public Item {
 public:
  Oxygen(std::string initName, std::string initDescription);
  bool action(Player* user, Player* target, std::istream& = std::cin);
};

#endif
