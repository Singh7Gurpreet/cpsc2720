#include "MainPlayer.h"
#include <time.h>

MainPlayer::MainPlayer(std::string name, Environment* spawnLoc, int startHP)
    : Player(name, spawnLoc, startHP) {
  oxygen = 100;
}

bool MainPlayer::useItem(std::istream& in, Player* target) {
  // Will use particular
  //List inventory,
  Inventory currBag = this->getBag();
  //List items with choice,
  Item* chosenItem = currBag.chooseItem(in);
  if (chosenItem == nullptr) {
    return false;
  }
  bool result = chosenItem->action(this, target);
  if (chosenItem->getUses() <= 0) {
    std::cout << "This item has seen all its uses,\n"
    "might as well discard it." << std::endl;
    currBag.rmItem(chosenItem);
    this->setBag(currBag);
    delete chosenItem;
  }
  return result;
  //false - free action item(do nothings)
  //true - full action items(do somethings)
}

bool MainPlayer::search() {
  static bool calledSrand = false;
  if (!calledSrand) {
    srand(time(0));
    calledSrand = true;
  }

  std::vector<Item*> bag = this->getLocation()->getItemsInRoom()->getItems();
  if (bag.empty()) {
    std::cout << "It appears this room is picked clean." << std::endl;
    return false;
    } else {
    // NOLINTNEXTLINE(runtime/threadsafe_fn)
    int index = rand() % bag.size();
    std::cout << "You found " << bag[index]->getName() << "!!!!\n";
    //Add item to personal bag, Remove item from room
    this->addItem(bag[index]);
    this->getLocation()->getItemsInRoom()->rmItem(bag[index]);
    return true;
  }
}

bool MainPlayer::interact() {
  // all logic for controlling the actions of the player
  return this->getLocation()->interactWith(this);
}

int MainPlayer::getOxygen() { return oxygen; }

void MainPlayer::reduceOxygen() {
  // on what aspect will we reduce the oxygen
  setOxygen(oxygen - 5);
}
void MainPlayer::setOxygen(int oxygenLevel) { oxygen = oxygenLevel; }

bool MainPlayer::move(std::istream& in) {
  if (this->getLocation() == nullptr ||
      this->getLocation()->getRoutes().size() == 0) {
    std::cerr << "Current room not set\n";
    return false;
  }
  std::vector<Environment*> doors = this->getLocation()->getRoutes();
  std::cout << "Enter the room number you want to move in\n";
  std::string test;
  int input;
  do {
    int j = 1;
    for (auto i : doors) {
      std::cout << j++ << ". " << i->getName() << "\n";
    }
    std::cout << j << ". Cancel" << "\n";
    std::cout << "Enter the room corresponding number you want to enter: "
              << std::endl;
    std::cout << "Input:";
    bool repeat = true;
    while (repeat) {
      try {
        in >> test;
        input = std::stoi(test);
        repeat = false;
      }
      catch(const std::exception& ex)
      {}
    }
    if (input == j) {
      return false;
    }
  } while (input < 1 || input > doors.size());
  this->setLocation(doors[input - 1]);
  std::cout << this->getLocation()->getDescription() << std::endl;
  return true;
}

void MainPlayer::statDisplay() {
  std::cout << getName() << std::endl;
  std::cout << "HP: " << getHP() << std::endl;
  std::cout << "Oxygen: " << getOxygen() << std::endl;
  std::cout << "Current Location: " << getLocation()->getName() << std::endl;
  std::cout << "----------------------------" << std::endl;
}
bool MainPlayer::helpAction() {
    std::cout << "TODO: Kill the Alien and Stop Self Destruct" << std::endl;
    std::cout << "HP or Oxygen reaching zero are death,\n"
    "Oxygen decreases per action" << std::endl;
    std::cout << "Some actions will take up your action ie:move" << std::endl;
    std::cout << "Some actions will not up your action\n"
    "ie:some items, and help" << std::endl;
    std::cout << "1) Move : Move to an adjacent room" << std::endl;
    std::cout << "2) Search : References current room\n"
    "and get a RANDOM item in that room" << std::endl;
    std::cout << "3) Interact: Work/discuss with room\n"
    "facility, or npc" << std::endl;
    std::cout << "4) Use an Item : Select item and do\n"
    "its respective action" << std::endl;
    std::cout << "5) Help : Explains actions" << std::endl;
  return true;
}


void MainPlayer::actionSelect(std::istream& in, Player* target) {
  bool actionState = false;
  this->statDisplay();
  while (!actionState) {
    //switch
    std::cout <<"Pick your action:" << std::endl;
    std::cout << "1) Move" << std::endl;
    std::cout << "2) Search" << std::endl;
    std::cout << "3) Interact" << std::endl;
    std::cout << "4) Use an Item" << std::endl;
    std::cout << "5) Help" << std::endl;
    //Input segment
    bool repeat = true;
    std::string input;
    int validatedInput;
    while (repeat) {
      try {
        in >> input;
        validatedInput = std::stoi(input);
        repeat = false;
      }
      catch(const std::exception& ex)
      {}
    }
    switch (validatedInput) {
      case 1:
        //Move action
        actionState = this->move(in);
        break;
      case 2:
        //Seach
        actionState = this->search();
        break;
      case 3:
        //Interact - TODO
        actionState = this->interact();
        break;
      case 4:
        //Use an Item
        actionState = this->useItem(in, target);
        break;
      case 5:
        //Help
        this->statDisplay();
        actionState = this->helpAction();
        break;
    }
    //No good inputs given, loops
  }
}
