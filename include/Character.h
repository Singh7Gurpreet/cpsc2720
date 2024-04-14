#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "Environment.h"
#include "Inventory.h"
//#include "Item.h"

class Character {
 private:
  std::string Name;
  std::string Description;
  Inventory bag;
  Environment* currLocation;

 public:
  Character(const std::string& name, const std::string& description,
            Environment* startLoc);
  Character();
  ~Character();

  // Getter
  std::string getDescription();

  std::string getName();

  // Setter
  void setDescription(const std::string& desc);

  // Method declaration for current location handling :)
  Environment* setLocation(Environment*);
  Environment* getLocation();

  // Inventory management
  bool hasItem(Item* item);
  void addItem(Item* item);
  void removeItem(Item* item);
  Inventory getBag();
  void setBag(Inventory newBag);
};

class Player : public Character {
 public:
  Player(std::string name, Environment* startLoc, int startHP);
  int getHP();
  void setHP(int setHP);
  bool takeDamage(int dmg);
  virtual void statDisplay() = 0;
  virtual bool move(std::istream& in) = 0;
  virtual bool helpAction() = 0;
  virtual bool useItem(std::istream& in, Player* User) = 0;
  virtual bool search() = 0;
  virtual bool interact() = 0;
  virtual int getOxygen() = 0;
  virtual void reduceOxygen() = 0;
  virtual void setOxygen(int newVal) = 0;
  virtual void actionSelect(std::istream&, Player* target) = 0;

 private:
  int HP;
};


class NPC : public Character {
 public:
  NPC(std::string name, std::string wantedItem, std::string msg);
  std::string getHint();
  void setHint(std::string);
  std::string getPrompt();
  bool attemptTrade(Player* user);

 private:
  std::string hint, name;
  bool tradeState = false;
  std::string initialPrompt;
  std::string desiredItem;
};

#endif
