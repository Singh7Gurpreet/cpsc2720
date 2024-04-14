#include "Character.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

Character::Character(const std::string& name, const std::string& description,
                     Environment* startLoc) {
  Name = name;
  Description = description;
  currLocation = startLoc;
}

Character::Character() {}

Character::~Character() {
  delete currLocation;
  currLocation = nullptr;
  for (Item* i : bag.getItems()) {
    delete i;
    i = nullptr;
  }
}

Player::Player(std::string name, Environment* startLoc, int startHp)
    : Character(name, "", startLoc) {
  HP = startHp;
}

bool Character::hasItem(Item* i1) {
  return std::any_of(bag.getItems().begin(),
  bag.getItems().end(), [&](Item* i) {
    return i1 == i;
  });
}

void Character::setBag(Inventory newBag) {
  bag = newBag;
}
void Player::setHP(int newHP) {
  HP = newHP;
}
// Getter for Description
std::string Character::getDescription() { return Description; }

std::string Character::getName() { return Name; }

void Character::addItem(Item* item) { bag.addItem(item); }

void Character::removeItem(Item* item) { bag.rmItem(item); }

Inventory Character::getBag() { return bag; }

// Setter for Description
void Character::setDescription(const std::string& desc) { Description = desc; }

// To be implemented according to our application needs, to be discussed or
// maybe
Environment* Character::getLocation() { return currLocation; }

Environment* Character::setLocation(Environment* temp) {
  this->currLocation = temp;
  return currLocation;
}

int Player::getHP() { return HP; }

bool Player::takeDamage(int damage) {
  if (damage < 0) {
    return false;
  } else {
    HP -= damage;
  }
  return true;
}
//Cant attack or die so we have character inherit here
NPC::NPC(std::string name, std::string desire, std::string msg) {
  this->name = name;
  this->desiredItem = desire;
  this->initialPrompt = msg;
}
std::string NPC::getHint() { return hint; }
void NPC::setHint(std::string hint) { this->hint = hint; }
std::string NPC::getPrompt() {return initialPrompt;}
bool NPC::attemptTrade(Player* user) {
  //Check given item name
  if (tradeState) {
    std::cout <<"I got nothing left for you" << std::endl;
    return true;
  }
  //Auto take item if player has item, if not
  std::vector<Item* > list = user->getBag().getItems();
  for (int i = 0; i < list.size(); i++) {
      if (list[i]->getName() == desiredItem) {
        std::cout << "I see you have what I need, great." <<std::endl;
        user->removeItem(list[i]);
        //check if theres an item on hand
        if (this->getBag().getItems().size() == 0) {
          std::cout << this->getHint() << std::endl;
          return true;
        } else {
          std::cout << "As promised, heres your item" << std::endl;
          user->addItem(this->getBag().getItem(0));
          this->getBag().rmItem(this->getBag().getItem(0));
          tradeState = true;
          return true;
        }
      }
  }
  std::cout << "Don't waste my time, /n"
  "you need the item before we can trade" << std::endl;
  return true;
}
