#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <string>

#include "Item.h"
class Note : public Item {
 public:
  Note(std::string initName, std::string initDescription);
  bool action(Player* user, Player* target, std::istream& = std::cin);
};

#endif
