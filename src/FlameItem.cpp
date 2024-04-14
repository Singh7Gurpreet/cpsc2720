#include "FlameItem.h"
#include "Character.h"
#include <iostream>
#include <string>

#include "Item.h"

FlameItem::FlameItem(std::string initName, std::string initDescription)
    : Item(initName) {
  setName(initName);
  setDescription(initDescription);
  setUses(3);
}

bool FlameItem::action(Player* user, Player* target, std::istream& in) {
  if (user->getLocation() == target->getLocation()) {
    std::cout << "You singe the Alien, severely wounding it"<< std::endl;
    target->takeDamage(250);
    this->reduceUses();
    return false;
  }
    std::cout << "You probably want to save this for the Alien"<< std::endl;
    return false;
}
