#include "Oxygen.h"
#include "Character.h"
#include <iostream>
#include <string>

#include "Item.h"

Oxygen::Oxygen(std::string initName, std::string initDescription)
    : Item(initName) {
  setName(initName);
  setDescription(initDescription);
  setUses(1);
}

bool Oxygen::action(Player* user, Player* target, std::istream& in) {
  user->setOxygen(100);
  this->reduceUses();
  return true;
}
