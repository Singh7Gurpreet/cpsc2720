#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <string>
#include <vector>

#include "Character.h"
#include "Environment.h"
#include "Inventory.h"
#include "Item.h"
class GameManager {
 private:
  std::vector<Environment*> map;
  PuzzleRoom* selfDestructorRoom = nullptr;
  std::vector<Player*> characters;
  int countDown;
  bool selfDistructStatus = true;

 public:
  GameManager(int countDownStart = 20);
  ~GameManager();
  // GameSetup
  void createMap();
  void createCharacters();
  Inventory* createRoomItems(bool fPresent, int toAdd);
  void gameSetup();

  // Outside functions
  void countDownUpdate();
  Player* getUser();
  Player* getAlien();
  void startMsg();
  Item* giveQuestItem(Player* user);
  bool winLossCheck();
  void disableCountDown();
  void warningMsg(std::istream& in = std::cin);
};

#endif  // ITEMCLASS_H
