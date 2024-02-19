/**
* @author L. Nicole  Wilson [n.wilson@uleth.ca]
* @date 2023-09
*/
#include <vector>

#include "BingoCard.h"
#include "BingoCardFactory.h"
#include "BingoTypes.h"
#include "MakeRandomInt.h"
#include "VictoryCondition.h"
#include "Exceptions.h"

BingoCardFactory::BingoCardFactory() {}

BingoCardFactory::~BingoCardFactory() {}

BingoCard* BingoCardFactory::makeBingoCard(BingoTypes::gameType game,
    VictoryCondition* victory) {
  if (victory == nullptr) {
    throw incomplete_settings
    ("Factory cannot make Bingo Card without a victory condition.");
  }
  if (game != BingoTypes::BINGO50 && game != BingoTypes::BINGO75) {
    throw invalid_size("The game must be a valid gameType.");
  }

  BingoCard* card = new BingoCard(game);
  card->setVictoryCondition(copyVictoryCondition(victory));

  delete victory;

  unsigned cardMax = static_cast<unsigned>(game);
  unsigned colRange = cardMax / 5;

  std::vector<Square*> grid;
  std::vector<Square*> newSquares;

  for (int i = 0; i < 5; ++i) {
    newSquares = makeSquares(i * colRange + 1, (i + 1) * colRange);
    grid.insert(grid.end(), newSquares.begin(), newSquares.end());
    newSquares.erase(newSquares.begin(), newSquares.end());
  }

  if (grid.size() > 12) {
    delete grid[12];
    grid[12] = new FreeSquare();
  }

  card->setGrid(grid);

  return card;
}

std::vector<Square*> BingoCardFactory::makeSquares(unsigned min, unsigned max,
    unsigned n) {
  if (max - min + 1 < n) {
    throw invalid_size("Insufficient range to make distinct squares.");
  }

  std::vector<unsigned> range;
  for (unsigned i = min; i <= max; ++i) {
    range.push_back(i);
  }

  MakeRandomInt& randInt = MakeRandomInt::getInstance();

  std::vector<Square*> squares;
  for (unsigned k = 0; k < n; ++k) {
    unsigned nextPos = randInt.getValue(range.size());
    squares.push_back(new IntSquare(range[nextPos]));
    range.erase(range.begin() + nextPos);
  }

  return squares;
}

VictoryCondition* BingoCardFactory::copyVictoryCondition
(VictoryCondition* victory) {
  switch (victory->getVictoryType()) {
    case BingoTypes::ANY_LINE:
      return new AnyLine();
    case BingoTypes::HORIZONTAL_LINE:
      return new HorizontalLine();
    case BingoTypes::VERTICAL_LINE:
      return new VerticalLine();
    case BingoTypes::BLACKOUT:
      return new Blackout();
    default:
      return nullptr;
  }
}
