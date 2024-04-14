#include "Item.h"
#include <iostream>
#include <string>
Item::Item(std::string newName) { name = newName; }

// Getter for name
std::string Item::getName() const { return name; }

// Setter for name
void Item::setName(const std::string& newName) { name = newName; }

// Getter for description
std::string Item::getDescription() const { return description; }

// Setter for description
void Item::setDescription(const std::string& newDescription) {
  description = newDescription;
}

void Item::reduceUses() {
  uses -= 1;
}

// Getter for uses
int Item::getUses() const {
  return uses; }

// Setter for uses
void Item::setUses(int newUses) { uses = newUses; }
