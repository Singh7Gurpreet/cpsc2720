#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "Environment.h"
#include "Inventory.h"
#include "Character.h"

class MainPlayer : public Player {
 public:
  MainPlayer(std::string name, Environment* startLoc, int startHP = 100);
  bool search();
  bool interact();
  int getOxygen();
  void reduceOxygen();
  void setOxygen(int newVal);
  bool useItem(std::istream& in, Player* target = nullptr);
  bool move(std::istream&);
  bool helpAction();
  void statDisplay();
  void actionSelect(std::istream&, Player* target);

 private:
  int oxygen;
};

#endif
