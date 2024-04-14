#ifndef OPPONENT_H
#define OPPONENT_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "Environment.h"
#include "Inventory.h"
#include "Character.h"

class Opponent : public Player {
 public:
  Opponent(std::string name, Environment* startLoc, int startHP = 500);
  bool useItem(std::istream& in, Player* User);
  bool move(std::istream&);
  bool helpAction();
  bool search();
  bool interact();
  int getOxygen();
  void reduceOxygen();
  void setOxygen(int newVal);
  void statDisplay();
  void actionSelect(std::istream&, Player* target);
};

#endif

