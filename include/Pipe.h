#ifndef PIPE_H
#define PIPE_H

#include <iostream>
#include <string>

#include "Item.h"
class Pipe : public Item {
 public:
  Pipe(std::string initName, std::string initDescription);
  bool action(Player* user, Player* target, std::istream& = std::cin);
};

#endif
