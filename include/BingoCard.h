/**
* @author L. Nicole  Wilson [n.wilson@uleth.ca]
* @date 2023-09
*/
#ifndef BINGOCARD_H_INCLUDED
#define BINGOCARD_H_INCLUDED

#include <vector>

#include "UserInput.h"
#include "VictoryCondition.h"
#include "Square.h"
#include "BingoTypes.h"

/**
* @class BingoCard BingoCard.h "BingoCard.h"
* @brief Implements the bingo card for a game of bingo.
*/
class BingoCard {
 public:
  /**
  * @brief Default constructor.
  * @details Initializes _victoryCondition to nullptr.
  * @param [in] type The type of game that can use this bingo card.
  */
  BingoCard(BingoTypes::gameType type = BingoTypes::BINGO75);

  /**
  * @brief Constructor, uses setGrid.
  * @details Initializes _victoryCondition to nullptr, and uses setGrid to
  *   initialize the squares in _grid.
  * @param [in] grid The squares on the bingo card.
  * @param [in] type The type of game that can use this bingo card.
  */
  BingoCard(std::vector<Square*> grid,
            BingoTypes::gameType type = BingoTypes::BINGO75);

  /**
  * @brief Destructor.
  * @details Deallocates _victoryCondition and all the Square pointers
  *   in _grid.
  */
  virtual ~BingoCard();

  /**
  * @brief Access the gameType of this card.
  * @return The gameType set for this card.
  */
  BingoTypes::gameType getGameType();

  /**
  * @brief Access the victoryType of this card.
  * @return The victoryType set for this card.
  * @throw incomplete_settings If _victoryCondition is a nullptr.
  */
  BingoTypes::victoryType getVictoryType();

  /**
  * @brief Gives access to the square in the given position.
  * @param pos The position of the desired square.
  * @return A pointer to the desire square.
  */
  Square* getSquare(BingoTypes::squarePos pos);

  /**
  * @brief Updates the _victoryCondition.
  * @param victory A pointer to an instance of a VictoryCondition.
  * @throw bad_input If victory is a nullptr.
  */
  void setVictoryCondition(VictoryCondition* victory);

  /**
  * @brief If grid defines a valid bingo card for this gameType, sets _grid.
  * @details Uses checkGridValidity to make sure grid defines a valid bingo card.
  * @param [in] grid The Squares that define a bingo card.
  */
  void setGrid(std::vector<Square*> grid);

  /**
   * @brief Resets all the squares in the bingo card.
   * @details Uses checkGridValidity to make sure the grid has been set before attempting to reset squares.
  */
  void resetCard();

  /**
  * @brief Attempts to daub the indicated Square, returns false if already daubed.
  * @details Uses checkGridValidity to make sure the grid is set properly.
  *   Uses squarePosToLoc to access the correct access the correct Square pointer.
  *   The Square pointer is used to call daubSquare.
  *   If the numberCalled doesn't equal the square's value then shouldDaubSquare is
  *   called with every square in the grid.
  * @param [in] numberCalled The number called by the bingo caller.
  * @param [in] pos The position of the square the player wants to daub.
  * @return false, if the square at pos is already daubed and true otherwise.
  */
  bool daubSquare(unsigned numberCalled, BingoTypes::squarePos pos);

  /**
   * @brief Determines if the player has made any errors daubing this card.
   * @details Uses checkGridValidity to make sure the grid is set correctly.
  * @return false, if an error is found, true otherwise.
  */
  bool isCorrect();

  /**
   * @brief Determines if the card has correctly met the victory conditions.
   * @details Uses checkGridValidity to make sure the grid is set properly.
  * @return true, if the card has met the victory condition, false otherwise.
  * @throw incomplete_settings If _victoryCondition is a nullptr.
  */
  bool isVictorious();

  /**
  * @brief Determines if the given types and the card's types are equal.
  * @param [in] game The game type compared to the card's gameType.
  * @param [in] victory The victory type compared to the card's victoryType.
  * @return true if both types match, false otherwise.
  * @throw incomplete_settings if the victoryCondition is not set.
  */
  bool typesMatch(BingoTypes::gameType game, BingoTypes::victoryType victory);

 private:
  VictoryCondition* _victoryCondition;
  std::vector<Square*> _grid;
  BingoTypes::gameType _game;

  /**
  * @brief Determines if the numbers on the card are valid.
  * @details Checks that all numbers on the bingo card are distinct.
  *   Checks that the numbers under the B are in the first fifth of the number
  *   range, that those under I are in the second fifth of the number range, and so on.
  * @throw incomplete_settings if there are no squares in the grid.
  * @throw invalid_size if the grid's size is not 25.
  * @throw card_to_game_mismatch if the value of a square is not correct for its
  * position in the grid for the gameType of this card.
  * @throw bad_input If all the values in the squares are not unique.
  */
  void checkGridValidity(std::vector<Square*> grid);

  /**
   * @brief Convert a position entered by the user to a location in _grid.
   * @param [in] pos A squarePos between (1,1) and (5,5).
   * @return The location the square is stored in _grid.
   * @throw bad_input if the row or col of pos is not in the interval [1, 5].
   */
  unsigned squarePosToLocation(BingoTypes::squarePos pos);
};

#endif // BINGOCARD_H_INCLUDED
