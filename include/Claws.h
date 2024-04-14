#ifndef CLAWS_H
#define CLAWS_H

#include <iostream>
#include <string>

#include "Item.h"
class Claws : public Item {
 public:
  Claws(std::string initName, std::string initDescription);
  bool action(Player* user, Player* target, std::istream& = std::cin);
};

#endif
