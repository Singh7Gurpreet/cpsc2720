#include "FlamePartItem.h"
#include "Character.h"
#include <iostream>
#include <string>

#include "Item.h"

FlamePartItem::FlamePartItem(std::string initName, std::string initDescription)
    : Item(initName) {
  setName(initName);
  setDescription(initDescription);
  setUses(999);
}

bool FlamePartItem::action(Player* user, Player* target, std::istream& in) {
  std::cout << "There must be a use for this with all the parts,\n"
  "looks like I need 5 of these"<< std::endl;
  return false;
}
