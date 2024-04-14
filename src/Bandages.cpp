#include "Bandages.h"
#include "Character.h"
#include <iostream>
#include <string>

#include "Item.h"

Bandages::Bandages(std::string initName, std::string initDescription)
    : Item(initName) {
  setName(initName);
  setDescription(initDescription);
  setUses(3);
}

bool Bandages::action(Player* user, Player* target, std::istream& in) {
  if (user->getHP() == 100) {
    std::cout << "Your feeling fine, better to hold onto this" << std::endl;
    return false;
  }
  std::cout << "You patch yourself up" << std::endl;
  user->setHP(100);
  this->reduceUses();
  return true;
}
