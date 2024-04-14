#include "Note.h"
#include "Character.h"
#include <iostream>
#include <string>

#include "Item.h"

Note::Note(std::string initName, std::string initDescription)
    : Item(initName) {
  setName(initName);
  setDescription(initDescription);
  setUses(999);
}

bool Note::action(Player* user, Player* target, std::istream& in) {
  std::cout << "You read the note" << std::endl;
  std::cout << this->getDescription() << std::endl;
  return false;
}
