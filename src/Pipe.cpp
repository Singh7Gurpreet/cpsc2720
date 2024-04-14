#include "Pipe.h"
#include "Character.h"
#include <iostream>
#include <string>

#include "Item.h"

Pipe::Pipe(std::string initName, std::string initDescription)
    : Item(initName) {
  setName(initName);
  setDescription(initDescription);
  setUses(1);
}

bool Pipe::action(Player* user, Player* target, std::istream& in) {
  //Find location adjacencies
  std::vector<Environment*> doors = user->getLocation()->getRoutes();
  std::cout << "Enter the room number you want to throw the pipe in\n";
  int input;
  std::string temp;
  do {
    int j = 1;
    for (auto i : doors) {
      std::cout << j++ << ". " << i->getName() << "\n";
    }
    std::cout << j << ". Cancel" << "\n";
    std::cout << "Enter the room corresponding number you want to enter: "
              << std::endl;
    in >> temp;
    input = std::stoi(temp);
    if (input == j) {
      return false;
    }
  } while (input < 1 || input > doors.size());
  //Pick one to throw
  //Cancel option that returns false instead
  std::cout << "After you throw the pipe,\n"
  "You hear frantic scurring crash into that room" << std::endl;
  target->setLocation(doors[input - 1]);
  this->reduceUses();
  return false;
}
