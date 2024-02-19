/**
 * @author L. Nicole  Wilson [n.wilson@uleth.ca]
 * @date 2023-09
 */
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

#include "BingoTypes.h"
#include "BingoCard.h"
#include "UserInput.h"
#include "VictoryCondition.h"
#include "Square.h"
#include "Exceptions.h"

BingoCard::BingoCard(BingoTypes::gameType game)
  : _game{game} {
  _victoryCondition = nullptr;
}

BingoCard::BingoCard(std::vector<Square*> grid, BingoTypes::gameType type)
  : BingoCard{type} {
  setGrid(grid);
}

BingoCard::~BingoCard() {
  if (_victoryCondition != nullptr) {
    delete _victoryCondition;
    _victoryCondition = nullptr;
  }
  for (auto i : _grid) {
    delete i;
  }
  _grid.clear();
}

BingoTypes::gameType BingoCard::getGameType() {
  return _game;
}

BingoTypes::victoryType BingoCard::getVictoryType() {
  if (_victoryCondition == nullptr)
    throw incomplete_settings("Victory condition not set");
  return _victoryCondition->getVictoryType();
}

Square* BingoCard::getSquare(BingoTypes::squarePos pos) {
  int index = 0;
  try {
    index = squarePosToLocation(pos);
  } catch (bad_input) {
    return nullptr;
  }
  return _grid[index];
}

void BingoCard::setVictoryCondition(VictoryCondition* victory) {
  if (victory == nullptr) throw bad_input("Victory is null");
  delete _victoryCondition;
  _victoryCondition = victory;
}

void BingoCard::setGrid(std::vector<Square*> grid) {
  checkGridValidity(grid);
  _grid = grid;
}

void BingoCard::resetCard() {
  checkGridValidity(_grid);
  for (auto i : _grid)
    i->resetSquare();
}

bool BingoCard::daubSquare(unsigned numberCalled, BingoTypes::squarePos pos) {
  int index = 0;
  checkGridValidity(_grid);
  index = squarePosToLocation(pos);

  Square* current = nullptr;
  current = _grid[index];
  if ( current->getDaubState()->isDaubed() ) return false;


  current->daubSquare(numberCalled);
  if (numberCalled != current->getValue()) {
    for (int i = 0; i < _grid.size(); i++)
        _grid[i]->shouldDaubSquare(numberCalled);
  }
  return (current->getDaubState())->isDaubed();
}

bool BingoCard::isCorrect() {
  try {
    checkGridValidity(_grid);
  } catch (card_to_game_mismatch) {
    return false;
  } catch (bad_input) {
    return false;
  }

  for ( auto i : _grid )
    if ( i->getDaubState()->isCorrect() == false ) return false;
  return true;
}

bool BingoCard::isVictorious() {
  if (_victoryCondition == nullptr)
    throw incomplete_settings("Victory Condition is null pointer");
  try {
    checkGridValidity(_grid);
  } catch (card_to_game_mismatch) {
    return false;
  } catch (bad_input) {
    return false;
  }
  return _victoryCondition->hasWon(_grid);
}

bool BingoCard::typesMatch(BingoTypes::gameType game,
                           BingoTypes::victoryType victory) {
    if (_victoryCondition == nullptr) throw incomplete_settings("");
    return (
      (_game == game) && (victory == _victoryCondition->getVictoryType()));
}

void BingoCard::checkGridValidity(std::vector<Square*> grid) {
  int size = (_game == BingoTypes::gameType::BINGO75)? 15:10;

  std::vector<unsigned int> hashSet((size*5)+1, 1);

  if (grid.size() == 0) {
    throw incomplete_settings("Invalid Size");
  }
  if (grid.size() != 25) {
    throw invalid_size("Not consists of 25 squares");
  }

  for (int i = 0; i < 5; i++) {
    int lowerLimit = (i*size) + 1;
    int upperLimit = (i+1)*size;
    for (int j = i*5; j < (i+1)*5; j++) {
      if (j == 12) {
        if (grid[j]->getValue() == 0) continue;
        else
          throw card_to_game_mismatch("Card is not in its correct position");
      }
      Square* currentSquare = grid[j];
      int valueOfSquare = currentSquare->getValue();
    if (valueOfSquare > upperLimit || valueOfSquare < lowerLimit) {
      throw card_to_game_mismatch("Card is not in its correct position");
    }
    if (hashSet[valueOfSquare] != 1) {
      throw bad_input("Duplicates not possible");
    }
    hashSet[valueOfSquare] = 2;
  }
}
}

unsigned BingoCard::squarePosToLocation(BingoTypes::squarePos pos) {
  if (_grid.size() < 25 ||
      pos.row > 5 ||
      pos.row < 1 ||
      pos.col < 1 ||
      pos.col > 5) {
      throw bad_input("Pos not in range"); }
  pos.row--;
  pos.col--;
  int result = (5 * (pos.col) + (pos.row));
  return result;
  }
