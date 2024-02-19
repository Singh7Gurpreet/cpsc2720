/**
* @author L. Nicole Wilson [n.wilson@uleth.ca]
* @date 2023-10
*/
#ifndef BINGOTYPES_H_INCLUDED
#define BINGOTYPES_H_INCLUDED

/**
* @class BingoTypes BingoTypes.h "BingoTypes.h"
* @brief A collection of types and constants.
*/
class BingoTypes {
 public:
  enum gameType {BINGO75 = 75, BINGO50 = 50};

  static const unsigned NUM_VICTORY_TYPES = 4;
  enum victoryType {HORIZONTAL_LINE = 1, VERTICAL_LINE, ANY_LINE, BLACKOUT};

  static const unsigned NUM_MOVE_TYPES = 8;
  enum moveType {DAUB = 1, BINGO, SHOW_CARD, CHECK_CARD, SHOW_GAME,
    SHOW_BOARD, HELP, QUIT_GAME};

  struct squarePos {
    unsigned row;
    unsigned col;
  };
};

#endif // BINGOTYPES_H_INCLUDED
