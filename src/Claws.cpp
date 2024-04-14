#include "Claws.h"
#include "Character.h"
#include <iostream>
#include <string>

#include "Item.h"

Claws::Claws(std::string initName, std::string initDescription)
    : Item(initName) {
  setName(initName);
  setDescription(initDescription);
  setUses(999);
}

bool Claws::action(Player* user, Player* target, std::istream& in) {
  std::cout << "The alien takes a quick slash,/n"
  "severely wounding you." << std::endl;
  target->takeDamage(50);
  return true;
}
