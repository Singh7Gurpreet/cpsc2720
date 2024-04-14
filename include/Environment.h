
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <vector>
#include <string>

#include "Inventory.h"

class Player;
class NPC;
class Environment {
  // a new change
  // Not possible to directly check for player or alien
  // need to pass parameter of player as it has current room id
 private:
  std::vector<Environment*> routes;
  std::string name;
  std::string description;
  Inventory* itemsInRoom;

 public:
  Environment(std::string newName, std::string newDesc);
  ~Environment();
  bool checkRoutesValidity(std::vector<Environment*>);
  void setRoutes(std::vector<Environment*>);
  void addRoute(Environment*);
  std::vector<Environment*> getRoutes();
  void setInventory(Inventory*);
  Inventory* getItemsInRoom();
  void addItem(Item* newItem);
  std::string getName();
  virtual bool interactWith(Player* user, std::istream& = std::cin) = 0;
  std::string getDescription();
};

class GeneralRoom : public Environment {
 public:
  GeneralRoom(std::string newName, std::string newDesc);
  bool interactWith(Player* user, std::istream& = std::cin);
};

class NpcRoom : public Environment {
 public:
  NpcRoom(std::string newName, std::string newDesc);
  ~NpcRoom();
  void setNPC(NPC* occupent);
  NPC* getNPC();
  bool interactWith(Player* user, std::istream& = std::cin);

 private:
  NPC* npc = nullptr;
};

class PuzzleRoom : public Environment {
 public:
  PuzzleRoom(std::string newName, std::string newDesc, Item* reward = nullptr);
  void setPuzzle(std::string riddle);
  std::string getPuzzle();
  void setAnswer(std::string ans);
  std::string getAnswer();
  void getRewardMsg();
  void setReward(Item* setter);
  Item* getReward();
  void setRewardMsg(std::string msg);
  void giveReward(Player* user);
  bool interactWith(Player* user, std::istream& = std::cin);
  bool getSolved();
  void setSolved();

 private:
  std::string puzzle, answer;
  bool solved = false;
  std::string rewardMsg = "PLACEHOLDER";
  Item* reward = nullptr;
};

class HazardRoom : public Environment {
 public:
  HazardRoom(std::string newName, std::string newDesc);
  bool getHazardStatus();
  void setHazardDesc(std::string input);
  std::string getHazardDesc();
  int getHazardDmg();
  void setHazardDmg(int input);
  void clearHazard();
  void triggerHazard();
  bool interactWith(Player* user, std::istream& = std::cin);

 private:
  std::string hazardDesc = "PLACEHOLDER";
  bool hazardActive = true;
  int dmgVal = 25;
};
#endif
