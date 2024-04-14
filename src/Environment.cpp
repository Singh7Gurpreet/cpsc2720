// Environnement Class

#include "Environment.h"
#include "Character.h"

#include <string>

Environment::Environment(std::string newName = "", std::string newDesc = "") {
  name = newName;
  description = newDesc;
}

Environment::~Environment() {
  if (itemsInRoom != nullptr) {
  std::vector<Item*> h = itemsInRoom->getItems();
  for (auto i : h) {
    delete i;
    i = nullptr;
  }
  itemsInRoom->getItems().clear();
  delete itemsInRoom;
  }
  // for(int i = 0; i < routes.size();i++){
  //   delete routes[i];
  //   routes[i] = nullptr;
  // }
}

void Environment::setInventory(Inventory* bag) { this->itemsInRoom = bag; }
void Environment::addItem(Item* newItem) {
  itemsInRoom->addItem(newItem);
}

bool Environment::checkRoutesValidity(std::vector<Environment*> routes) {
  if (routes.size() == 0) return false;

  for (int i = 0; i < routes.size(); i++) {
    if (routes[i] == nullptr) return false;
  }
  return true;
}
std::string Environment::getDescription() {
  return description;
}

void Environment::setRoutes(std::vector<Environment*> routes) {
  if (!checkRoutesValidity(routes)) {
    std::cerr << "Not valid grid" << std::endl;
  }
  this->routes = routes;
}

void Environment::addRoute(Environment* route) {
  this->routes.push_back(route);
}

std::string Environment::getName() { return name; }

std::vector<Environment*> Environment::getRoutes() { return routes; }

Inventory* Environment::getItemsInRoom() { return itemsInRoom; }

GeneralRoom::GeneralRoom(std::string newName, std::string newDesc)
    : Environment(newName, newDesc) {}

bool GeneralRoom::interactWith(Player* user, std::istream& in) {
  // No idea what this interact with will do;
  std::cout << "You fiddle around with some things,/n"
  "but nothing specail happens." << std::endl;
  return true;
}

NpcRoom::NpcRoom(std::string newName, std::string newDesc)
    : Environment(newName, newDesc) {}
NpcRoom::~NpcRoom() {
delete npc;
}

NPC* NpcRoom::getNPC() { return npc; }

void NpcRoom::setNPC(NPC* character) { npc = character; }

bool NpcRoom::interactWith(Player* user, std::istream& in) {
  //Pull npc from list
  //Run actions against npc
  if (npc == nullptr) {
    std::cout << "Strangely this person isnt here?";
    return false;
  }
  std::cout << npc->getPrompt() <<std::endl;
  std::cout << "Would you like to trade (y or n): ";
  std::string input = "";
  in >> input;
  if (input == "y") {
    //Select Item

    //Handoff
    npc->attemptTrade(user);
  }
  return true;
}


PuzzleRoom::PuzzleRoom(std::string newName,
// NOLINTNEXTLINE(runtime/string)
std::string newDesc,
Item* newReward)
    : Environment(newName, newDesc) {
      reward = newReward;
    }

void PuzzleRoom::setPuzzle(std::string riddle) { puzzle = riddle; }

std::string PuzzleRoom::getPuzzle() { return puzzle; }

void PuzzleRoom::setAnswer(std::string answer) { this->answer = answer; }

void PuzzleRoom::giveReward(Player* user) {
  user->addItem(reward);
}


bool PuzzleRoom::interactWith(Player* user, std::istream& in) {
  // No idea what this interact with will do;
  // Puzzle Prompt
  std::cout << getPuzzle() << std::endl;
  std::string answerInput = "";
  std::cout << "Input:";
  in >> answerInput;
  if (solved) {
    std::cout << "Looks like my work here is done" << std::endl;
    return false;
  }
  if (answerInput == this->answer) {
    //void rewardMsg();
    getRewardMsg();
    setSolved();
    //Accomlish reward, update state or give item
    if (reward != nullptr) {
      giveReward(user);
    }
  } else {
    std::cout << "That doesn't seem quite right" << std::endl;
  }
  return true;
}
void PuzzleRoom::getRewardMsg() {
  std::cout << rewardMsg << std::endl;
}
void PuzzleRoom::setRewardMsg(std::string msg) {
  rewardMsg = msg;
}
void PuzzleRoom::setReward(Item* setter) {
  reward = setter;
}
Item* PuzzleRoom::getReward() {
  return reward;
}

bool PuzzleRoom::getSolved() { return solved; }
void PuzzleRoom::setSolved() { solved = true; }
HazardRoom::HazardRoom(std::string newName, std::string newDesc)
    : Environment(newName, newDesc) {}

bool HazardRoom::getHazardStatus() { return hazardActive; }

void HazardRoom::triggerHazard() { hazardActive = true; }

void HazardRoom::clearHazard() { hazardActive = false; }

void HazardRoom::setHazardDesc(std::string input) {
  hazardDesc = input;
}

std::string HazardRoom::getHazardDesc() {
  return hazardDesc;
}

void HazardRoom::setHazardDmg(int input) {
  dmgVal = input;
}

int HazardRoom::getHazardDmg() {
  return dmgVal;
}

bool HazardRoom::interactWith(Player* user, std::istream& in) {
  // No idea what does this function do
  //Check room state, if active then continue
  //Check for item to fix this, if not take some damage
  if (hazardActive) {
    // get Hazard desc
    std::cout << this->getHazardDesc() << std::endl;
    // get hazard punihs value
    user->takeDamage(this->getHazardDmg());
    // deal hazard damage
  }
  //Otherwise, do a usage of the item and switch
  return true;
}

