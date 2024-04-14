#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
class Player;

class Item {
 private:
  std::string name;
  std::string description;
  int uses;

 public:
  Item(std::string newName);

  // Getter for name
  std::string getName() const;

  // Setter for name
  void setName(const std::string& newName);

  // Getter for description
  std::string getDescription() const;

  // Setter for description
  void setDescription(const std::string& newDescription);

  // Getter for uses
  int getUses() const;

  void reduceUses();

  // Setter for uses
  void setUses(int newUses);

  virtual bool action(Player* user,
  Player* target,
  std::istream& = std::cin) = 0;
};

#endif  // ITEMCLASS_H
