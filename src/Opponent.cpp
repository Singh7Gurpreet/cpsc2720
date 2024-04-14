#include "Opponent.h"
#include <time.h>

#include <iostream>
#include <vector>

Opponent::Opponent(std::string name, Environment* spawnLoc, int startHP)
    : Player(name, spawnLoc, startHP) {}

bool Opponent::useItem(std::istream& in, Player* User) {
  // Uses its only item, claws
  if (User->getHP() > 0) {
    Inventory currBag = this->getBag();
    Item* weapon = currBag.getItem(0);
    weapon->action(User, User);
  }
  return true;
}

bool Opponent::move(std::istream& in) {
  if (this->getLocation() == nullptr ||
      this->getLocation()->getRoutes().size() == 0) {
    std::cerr << "Current room not set";
    return false;
  }
  if (this->getHP() <= 0) {
      return false;
  }

  std::vector<Environment*> doors = this->getLocation()->getRoutes();
  srand(time(0));
  int input;

  // NOLINTNEXTLINE(runtime/threadsafe_fn)
  input = static_cast<int>(rand()) % doors.size();
  this->setLocation(doors[input]);
  return true;
}
void Opponent::statDisplay() {
  std::cout << getName() << std::endl;
  std::cout << "HP: " << getHP() << std::endl;
  std::cout << "----------------------------" << std::endl;
}

// Possible future adds, if we want alien to be player controlled
void Opponent::actionSelect(std::istream&, Player* target) {}
bool Opponent::helpAction() { return false; }
bool Opponent::search() { return false; }
bool Opponent::interact() { return false; }
int Opponent::getOxygen() { return 0; }
void Opponent::reduceOxygen() {}
void Opponent::setOxygen(int newVal) {}
