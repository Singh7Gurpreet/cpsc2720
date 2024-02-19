/**
* @author L. Nicole Wilson [n.wilson@uleth.ca]
* @date 2023-09
*/
#ifndef VICTORY_CONDITION_H_INCLUDED
#define VICTORY_CONDITION_H_INCLUDED

#include <string>
#include <vector>

#include "Square.h"
#include "BingoTypes.h"

/**
* @class VictoryCondition VictoryCondition.h "VictoryCondition.h"
* @brief Interface for bingo victory conditions.
*/
class VictoryCondition {
 public:
  /**
  * @brief Constructor.
  * @param [in] description Description of the victory condition suitable to
  *   be shared with players.
  * @param [in] victory A victory type.
  */
  VictoryCondition(std::string description, BingoTypes::victoryType victory);

  /**
  * @brief Destructor
  */
  virtual ~VictoryCondition();

  /**
  * @brief Access the _description.
  * @return The description of the victory condition.
  */
  std::string getDescription();

  /**
  * @brief Access the victoryType
  * @return The victoryType.
  */
  BingoTypes::victoryType getVictoryType();

  /**
  * @brief Examines the grid to determine if the card has won.
  * @param [in] grid The squares of a bingo card.
  * @return true, if the victory condition is met, false otherwise.
  */
  virtual bool hasWon(std::vector<Square*> grid) = 0;

 protected:
  std::string _description;
  BingoTypes::victoryType _victoryType;
  /**
  * @brief Determines if all the Squares in squares are daubed and correct.
  * @param [in] squares The squares to be checked.
  * @return false, if any of the squares are not daubed or not correct,
  *   true otherwise.
  */
  bool checkSquareSet(std::vector<Square*> squares);
};

/**
* @class HorizontalLine VictoryCondition.h "VictoryCondition.h"
* @brief Implements the victory condition: one horizontal line of squares is
*   correctly daubed.
*/
class HorizontalLine : public VictoryCondition {
 public:
  /**
  * @brief Default constructor, set _victoryType and description.
  */
  HorizontalLine();

  /**
  * @brief Destructor
  */
  virtual ~HorizontalLine();

  /**
  * @brief Examines the grid to determine if the card has won.
  * @details Determines if any horizontal line of the bingo card has Squares
  *   that are all daubed and correct.
  * @param [in] grid The squares of a bingo card.
  * @return true, if the victory condition is met, false otherwise.
  */
  bool hasWon(std::vector<Square*> grid);
};

/**
* @class VerticalLine VictoryCondition.h "VictoryCondition.h"
* @brief Implements the victory condition: one vertical line of squares is
*   correctly daubed.
*/
class VerticalLine : public VictoryCondition {
 public:
  /**
  * @brief Default constructor, set _victoryType and description.
  */
  VerticalLine();

  /**
  * @brief Destructor
  */
  virtual ~VerticalLine();

  /**
  * @brief Examines the grid to determine if the card has won.
  * @details Determines if any vertical line of the bingo card has Squares
  *   that are all daubed and correct.
  * @param [in] grid The squares of a bingo card.
  * @return true, if the victory condition is met, false otherwise.
  */
  bool hasWon(std::vector<Square*> grid);
};

/**
* @class AnyLine VictoryCondition.h "VictoryCondition.h"
* @brief Implements the victory condition: any line horizontal, vertical or
*   diagonal of five squares is correctly daubed.
*/
class AnyLine : public VictoryCondition {
 public:
  /**
  * @brief Default constructor, set _victoryType and description.
  */
  AnyLine();

  /**
  * @brief Destructor
  */
  virtual ~AnyLine();

  /**
  * @brief Examines the grid to determine if the card has won.
  * @details Determines if any line, vertical, horizontal, or diagonal of the
  *   bingo card has five Squares that are all daubed and correct.
  * @param [in] grid The squares of a bingo card.
  * @return true, if the victory condition is met, false otherwise.
  */
  bool hasWon(std::vector<Square*> grid);
};

/**
* @class Blackout VictoryCondition.h "VictoryCondition.h"
* @brief Implements the victory condition: all squares are correctly daubed.
*/
class Blackout : public VictoryCondition {
 public:
  /**
  * @brief Default constructor, set _victoryType and description.
  */
  Blackout();

  /**
  * @brief Destructor
  */
  virtual ~Blackout();

  /**
  * @brief Examines the grid to determine if the card has won.
  * @details Determines if all Squares are daubed and correct.
  * @param [in] grid The squares of a bingo card.
  * @return true, if the victory condition is met, false otherwise.
  */
  bool hasWon(std::vector<Square*> grid);
};
#endif // VICTORY_CONDITION_H_INCLUDED
