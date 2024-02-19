/**
* @author L. Nicole  Wilson [n.wilson@uleth.ca]
* @date 2023-09
*/
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

#include "VictoryCondition.h"

VictoryCondition::VictoryCondition(std::string description,
                                   BingoTypes::victoryType victory)
  : _description{description}, _victoryType{victory} {}

VictoryCondition::~VictoryCondition() {}

std::string VictoryCondition::getDescription() {
  return _description;
}

BingoTypes::victoryType VictoryCondition::getVictoryType() {
  return _victoryType;
}

bool VictoryCondition::checkSquareSet(std::vector<Square*> squares) {
  for (unsigned i = 0; i < squares.size(); ++i) {
    if (!((squares[i]->getDaubState())->isDaubed()
          && (squares[i]->getDaubState())->isCorrect()))
      return false;
  }
  return true;
}

HorizontalLine::HorizontalLine()
  : VictoryCondition{"Daub five squares in a horizontal line.",
                     BingoTypes::HORIZONTAL_LINE} {}

HorizontalLine::~HorizontalLine() {}

bool HorizontalLine::hasWon(std::vector<Square*> grid) {
  int j, i;
  for (i = 0; i <= 4; i++) {
    bool result = true;
    for (j = i; j <= 20 + i; j += 5) {
      if ( grid[j]->getDaubState()->isDaubed() == false ) {
        result = false;
        break;
      }
    }
    if (result == true) {
      return true;
    }
  }
  return false;
}
VerticalLine::VerticalLine()
  : VictoryCondition{"Daub five squares in a vertical line.",
                     BingoTypes::VERTICAL_LINE} {}

VerticalLine::~VerticalLine() {}

bool VerticalLine::hasWon(std::vector<Square*> grid) {
  for (int i = 0; i < 25; i += 5) {
    bool result = true;
    for (int j = i; j < (i + 5); j++) {
      if ( grid[j]->getDaubState()->isDaubed() == false ) {
        result = false;
        break;
      }
    }
    if ( result == true ) {
      return true;
    }
  }
  return false;
}

AnyLine::AnyLine()
  : VictoryCondition
    {"Daub five squares in a horizontal, vertical or diagonal line.",
     BingoTypes::ANY_LINE} {}

AnyLine::~AnyLine() {}

bool AnyLine::hasWon(std::vector<Square*> grid) {
  int i, j;
  bool result;
  //for vertical test
  for (i = 0; i < 25; i += 5) {
    result = true;
    for (j = i; j < (i + 5); j++) {
      if ( grid[j]->getDaubState()->isDaubed() == false ) {
        result = false;
        break;
      }
    }
    if ( result == true ) {
      return true;
    }
  }
  result = true;
  for ( i = 0; i < 25; i+=6 ) {
    if ( grid[i]->getDaubState()->isDaubed() == false ) {
      result = false;
      break;
    }
  }
  if ( result == true ) { return true; }
  result = true;
  //for left diagonal
  for ( i = 4; i <= 20; i+=4 ) {
    if ( grid[i]->getDaubState()->isDaubed() == false ) {
      result = false;
      break;
    }
  }
  if (result == true) { return true; }
    for ( i = 0; i <= 4; i++ ) {
    result = true;
    for (j = i; j <= 20 + i; j += 5) {
      if ( grid[j]->getDaubState()->isDaubed() == false ) {
        result = false;
        break;
      }
    }
    if (result == true) {
      return true;
    }
  }
  return false;
}


Blackout::Blackout()
  : VictoryCondition{"Daub all squares on the card.", BingoTypes::BLACKOUT} {}

Blackout::~Blackout() {}

bool Blackout::hasWon(std::vector<Square*> grid) {
  return checkSquareSet(grid);
}
