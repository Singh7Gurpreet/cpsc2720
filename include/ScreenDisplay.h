/**
 * @author L. Nicole  Wilson [n.wilson@uleth.ca]
 * @date 2023-09, 2023-10
 */
#ifndef SCREEN_DISPLAY_H_INCLUDED
#define SCREEN_DISPLAY_H_INCLUDED

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "UserInput.h"
#include "Square.h"
#include "BingoTypes.h"
#include "BingoCaller.h"
#include "BingoCard.h"

/**
 * @class ScreenDisplay ScreenDisplay.h "ScreenDisplay.h"
 * @brief Methods for text based display.
 */
class ScreenDisplay {
 public:
  /**< The column width for displaying a bingo card. >**/
  const int COL_WIDTH = 6;
  /**
   * @brief Default constructor.
   */
  ScreenDisplay();

  /**
   * @brief Destructor.
   */
  ~ScreenDisplay();

  /**
   * @brief Display a the grid, showing the state of each square.
   * @details If a square is daubed then the number appears in braces,
   * @param [inout] out Insert to this input stream.
   * @param [in] grid A grid of squares.
   */
  void displayGrid(std::ostream& out,
                   const std::vector<Square*>& grid);

  /**
   * @brief Display a the bingo card, showing the squares' states.
   * @details If a square is daubed then the number appears in braces,
   *   if it is incorrect, it is followed by an x.
   * @param [inout] out Insert to this input stream.
   * @param [in] card A pointer to a bingo card.
   */
  void displayValidity(std::ostream& out, BingoCard* card);

  /**
   * @brief Display a the bingo card, showing which squares are daubed.
   * @param [inout] out Insert to this input stream.
   * @param [in] card A pointer to a bingo card.
   */
  void displayBingoCard(std::ostream& out,
                        BingoCard* card);

  /**
   * @brief Display a message for the caller.
   * @param [inout] out Insert to this input stream.
   * @param [in] msg The message from the caller.
   */
  void displayCallerMessage(std::ostream& out, std::string msg);

  /**
   * @brief Display the game info.
   * @details Shows the gameType and victoryType.
   * @param [inout] out Insert to this input stream.
   * @param [in] caller a pointer to a bingo caller.
   * @throw bad_input if the caller is a nullptr.
   */
  void displayGameInfo(std::ostream& out, BingoCaller* caller);

  /**
   * @brief Display the balls that have been pulled.
   * @details Shows the gameType and victoryType.
   * @param [inout] out Insert to this input stream.
   * @param [in] caller a pointer to a bingo caller.
   * @throw bad_input if the caller is a nullptr.
   */
  void displayGameBoard(std::ostream& out, BingoCaller* caller);

  /**
   * @brief Read the instructions from a file and display to the user.
   * @param [inout] out Insert to this input stream.
   * @param [in] filename The name of the file containing the instructions.
   * @param [in] tag The tag for the info in the file to be output.
   * @throw bad_input if the file cannot be opened or the tag isn't found.
   */
  void displayGameInstructions(std::ostream& out,
                               std::string filename, std::string tag);

  /**
   * @brief Display a string representation of the game's type.
   * @param [inout] out Insert to this input stream.
   * @param [in] game A type of game.
   */
  void displayGameType(std::ostream& out,
                       const BingoTypes::gameType& game);

  /**
   * @brief Display a string representation of the game's type.
   * @param [inout] out Insert to this input stream.
   */
  void displayGameTypePrompt(std::ostream& out);

  /**
   * @brief Display a string representation of the game's type.
   * @param [inout] out Insert to this input stream.
   * @param [in] move A type of player move.
   */
  void displayMoveType(std::ostream& out,
                       const BingoTypes::moveType& move);

  /**
   * @brief Display a string representation of the game's type.
   * @param [inout] out Insert to this input stream.
   */
  void displayMoveTypePrompt(std::ostream& out);

  /**
   * @brief Display a prompt to enter the position of a square.
   * @details Give the ranges for row, column, and card numbers.
   * @param [inout] out Insert to this input stream.
   */
  void displaySquarePositionPrompt(std::ostream& out);

  /**
   * @brief Display a prompt to enter a player's id.
   * @details List the valid player ids.
   * @param [inout] out Insert to this input stream.
   * @param [in] players A set of players available via identifier.
   */
  void displayPlayerIdPrompt(std::ostream& out,
                             const std::map<std::string, BingoCard*>& players);

  /**
   * @brief Display a bingo card, showing which squares are incorrect.
   * @param [inout] out Insert to this input stream.
   * @param [in] grid A grid of squares.
   */
  void displayValidityCheck(std::ostream& out,
                            const std::vector<Square*>& grid);

  /**
   * @brief Display a string representation of the game's type.
   * @param [inout] out Insert to this input stream.
   * @param [in] victory A type of victory condition.
   */
  void displayVictoryType(std::ostream& out,
                          const BingoTypes::victoryType& victory);

  /**
   * @brief Display a string representation of the game's type.
   * @param [inout] out Insert to this input stream.
   */
  void displayVictoryTypePrompt(std::ostream& out);

  /**
   * @brief Display the description of a victory condition.
   * @param [inout] out Insert to this input stream.
   * @param [in] victory A type of victory condition.
   */
  void displayVictoryDescription(std::ostream& out,
                                 const BingoTypes::victoryType& victory);

 private:
  /**
   * @brief Convert a gameType to string.
   * @param [in] game The gameType to convert.
   * @return The resulting string.
   */
  std::string gameToString(BingoTypes::gameType game);

  /**
   * @brief Convert a victoryType to string.
   * @param [in] victory The victoryType to convert.
   * @return The resulting string.
   */
  std::string victoryToString(BingoTypes::victoryType victory);

  /**
   * @brief Convert a victoryType to a description of a victoryCondition
   * @param [in] victory The victoryType to convert.
   * @return The resulting string.
   */
  std::string victoryToDescription(BingoTypes::victoryType victory);

  /**
   * @brief Convert a moveType to string.
   * @param [in] playerMove The moveType to convert.
   * @return The resulting string.
   */
  std::string moveToString(BingoTypes::moveType playerMove);

  /**
   * @brief Display horizontal border for bingo card.
   * @param [inout] out Insert to this input stream.
   * @param [in] colWidth number of characters of a column, excluding borders.
   */
  void drawHorizontalBorder(std::ostream& out, unsigned colWidth);

  /**
   * @brief Display header lines for bingo card.
   * @param [inout] out Insert to this input stream.
   * @param [in] colWidth number of characters of a column, excluding borders.
   */
  void drawBingoCardTop(std::ostream& out, unsigned colWidth);
};

#endif // SCREEN_DISPLAY_H_INCLUDED
